#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>

int pid, estado;

static void manejador (int sig){
	
	pid = wait(NULL);
}

int main (int argc, char *argv[]){
	if (argc != 2){
		perror("Debe especificar el nombre del fifo y ejecutarlo en segundo plano \"&\"\n");
		exit(-1);
	}
	
	char nombreFIFOe[50], nombreFIFOs[50], nombreProxy[50];
	int fde, fds, fdBloq, pidcliente, fdProxy;
	pid_t pidProxy;
	// Manejamos la señal
	signal(SIGCHLD, manejador);
	// Establecemos el nombre de los FIFOS
	sprintf(nombreFIFOe, "%se", argv[1]);
	sprintf(nombreFIFOs, "%ss", argv[1]);
	// Establecemos la máscara a cero.
	umask(0);
	// Creamos los FIFOS.
	mknod(nombreFIFOe, S_IFIFO|S_IRWXU,0);
	mknod(nombreFIFOs, S_IFIFO|S_IRWXU,0);
	// Abrimos los FIFOS.
	if ((fde=open(nombreFIFOe, O_RDWR))<0){
		perror("No se ha podido abrir el fifo de entrada.\n");
		exit(-1);
	}
	if ((fds=open(nombreFIFOs, O_RDWR))<0){
		perror("No se ha podido abrir el fifo de salida.\n");
		exit(-1);
	}
	
	// Creamos el archivo de bloqueo
	if ((fdBloq = open("archivoBloq", O_CREAT, S_IRWXU))<0){
		perror("Servidor: No se ha podido crear el archivo de bloqueo.\n");
		exit(-1);
	}
	
	// Mientras se lea del fifo de entrada.
	while (read(fde, &pidcliente, sizeof(int))!=0){
		pid = fork();
		if (pid==0){	// Si es el proceso hijo.
			// obtenemos su pid
			pidProxy = getpid();
			// Creamos la cadena del nombre del fifo del Proxy
			sprintf(nombreProxy, "fifo.%d", pidProxy);
			// Creamos el archivo fifo.
			mkfifo(nombreProxy, 0666);
			// Escribimos en el FIFOs el pid del proceso hijo
			if (write(fds, &pidProxy, sizeof(int))<0){
				perror("No se ha podido escribir el PID del proxy en el FIFOs.\n");
				exit(-1);
			}
			// Abrimos el FIFO en solo lectura.
			if ((fdProxy = open(nombreProxy, O_RDONLY))<0){
				perror("No se ha podido abrir el FIFO para el proxy.\n");
				exit(-1);
			}
			// Redirigimos la entrada estándar al archivo fifo
			dup2(fdProxy, STDIN_FILENO);
			// Ejecutamos el proxy
			execlp("./proxy","proxy", NULL);
			
			exit(0);
		}
	}
	// Borramos los archivos FIFOS.
	unlink (nombreFIFOe);
	unlink (nombreFIFOs);
	unlink ("archivoBloq");
}
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>

int main (int argc, char * argv[]){
	
	int pid = getpid(), leidos, fdBloqueo;
	char buffer[1024], nombreFIFO[50];
	FILE *tmp = tmpfile();
	struct flock cerrojo;
	
//	 Mientras haya datos en el FIFO estamos leyendo
	while ((leidos = read(STDIN_FILENO, buffer, 1024))!=0){
		fwrite(buffer, sizeof(char), leidos, tmp);
	}
	
//	Empezamos a establecer el bloqueo la salida en pantalla
	
// 	Abrimos el archivo de bloqueo.
	if ((fdBloqueo = open("archivoBloq", O_RDWR))<0){
		perror("Proxy: No se ha podido abrir el archivo de bloqueo\n");
		exit(-1);
	}
	
	sleep(5);
	
	// Establecemos los atributos de la estructura para realizar el bloqueo del fichero.
	cerrojo.l_type = F_WRLCK;		// Bloqueo para escritura.
	cerrojo.l_whence = SEEK_SET;	// Establecemos el bloqueo al inicio del fichero.
	cerrojo.l_start = 0;			// El bloqueo empieza en la posición inicial del fichero
	cerrojo.l_len = 0;				// El bloqueo es para todo el fichero (hasta el final)
	
	// Si está bloqueado esperamos hasta que se desbloquee.
	if (fcntl(fdBloqueo, F_SETLKW, &cerrojo)<0){
		perror ("Proxy: No se pudo bloquear la impresion.\n");
		exit(1);
	}
	// Ya tenemos la exclusión mutua para la pantalla.
	
	while (!feof(tmp)){
		// Leemos del fichero temporal.
		if ((leidos=fread(buffer, sizeof(char), 1024, tmp))<0){
			perror ("No se ha podido leer del fichero temporal.\n");
			exit(-1);
		}
		
		// Escribimos en salida estándar
		if (write(STDOUT_FILENO, buffer, 1024)<0){
			perror("No se ha podido escribir por salida estandar\n");
			exit(-1);
		}
	}
	
	// Desbloqueamos de nuevo el archivo.
	cerrojo.l_type = F_UNLCK;
	if (fcntl(fdBloqueo, F_SETLKW, &cerrojo)<0){
		perror ("Proxy: No se pudo desbloquear la impresion.\n");
		exit(1);
	}
	
	// Eliminamos el fifo del hijo.
	sprintf(nombreFIFO, "fifo.%d", getpid());
	unlink(nombreFIFO);
	exit(0);
}

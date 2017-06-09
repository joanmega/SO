// Ejercicio 1

#include "stdio.h"
#include <stdlib.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

int main (int argc, char * argv[]){
	
	int fd;
	
	if (argc != 4){
		perror("Introduce 3 parametros.\n");
		exit(-1);
	}
	if (strcmp(argv[2], "<")!=0 && strcmp(argv[2], ">")){
		perror("El segundo parametro debe ser \"<\" o \">\".\n");
		exit(-1);
	}
	
	if ((fd = open(argv[3], O_CREAT|O_RDWR, S_IRWXU, S_IRWXG ,S_IRWXO))<0){
		perror("Error al abrir o crear el fichero\n");
		exit(-1);
	}
	
	if (strcmp(argv[2], ">")==0){
// 		Si el direccionamiento es hacia el fichero hay que cambiar el 
// 		la salida estándar al fichero.
		
		close(1);
		if (fcntl(fd, F_DUPFD, 1)==-1){
			perror("Error al duplicar el descriptor\n");
			exit(-1);
		}
		
		if (execlp(argv[1], argv[1], NULL)<0){
			perror("Error en exec\n");
			exit(-1);
		}
	}else{
// 		Si el direccionamiento es hacia la orden de linux hay que cambiar el
// 		la entrada estándar al fichero.
		
		close(0);
		if (fcntl(fd, F_DUPFD, 0)==-1){
			perror("Error al duplicar el descriptor\n");
			exit(-1);
		}
		
		if (execlp(argv[1], argv[1], NULL)<0){
			perror("Error en exec\n");
			exit(-1);
		}
	}
}
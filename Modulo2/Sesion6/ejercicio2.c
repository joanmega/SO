// Ejercicio 2

#include "stdio.h"
#include <stdlib.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

int main (int argc, char * argv[]){
	
	int fd[2], PID;
	pipe(fd);
	
	if (argc != 4){
		perror("Introduce 3 parametros.\n");
		exit(-1);
	}
	
	if (strcmp(argv[2], "|")!=0){
		perror("El segundo parametro debe ser \"|\".\n");
		exit(-1);
	}
	
	if (strcmp(argv[2], "|")==0){
		
		if ((PID = fork())<0){
			perror("Error en el fork\n");
			exit(-1);
		}else{
			if (PID == 0){
				close(1);
				close(fd[0]);	// Cerramos lectura en el pipe
				if (fcntl(fd[1], F_DUPFD, STDOUT_FILENO)==-1){
					perror("Error al duplicar el descriptor\n");
					exit(-1);
				}
				if (execlp(argv[1], argv[1], NULL)<0){
					perror("Error en exec\n");
					exit(-1);
				}
			}else{
				close(0);
				close(fd[1]);	// Cerramos la escritura en pipe
				if (fcntl(fd[0], F_DUPFD, STDIN_FILENO)==-1){
					perror("Error al duplicar el descriptor\n");
					exit(-1);
				}
				if (execlp(argv[3], argv[3], NULL)<0){
					perror("Error en exec\n");
					exit(-1);
				}
			}
		}
	}
	return 0;
}
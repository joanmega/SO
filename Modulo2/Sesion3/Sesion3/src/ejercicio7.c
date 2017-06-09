// Ejercicio7.c

#include <sys/types.h>	//Primitive system data types for abstraction of implementation-dependent data types.
						//POSIX Standard: 2.6 Primitive System Data Types <sys/types.h>
#include <unistd.h>		//POSIX Standard: 2.10 Symbolic Constants         <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * argv[]){
	pid_t pid;
	int estado;

	if (argc<=1){
		printf("introduce un programa con sus argumentos seguido de 'bg' si quiere ejecutarlo en segundo plano.\n");
		exit(-1);
	}
	
	if( (pid=fork())<0) {
		perror("\nError en el fork");
		exit(-1);
	}
	
	else if(pid==0) { //proceso hijo ejecutando el programa
		if( (execv(argv[1], argv)<0)) {
			perror("\nError en el execl");
			exit(-1);
		}
	}
	wait(&estado);
	
	printf("\nMi hijo %d ha finalizado con el estado %d\n",pid,estado>>8);
	exit(0);
}
// Ejercicio3

#include <sys/types.h>	//Primitive system data types for abstraction of implementation-dependent data types.
						//POSIX Standard: 2.6 Primitive System Data Types <sys/types.h>
#include <unistd.h>		//POSIX Standard: 2.10 Symbolic Constants         <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

/*
Jerarquía de procesos tipo 1
*/

void procesoTipo1(int nprocs){
	int i;
	pid_t childpid;
	for (i=1; i < 20; i++) {
		if ((childpid=fork()) == -1) {
			fprintf(stderr, "Could not create child %d: %s\n",i,strerror(errno));
			exit(-1);
		}
		if (childpid){
			printf("Identificador de proceso hijo: %d\n", childpid);
			printf("Identificador del proceso padre: %d\n", getppid());
			break;
		}
	}
}
/*
Jerarquía de procesos tipo 2
*/

void procesoTipo2(int nprocs){
	int i;
	pid_t childpid;
	for (i=1; i < nprocs; i++) {
		if ((childpid=fork()) == -1) {
			fprintf(stderr, "Could not create child %d: %s\n",i,strerror(errno));
			exit(-1);
		}
		if (!childpid){
			break;
		}
		printf("Identificador de proceso hijo: %d\n", childpid);
		printf("Identificador del proceso padre: %d\n", getppid());
	}
}

void main (int argc, char * argv[]){
// 	printf("Proceso tipo 1\n");
// 	procesoTipo1(20);
	printf("Proceso tipo 2\n");
	procesoTipo2(20);
}
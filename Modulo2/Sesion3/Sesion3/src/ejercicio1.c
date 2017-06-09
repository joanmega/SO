// Ejercicio1

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void main(int argc, char * argv[])
{
	pid_t PID;
	if (argc != 2){
		printf("Introduce un numero por parametro\n\t Ej: ./ejercicio1 <numero>\n");
	}
	
	if ((PID = fork())<0){
		printf("No se ha podido realizar el fork\n");
		exit(-1);
	}else{	
		if (PID == 0){	// Es el proceso hijo
			if (atoi(argv[1])%2){
				printf("El numero es impar\n");
			}else{
				printf("El numero es par\n");
			}
		}else{	// Es el proceso padre
			if (atoi(argv[1])%4){
				printf("El numero no es divisible por 4\n");
			}else{
				printf("El numero es divisible por 4\n");
			}
		}
	}
}
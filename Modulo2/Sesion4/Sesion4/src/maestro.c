/*

Ejercicio 5.
Este ejercicio se basa en la idea de utilizar varios procesos para realizar partes de una
computación en paralelo. Para ello, deberá construir un programa que siga el esquema de
computación maestro-esclavo, en el cual existen varios procesos trabajadores (esclavos)
idénticos y un único proceso que reparte trabajo y reúne resultados (maestro). Cada esclavo
es capaz de realizar una computación que le asigne el maestro y enviar a este último los
resultados para que sean mostrados en pantalla por el maestro.
El ejercicio concreto a programar consistirá en el cálculo de los números primos que hay en
un intervalo. Será necesario construir dos programas, maestro y esclavo. Ten en cuenta la
siguiente especificación:
1. El intervalo de números naturales donde calcular los número primos se pasará como
argumento al programa maestro. El maestro creará dos procesos esclavos y dividirá
el intervalo en dos subintervalos de igual tamaño pasando cada subintervalo como
argumento a cada programa esclavo. Por ejemplo, si al maestro le proporcionamos el
intervalo entre 1000 y 2000, entonces un esclavo debe calcular y devolver los
números primos comprendidos en el subintervalo entre 1000 y 1500, y el otro esclavo
entre 1501 y 2000. El maestro creará dos cauces sin nombre y se encargará de su
redirección para comunicarse con los procesos esclavos. El maestro irá recibiendo y
mostrando en pantalla (también uno a uno) los números primos calculados por los
esclavos en orden creciente.


*/

#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include <string.h>

int main (int argc, char * argv[]){
	
	int fdPipe1[2], fdPipe2[2];
	char mitad1[10], mitad2[10];
	pid_t pid_esclavos[2], hijo;
	int i;
	
	if (argc!=3){
		printf ("Introduce el intervalo al que buscar los numeros primos\n");
		exit(-1);
	}
	
	pipe(fdPipe1);
	pipe(fdPipe2);
	
	sprintf(mitad1, "%d", ((atoi(argv[1])+atoi(argv[2]))/2));
	sprintf(mitad2, "%d", ((atoi(argv[1])+atoi(argv[2]))/2)+1);
	
 	for (i = 0; i<2; i++){
 		if ((hijo=fork())==0){
 			pid_esclavos[i]=getpid();
			break;
		}
 	}
	
	if(hijo==0){
		if ((pid_esclavos[0]==getpid())){
			close(fdPipe1[0]);
			dup2(fdPipe1[1], STDOUT_FILENO);
			if (execl("./esclavo", "./esclavo", argv[1], (char *) mitad1, NULL)<0){
				printf("No se ha podido ejecutar el esclavo 1\n");
				exit(-1);
			}
		}
// 		if ((pid_esclavos[1]==getpid())){
// 			close(fdPipe2[0]);
// 			dup2(fdPipe2[1], STDOUT_FILENO);
// 			if (execl("./esclavo", "./esclavo", (char *) (mitad2), argv[2], NULL)<0){
// 				printf("No se ha podido ejecutar el esclavo 2\n");
// 				exit(-1);
// 			}
// 		}
	}else{
		close(fdPipe1[1]);
		close(fdPipe2[1]);/*
		dup2(fdPipe1[0], STDIN_FILENO);
		dup2(fdPipe2[0], STDIN_FILENO);*/
	}
	
	wait();
	wait();
	
	char buffer[4];
	int n=0;
	
	printf("Llega aqui 1\n");
	
	while ((n=read(fdPipe1[0], buffer, sizeof(int)))!=0){
		printf("Hola %s", buffer);
	}
	
	printf("%d %s Llega aqui 2\n", n, buffer);
	printf("\n");
	
	// 	while ((read(fdEsclavo1[0], buffer, sizeof(int)))!=0){
// 		printf("%s ", buffer);
// 	}
	
	printf("\n");
	
}
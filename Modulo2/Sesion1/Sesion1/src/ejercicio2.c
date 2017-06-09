/*

ejercicio2.c

Implementa un programa que realice la siguiente funcionalidad. El programa
acepta como argumento el nombre de un archivo (pathname), lo abre y lo lee en bloques de
tamaño 80 Bytes, y crea un nuevo archivo de salida, salida.txt, en el que debe aparecer la
siguiente información:

*/

#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include <string.h>

int main(int argc, char *argv[]){
	
	int fdEntrada, fdSalida, leidos, numBloque=2;
	char buffer[80], linea[100]="", *entrada;
	
	
	if (argc !=2){
		if (argc == 1){
			printf("Introduce una ruta de archivo: ");
			scanf("%s", entrada);
		}else{
			perror("Falta el nombre del archivo a leer\n");
			exit(EXIT_FAILURE);
		}
	}
	
	
	if (argc ==2){
 		entrada = argv[1];
	}
	
	if ((fdEntrada=open(entrada, O_RDONLY))<0 ){
		printf("\nError %d en open del archivo de lectura",errno);
		perror("\nError en open");
		exit(EXIT_FAILURE);
	}
	
	if ((fdSalida=open("salida.txt", O_CREAT|O_RDWR, S_IRUSR|S_IWUSR))<0 ){
		printf("\nError %d en open del archivo de salida",errno);
		perror("\nError en open");
		exit(EXIT_FAILURE);
	}
	
	if ((leidos=read(fdEntrada, buffer, 80))>0){
		
		sprintf (linea, "Bloque 1\n// Aquí van los primeros 80 Bytes del archivo pasado como argumento.\n\n");
		
		write (fdSalida, linea, 80);
 		write (fdSalida, buffer, leidos);
		
		while ((leidos=read(fdEntrada, buffer, 80))!=0){
			
			sprintf (linea, "\n\nBloque %d\n// Aquí van los siguientes 80 Bytes del archivo pasado como argumento.\n\n   ", numBloque);
			write (fdSalida, linea, 84);
			write (fdSalida, buffer, leidos);
			numBloque++;
		}
	}else{
		printf ("El archivo origen esta vacio\n");
	}
	
	close(fdEntrada);
	close(fdSalida);
	
}

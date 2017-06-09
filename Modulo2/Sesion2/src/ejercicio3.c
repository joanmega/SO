// ejercicio3.c

#include<sys/types.h> 	//Primitive system data types for abstraction of implementation-dependent data types.
//POSIX Standard: 2.6 Primitive System Data Types <sys/types.h>

#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<errno.h>

#include<dirent.h>


int main(int argc, char *argv[]){
	
	DIR *directorioInicial, *directorioActual;
	struct dirent *archivo;
	int fd, i=0, tamanio=0;
	struct stat atributos;
	
	if(argc!=2) {
		printf("\nSintaxis de ejecucion: buscar <pathname>\n\n");
		exit(-1);
	}
	
	directorioInicial = opendir(argv[1]);
	
	archivo = readdir(directorioInicial);
	
	printf("Los i-nodos son:\n");
	
	while(archivo != NULL){
		// 		Sí es regular
		if (lstat(archivo->d_name, &atributos)<0){
			printf("\nError al intentar acceder a los atributos");
			perror("\nError en lstat");
		}else{
			if(S_ISREG(atributos.st_mode) && (atributos.st_mode & S_IXOTH) && (atributos.st_mode & S_IXGRP)){
				printf("%s \t%li \n", archivo->d_name, atributos.st_ino);
				++i;
				tamanio=tamanio+atributos.st_size;
			}
		}
		archivo = readdir(directorioInicial);
	}
	if(closedir(directorioInicial)<0) {
		printf("\nFallo en cerrar directorio\n\n");
		exit(-1);
	}
	printf("Existen %d archivos regulares con permiso x para grupo y otros\n", i);
	printf("El tamaño total ocupado por dichos archivos es %d bytes\n", tamanio);
	return 0;
}
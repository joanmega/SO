#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

int main (int argc, char *argv[]){
	if (argc!=3){
		perror("Introduce el fichero fuente seguido del fichero destino.\n");
		exit(-1);
	}
	
	struct stat atributos;	// variable para los atributos.
	char *p1, *p2;	// Variables para guardar la memoria del archivo.
	int fd1, fd2;	// Descriptores de ambos archivos.
	
	if (stat(argv[1], &atributos)==-1){	// Leemos los atributos del primer archivo
		perror ("Error al hacer stat.\n");
		exit(-1);
	}
	
// 	Abrimos el fichero que vamos a copiar.
	if((fd1 = open (argv[1], O_CREAT|O_RDWR, S_IRWXU | S_IRWXG | S_IRWXO))<0){
		perror ("Error al hacer open.\n");
		exit(-1);
	}
	
// 	Hacemos la proyeccion del archivo 1.
	p1 = (char*) mmap (NULL, atributos.st_size, PROT_READ, MAP_SHARED, fd1, 0);
	if (p1 == MAP_FAILED) {//retorna en memoria la direccion principal de la proyeccion
		perror("Fallo la proyeccion2");//si fallo devuelve MAP_FAILED
		exit(-1);
	}
	
// 	Abrimos el fichero que al que vamos a copiar.
	if((fd2 = open (argv[2], O_CREAT|O_RDWR, S_IRWXU | S_IRWXG | S_IRWXO))<0){
		perror ("Error al hacer open.\n");
		exit(-1);
	}
	
// 	Hacemos la proyección del archivo 2.
	p2 = (char*) mmap (NULL, atributos.st_size, PROT_WRITE, MAP_SHARED, fd2, 0);
	if (p2 == MAP_FAILED) {//retorna en memoria la direccion principal de la proyeccion
		perror("Fallo la proyeccion2");//si fallo devuelve MAP_FAILED
		exit(-1);
	}
	
	// Realizamos el truncamiento.
	ftruncate(fd2, atributos.st_size);
	
// 	Realizamos la copia del contenido de la memoria de ambos ficheros.
	
	memcpy(p2, p1, atributos.st_size);
	
//	Cerrar la proyeccion del archivo 1.
	if(munmap (p1, atributos.st_size) == -1) {
		printf("Error al cerrar la proyeccion \n");
		exit(-1);
	}
	
	//	Cerrar la proyeccion del archivo 2.
	if(munmap (p2, atributos.st_size) == -1) {
		printf("Error al cerrar la proyeccion \n");
		exit(-1);
	}
	return 0;
}
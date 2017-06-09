#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include<dirent.h>
#include<string.h>

int main (int argc, char *argv[]){
	
	if (argc!=3){
		printf("\nNo se ha introducido los parámetros correctos.\n\t./ejercicio3 <pathname> <permisos>\n\n");
		exit(-1);
	}
	
	char * pEnd;
	long int permisos = strtol(argv[2], &pEnd, 8);
		
	DIR * directorio;
	struct dirent *archivo;
	
	directorio = opendir(argv[1]);
	archivo = readdir(directorio);
	
	struct stat atributos;
	int fd;
	
	while (archivo != NULL){
		
		if ((strcmp(archivo->d_name,"..")!=0) && (strcmp(archivo->d_name, ".")!=0)){
			
			printf("%s ", archivo->d_name);
			
			if(stat(archivo->d_name, &atributos) < 0) {
				printf("\nError al intentar acceder a los atributos\n");
				perror("\nFallo en stat");
				exit(-1);
			}
			
			if((atributos.st_mode & S_IRUSR)!=0) printf("<r"); else printf("<-");
			if((atributos.st_mode & S_IWUSR)!=0) printf("w"); else printf("-");
			if((atributos.st_mode & S_IXUSR)!=0) printf("x"); else printf("-");
			if((atributos.st_mode & S_IRGRP)!=0) printf("r"); else printf("-");
			if((atributos.st_mode & S_IWGRP)!=0) printf("w"); else printf("-");
			if((atributos.st_mode & S_IXGRP)!=0) printf("x"); else printf("-");
			if((atributos.st_mode & S_IROTH)!=0) printf("r"); else printf("-");
			if((atributos.st_mode & S_IWOTH)!=0) printf("w"); else printf("-");
			if((atributos.st_mode & S_IXOTH)!=0) printf("x> "); else printf("-> ");
			
			if(chmod(archivo->d_name, permisos) < 0) {
				perror("\nError en chmod para archivo");
				exit(-1);
			}
			
			if(stat(archivo->d_name, &atributos) < 0) {
				printf("\nError al intentar acceder a los atributos");
				perror("\nFallo en stat");
				exit(-1);
			}
			
			if((atributos.st_mode & S_IRUSR)!=0) printf("<r"); else printf("<-");
			if((atributos.st_mode & S_IWUSR)!=0) printf("w"); else printf("-");
			if((atributos.st_mode & S_IXUSR)!=0) printf("x"); else printf("-");
			if((atributos.st_mode & S_IRGRP)!=0) printf("r"); else printf("-");
			if((atributos.st_mode & S_IWGRP)!=0) printf("w"); else printf("-");
			if((atributos.st_mode & S_IXGRP)!=0) printf("x"); else printf("-");
			if((atributos.st_mode & S_IROTH)!=0) printf("r"); else printf("-");
			if((atributos.st_mode & S_IWOTH)!=0) printf("w"); else printf("-");
			if((atributos.st_mode & S_IXOTH)!=0) printf("x>\n"); else printf("->\n");
		}
		archivo = readdir(directorio);
	}
	
	if(closedir(directorio)<0) {
		printf("\nFallo en cerrar directorio\n\n");
		exit(-1);
	}
	printf("\n");
	return 0;
}
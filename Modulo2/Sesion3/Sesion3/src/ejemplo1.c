// Ejemplo1

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

void main(void)
{
	pid_t id_proceso;
	pid_t id_padre;
	id_proceso = getpid();
	id_padre = getppid();
	printf("Identificador de proceso: %d\n", id_proceso);
	printf("Identificador del proceso padre: %d\n", id_padre);
	
	printf("Identificador de usuario: %d\n", getuid());
	printf("Identificador de usuario efectivo: %d\n", geteuid());
	printf("Identificador de grupo: %d\n", getgid());
	printf("Identificador de grupo efectivo: %d\n", getegid());
}
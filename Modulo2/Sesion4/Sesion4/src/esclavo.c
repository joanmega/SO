#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include <string.h>

/*
2. El programa esclavo tiene como argumentos el extremo inferior y superior del
intervalo sobre el que buscará números primos. Para identificar un número primo
utiliza el siguiente método concreto: un número n es primo si no es divisible por
ningún k tal que 2 < k <= sqrt(n), donde sqrt corresponde a la función de cálculo
de la raíz cuadrada (consulte dicha función en el manual). El esclavo envía al maestro
cada primo encontrado como un dato entero (4 bytes) que escribe en la salida
estándar, la cuál se tiene que encontrar redireccionada a un cauce sin nombre. Los
dos cauces sin nombre necesarios, cada uno para comunicar cada esclavo con el
maestro, los creará el maestro inicialmente. Una vez que un esclavo haya calculado y
enviado (uno a uno) al maestro todos los primos en su correspondiente intervalo
terminará.
*/


int main (int argc, char * argv[]){
	
	int i, k, primo = 0;
	char archivo[20];
	
	printf("Minimo %s - Maximo: %s con pid %d.\n", argv[1], argv[2], getpid());
	
	int escritos;
	
	for (i = atoi(argv[1]); i<=atoi(argv[2]); i++){
		for (k = 2; i%k && k <= sqrt(i); k++){
			if (i%k){
				primo = 1;
			}
		}
		if (primo == 1){
		printf("%d\n", i);
			write(STDOUT_FILENO, &i, sizeof(int));
		}
		primo = 0;
	}
	return 0;
}
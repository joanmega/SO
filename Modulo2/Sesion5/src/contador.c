#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>

int cont[31];
struct sigaction sa;

static void contador(int sigNum, siginfo_t *si, void *contex){
	cont[sigNum-1]++;
	printf("La senal %d se ha recibido %d veces.\n", sigNum, cont[sigNum-1]);
}

int main(int argc, char *argv[]){
	int i;
	for (i = 0 ; i<31; ++i){
		cont[i] = 0;
	}
	
	sa.sa_sigaction = contador;
	sigemptyset(&sa.sa_mask);
	
	sa.sa_flags = SA_SIGINFO;
	
	for (i = 1; i <=31; i++){
		if (sigaction(i, &sa, NULL) == -1){
			printf("error en el manejador");
		}
	}
	for (;;){}
}
#include<sys/types.h> //Primitive system data types for abstraction of implementation-dependent data types.
//POSIX Standard: 2.6 Primitive System Data Types <sys/types.h>
#include<unistd.h>    //POSIX Standard: 2.10 Symbolic Constants         <unistd.h>
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>


int main(int argc, char *argv[]){
	
	int num_hijos = 3;
	int i, estado;
	pid_t pid;
	
	for(i=0; i<num_hijos; i++){
		if((pid = fork())<0){
			perror("Error fork\n");
			exit(-1);
		}
		if(pid==0){
			printf("I am the son %i\n", getpid());
			exit(0);
		}
	}    
	
	for(i=num_hijos-1; i>=0; i--){
		pid = wait(&estado);
		printf("My son just finished with PID = %i\n", pid);
		printf("I only have %i living children\n", i);
	}
	
	exit(0);
	
}

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
int ntimes = 0;
int pid[3];

int main(){
    pid_t ppid;
    void p_action(int), c_action(int), c2_action(int);

    static struct sigaction pact, cact, ccact;

    pact.sa_handler = p_action;
    sigaction(SIGUSR2, &pact, NULL);
	int pppid = getpid();

	for (int i = 0; i < 3; i++){
        if (pppid == getpid()) {
            pid[i] = fork();
        }
    }
	// 1 Daughter process
	if(pid[0] == 0){
		cact.sa_handler = c_action;
			sigaction(SIGUSR1, &cact, NULL);

			//Get parent ID
			ppid = getppid();

			for(;;){
				sleep(1);
				
				printf("Daughter process 1 put SIGUSR2 to parent\n");
				kill(ppid, SIGUSR2);
				pause();	
			}
	}
	// 2 Daughter process
	if(pid[1] == 0) {
		ccact.sa_handler = c2_action;
		sigaction(SIGUSR1, &ccact, NULL);

		//Get parent ID
		ppid = getppid();

		for(;;){
			sleep(1);
			
			printf("Daughter process 2 put SIGUSR2 to parent\n");
			kill(ppid, SIGUSR2);
			pause();	
		}
	}
	//Parent
	if (pppid == getpid()){
		for(;;) {
			pause();
			sleep(1);
			printf("Parent process put SIGUSR1 to daughter 1\n");
			kill(pid[0], SIGUSR1);

			pause();
			sleep(1);
			printf("Parent process put SIGUSR1 to daughter 2\n");
			kill(pid[1], SIGUSR1);
		}
	}

	
}

void p_action(int sig){
	if(sig == SIGUSR2){
		printf("Parent process get signal #%d from Dauther\n", ++ntimes);
	}
	else printf("error");
}

void c_action(int sig) {
	if(sig == SIGUSR1) {
		printf("Daughter 1 proccess get signal #%d\n", ++ntimes);
	}
	else printf("error");
}

void c2_action(int sig) {
	if(sig == SIGUSR1) {
		printf("Daughter 2 proccess get signal #%d\n", ++ntimes);
	}
	else printf("error");
}

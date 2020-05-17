#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

#define	DELAY	5

int main(int argsc, char **argsv) {
	//srand(time(0));
	int i = 0;
	//int num_children;
 //sscanf(argsv[1], "%d", &num_children);
	int new_pid;
	void child_code(), parent_code();
	
	int child_ids[2];
	
	//printf("making %d children\r\n", num_children);
	printf("before: mypid is %d\n", getpid());
	
	while (i < 2) {
		//int sleep_time = rand() % 20 + 1;
		if ((new_pid = fork()) == -1) {
			perror("fork");
		} else if(new_pid == 0) {
			child_code(DELAY + i);
		}
		
		child_ids[i] = new_pid;
		i++;
	}
	
	
	parent_code(child_ids, i);
	
	return 0;
}

void child_code(int delay) {
	printf("child %d here. will sleep for %d seconds\n", getpid(), delay);
	sleep(delay);
	printf("child done. about to exit\n");
	exit(delay);
}

void parent_code(int ids[], int id_size) {
	int i = 0;
	int wait_rv;		/* return value from wait() */
	int child_status;
	int high_8, low_7, bit_7;
	
	while(i < id_size) {
		//wait_rv = wait(&child_status);
		wait_rv = waitpid(ids[i], &child_status, 0);
		printf("done waiting for %d. Wait returned: %d\n", ids[i], wait_rv);
		
		high_8 = child_status >> 8;     /* 1111 1111 0000 0000 */
		low_7  = child_status & 0x7F;   /* 0000 0000 0111 1111 */
		bit_7  = child_status & 0x80;   /* 0000 0000 1000 0000 */
		printf("status: exit=%d, sig=%d, core=%d\n", high_8, low_7, bit_7);
		i++;
	}
}
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#define AVERAGE    0
#define WORD_COUNT 1
#define EDIT       2

#include "marks.h"
#include "wc.h"
#include "find_and_replace.h"

void parent(int ids[], int id_size);

int main(int argsc, char **argsv) {
	int new_pid;
	int i = 0;
	int child_ids[3];
	
	char *file_1, *file_2;
	if (argsc < 3) { // Check that we have the minimum number of arguments.
		printf("\033[1;31m[ ERROR ]\033[0m :: Missing required arguments\r\n");
		return 1;
	} else {
		if (argsc > 3) { // Show a warning to the user if too many arguments were supplied.
			printf("\033[1;33m[ WARNING ]\033[0m :: Extra arguments have been supplied. Ignoring the following arguments:\r\n");
			int z = 3;
			while (z < argsc) {
				printf("Argument %d: %s\r\n\r\n", z, argsv[z]);
				z++;
			}
		}
		
		// Store the two files that were passed in as command line arguments.
		file_1 = argsv[1];
		file_2 = argsv[2];
	}
	
	// Loop from 0 to 2 (inclusive)
	while (i <= 2) {
		// Try to create a new fork and catch any errors.
		if ((new_pid = fork()) == -1) {
			perror("forking error");
		} else if(new_pid == 0) {
			// If a new for is created, determine which function to run based on the current loop we are in.
			switch (i) {
				case AVERAGE: {
					get_marks();
				} break;
				
				case WORD_COUNT: {
					call_wc(file_1);
				} break;
				
				case EDIT: {
					edit_file(file_2, "examine");
				} break;
			}
		}
		
		// Store the new id in an array.
		child_ids[i] = new_pid;
		i++;
	}
	
	// Call a parent function that waits for all the child processes to finish.
	parent(child_ids, i);
	printf("Parent done\r\n");
	return 0;
}

void parent(int ids[], int id_size) {
	int i = 0;
	int wait_rv;
	int child_status;
	int high_8;
	
	// Loop from 0 to however many process ids were created.
	while (i < id_size) {
		// wait for the process to end and save it's return value.
		wait_rv = waitpid(ids[i], &child_status, 0);
		
		// Get the high 8 bits which will be the exit status of the process.
		high_8 = child_status >> 8;
		// Determine which process we are outputting for based on the current iterator value.
		switch (i) {
			case AVERAGE: {
				printf("Average Marks: ");
			} break;
			
			case WORD_COUNT: {
				printf("Word Count: ");
			} break;
			
			case EDIT: {
				printf("Search and Replace: ");
			} break;
		}
		
		// Output which child is done, and it's exit status
		printf("Child %d done. The exit status is %d.\r\n", ids[i], high_8);
		
		i++;
	}
}





#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "iorb.h"
#include "priority.h"

#include "tests.h"


int main(int argsc, char *argsv[]) {
	srand(time(NULL));
	if (argsc > 1) {
		if (!strcmp(argsv[1],"-test")) {
			run_tests();
		}
	} else {
		int (*prio)(int);
		prio = &compute_priority;
		
		IORB* list_root = (IORB *)malloc(sizeof(IORB));
		
		int choice;
		// Keep looping until the user inputs the number 0. Each loop display a list
		// of choices and wait for input from the user.
		// Depending on the input, run the relevant function.
		while (1) {
			printf("\r\nPlease enter your choice:\r\n0) Exit\r\n1) Build List\r\n2) Sort List (ascending)\r\n3) Display List\r\n");
			scanf("%d", &choice);
			
			switch (choice) {
				case 0: {
					printf("Terminating\r\n");
					return 0;
				} break;
				
				case 1: {
					build_list(list_root, 10);
				} break;
				
				case 2: {
					sort_list(list_root, prio);
				} break;
				
				case 3: {
					display_list(list_root, (*prio));
				} break;
				
				default: {
					printf("You have entered an invalid option. Please select an option between 0 and 3\r\n");
				} break;
			}
		}
	}
	
	return 0;
}
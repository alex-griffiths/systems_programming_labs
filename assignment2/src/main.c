#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#define AVERAGE    0
#define WORD_COUNT 1
#define EDIT       2

void get_marks();
void parent(int ids[], int id_size);
void call_wc(char *filename);
void edit_file(char *filename, char *needle);

int main(int argsc, char **argsv) {
	char *file_1, *file_2;
	if (argsc < 3) {
		perror("Missing required arguments.\r\n");
	} else {
		file_1 = argsv[1];
		file_2 = argsv[2];
	}
	
	
	get_marks();
	call_wc(file_1);
	edit_file(file_2, "examine");
	
	return 0;
}

void parent(int ids[], int id_size) {
	int i = 0;
	int wait_rv;
	int child_status;
	int high_8, low_7, bit_7;
	
	while (i < id_size) {
		wait_rv = waitpid(ids[i], &child_status, 0);
		
		high_8 = child_status >> 8;     /* 1111 1111 0000 0000 */
		low_7  = child_status & 0x7F;   /* 0000 0000 0111 1111 */
		bit_7  = child_status & 0x80;   /* 0000 0000 1000 0000 */
		
		switch (i) {
			case AVERAGE: {
				
			} break;
			
			case WORD_COUNT: {
				
			} break;
			
			case EDIT: {
				
			} break;
		}
		
		i++;
	}
}

void edit_file(char *filename, char *needle) {
	char *replace = "check";
	
	FILE *r_fp = fopen(filename, "r"); // Read file pointer
	
	// Determine the size of buffer needed.
	fseek(r_fp, 0, SEEK_END);
	size_t buf_size = ftell(r_fp);
	// Go back to beginning of the file.
	rewind(r_fp);
	
	// allocate the buffer.
	char *buf = NULL;
	buf = malloc((buf_size + 1) * sizeof(*buf));
	
	// read the file into the buffer.
	fread(buf, buf_size, 1, r_fp);
	fclose(r_fp); // Close the read file pointer
	
	// Terminate the buffer.
	buf[buf_size] = '\0';
	
	// Set up file to write to it. 'w' mode will clear the contents of the file, meaning we will have an empty file that we will be writing to.
	FILE *w_fp = fopen(filename, "w");
	
	// Write update line to file initially. 
	char *update_line = "This is the updated version.";
	fprintf(w_fp, "%s", update_line);
	char *word;
	
	word = strtok(buf, " ");
	// Iterate over each word in the buffer.
	while(word != NULL) {
		// Compare current word to needle.
		if (strcmp(word, needle) == 0) {
			// Replace needle with the desired word and write it to the file.
			fprintf(w_fp, "%s ", replace);
		} else {
			// Write the current word to the file.
			fprintf(w_fp, "%s ", word);
		}
		word = strtok(NULL, " ");
	}
	
	if (fclose(w_fp)) { // Close the write file pointer;
		exit(200);
	} else {
		exit(0);
	}
}


void call_wc(char *filename) {
	char	*arglist[3];
	
	arglist[0] = "wc";
	arglist[1] = filename;
	arglist[2] = 0 ;
	
	execvp("wc" , arglist);
}

void get_marks() {
	float sum = 0.0;
	int i = 0;
	printf("Please enter each mark:\r\n");
	while(i < 10) {
		float mark;
		scanf("%e", &mark);
		sum = sum + mark;
		i++;
	}
	
	// Calculate the average;
	float average = sum / (float)i;
	
	printf("The average mark is %.2f\r\n", average);
	
	exit(200);
}
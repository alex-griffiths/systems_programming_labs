#ifndef FIND_REPLACE_H_
#define FIND_REPLACE_H_

// This function is passed a file path and a needle to search for. It will search the supplied file and replace all instances of the needle with a defined word. It will also write a new line to the top of the file.
void edit_file(char *filename, char *needle) {
	printf("\r\nChild %d here. Will update file.\r\n", getpid());
	char *replace = "check";
	// Check that we can actually access the file.
	if (access(filename, F_OK) != -1) {
		FILE *r_fp = fopen(filename, "r"); // Read file pointer
		// Determine the size of buffer needed.
		fseek(r_fp, 0, SEEK_END);
		size_t buf_size = ftell(r_fp);
		// Go back to beginning of the file.
		rewind(r_fp);
		
		// allocate the buffer.
		char *buf = NULL;
		buf = malloc((buf_size + 1) * sizeof(*buf)); // plus one to handle \0 that is added.
		
		// read the file into the buffer.
		fread(buf, buf_size, 1, r_fp);
		fclose(r_fp); // Close the read file pointer
		
		// Terminate the buffer.
		buf[buf_size] = '\0';
		
		// Set up file to write to it. 'w' mode will clear the contents of the file, meaning we will have an empty file that we will be writing to.
		FILE *w_fp = fopen(filename, "w");
		
		// Write update line to file initially. 
		char *update_line = "This is the updated version.\r\n";
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
		
		fclose(w_fp);
		printf("%s has been updated\r\n", filename);
		exit(0);
	} else {
		printf("\033[1;31m[ ERROR ]\033[0m :: %s : File does not exist\r\n", filename);
		exit(1);
	}
}

#endif


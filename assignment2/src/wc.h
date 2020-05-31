#ifndef WC_H_
#define WC_H_

// Given a filename, call the wc program with execvp to get the number of words in the file.
void call_wc(char *filename) {
	printf("\r\nChild %d here. Will execute command wc.\r\n", getpid());
	char	*arglist[4];
	
	// Define arguments vector that will be passed to execvp
	arglist[0] = "wc";
	arglist[1] = filename;
	arglist[2] = "-w"; // Makes sure that wc only outputs the number of words.
	arglist[3] = 0 ;
	
	printf("\r\nHere is the output from wc:\r\n");
	execvp("wc" , arglist); // Run the wc program with our given arguments.
}

#endif
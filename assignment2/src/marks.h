#ifndef MARKS_H_
#define MARKS_H_

// This function reads in 10 inputs from stdin and calculates an average mark based on these input values.
int get_marks() {
	printf("\r\nChild %d here. Will calculate average mark.\r\n", getpid());
	float sum = 0;
	int i = 1;
	printf("Please enter each mark:\r\n");
	// Read 10 inputs from stdin.
	while(i <= 10) {
		float mark;
		printf("(%d):", i);
		scanf("%f", &mark);
		// Add the new mark to the sum of marks.
		sum += mark;
		i++;
	}
	
	// Calculate the average;
	// Minus one to account for the fact we start the count at one, which eventully ends up at 11.
	float average = sum / (i - 1);
	
	printf("The average mark is %.2f\r\n", average);
	
	exit(0);
}

#endif
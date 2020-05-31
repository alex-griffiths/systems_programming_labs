Name: Alex Griffiths
Student ID: 18001525

Instructions:
To build the program you can run "bash build.sh" which will run my build script. This script just runs the compiler and outputs the executable file to the "build" directory.
Additionally you could also directly call the compiler: "cc src/main.c -o build/main"

To run the program run "./build/main file1.txt file2.txt" where "file1.txt" is the file you would like the word count of, and "file2.txt" is the file you would like read and modify. These files can be any valid file path.

Solution Logic:
Driver:
	Check how many arguments were supplied
	If the number of arguments is less than 3 throw an error.
	If the number of arguments is not less than three check if the number is greater than 3. If it is, display a warning to the user and ignore the extra arguments.
	Loop 3 times
		Each time we loop, create a new fork and check that it is created correctly.
		Based on the number of times we have looped we will determine which function to run.
		If this is the first time we have looped, run the get_marks() function
		If this the second time we have looped, run the call_wc() function and pass the first argument to the function.
		If this is the third time we have looped, call the edit_file() function and pass the second argument, and the word we are looking for to the function.
		At the end of each loop save the new process id in an array.
		Increment the loop counter
	Run the parent() function.

Parent Code (parent(int ids, int id_size)):
	Loop from from 0 to the number of child processes - in this case, 3.
		Each loop we wait for the return value of a given child process.
		Based on the number of times we've looped through we print out what the child process is, and it's exit status.

Update File (edit_file(char *filename, char *needle)):
	Print the process id and what is going to happen.
	Define the word we that we will use to replace the needle (examine).
	Check that we can access the file properly. This will tell us if the file exists or not. 
	If it doesn't, print an error, and exit with status code 1.
	If it does, open the given file based on the filename/file path in read only mode and store a pointer to it.
	Move to the end of the file and return the position in the file, giving us the size of the buffer we will need.
	Move the file pointer back to the beginning of the file.
	Allocate the memory required to store the contents of the file.
	Read the file into a buffer.
	Close the read file.
	Add the termination character at the end of the buffer.
	Open the file again, this time for writing, which will also clear the contents of the file. Store a pointer to this file.
	Write the update line to the write file.
	Iterate over each word in the buffer until we reach a NULL terminator.
	For each word:
		Compare the current word to the needle word (examine).
		If the current word matches the needle word, write the replace word to the file.
		If the current word does not match the needle word, write the current word to the file
		Save the next token in the word variable, and repeat the loop.
	Close the write file.
	Print that we are finished updating
	Exit with status 0

Calculate Average Mark (get_marks()):
	Print the current process id and what is going to happen
	Declare a sum value that is initialised to 0.
	Declare an incrementer variable set to 1.
	Print instructions to the user.
	Loop from 1 to 10 (inclusive):
	Each loop:
		Declare a float to store the input value.
		Print a message to the users.
		Read in from stdin and store the input in the mark variable.
		Add the mark to the sum variable.
		Incremented the incrementer variable.
	Calculate the average by dividing the total sum of numbers by 1 minus the final incrementer value.
	Print the result.
	Exit with status 0.

Word Count (call_wc(char *filename)):
	Print the current process id and what is going to happen
	Create a character array with 3 indicies and a null terminator
	Define the first index to be the name of the program we want to execute
	Define the second index to be the file name passed in as a command line argument
	Define the third index to be '-w' switch that tells wc to only print the word counts.
	Define the final index to be 0 to let execvp know there are no more arguments.
	Call execvp passing "wc" as the program we want to execute, and the character array of arguments defined above.


	

Test Plan:
Test no arguments given:
This should be handled by the program and explain to the user that two filepaths need to be provided.

./build/main

Output:

[ ERROR ] :: Missing required arguments

Test single argument given:
This should be handled by the program and explain to the user that they need to provide another file path.

./build/main readme.txt

Output:

[ ERROR ] :: Missing required arguments

Test three arguments given:
This should be acknowledged by the program, but it should still run as normal after letting the user know extra arguments will be ignored.

./build/main readme.txt afile.txt build.sh

Output:

[ WARNING ] :: Extra arguments have been supplied. Ignoring the following arguments:
Argument 3: build.sh
...


Test file does not exist for word count:
The program should execute normally and allow the wc program to handle the error, which will be reflected in the exit status.

/build/main assignment_descrition.txt afile.txt

Output:

Child 475 here. Will calculate average mark.
Please enter each mark:
(1):
Child 476 here. Will execute command wc.

Here is the output from wc:

Child 477 here. Will update file.
wc: assignment_descrition.txt: No such file or directory
afile.txt has been updated
1
(2):2
(3):3
(4):4
(5):5
(6):6
(7):7
(8):8
(9):9
(10):10
The average mark is 5.50
Average Marks: Child 475 done. The exit status is 0.
Word Count: Child 476 done. The exit status is 1.
Search and Replace: Child 477 done. The exit status is 0.
Parent done

Test file does not exist for update file:
The program should output an error stating the file does not exist and exit with status 1. 

./build/main readme.txt afie.txt

Output: 

Child 509 here. Will calculate average mark.
Please enter each mark:
(1):
Child 510 here. Will execute command wc.

Here is the output from wc:

Child 511 here. Will update file.
[ ERROR ] :: afie.txt : File does not exist
332 readme.txt
1
(2):2
(3):3
(4):4
(5):5
(6):6
(7):7
(8):8
(9):9
(10):10
The average mark is 5.50
Average Marks: Child 509 done. The exit status is 0.
Word Count: Child 510 done. The exit status is 0.
Search and Replace: Child 511 done. The exit status is 1.
Parent done

Limitations:
One of the biggest limitations of this program is the average marks function's ability to verify that the value input is a number. If the user inputs a character or string, the function will fail, and the program will crash.
Name: Alex Griffiths
Student ID: 18001525

Instructions:
To build the program you can run "bash build.sh" which will run my build script. This script just runs the compiler and outputs the executable file to the "build" directory.
Additionally you could also directly call the compiler: "cc src/main.c -o build/main"

To run the program run "./build/main"

Solution Logic:
	buildList() (build_list(IORB *list_root, int length)):
		Create an empty IROB node
		Copy the list root into a new variable to use in a loop.
		Keep looping while the incrementer variable (i) is less that the specified length (length)
		Each time we loop:
			Allocate memory for a new item (IORB node)
			Generate a random number for the base priority of the new item.
			Set the link of the new item to null.
			Use the sprintf function to pass a formatted string into the filler buffer.
			Set the link of the preview node to equal the new item.
			Set the current pointer to equal to the new item.
			Increment the counter.

	displayList() (display_list(IORB* list_root, int(*prio)(int)):
		Copy the list root into a new variable to use in a loop.
		Keep looping while the link of the ptr node is not null. 
		Each loop:
			Use the node linked to by the current node (ptr)
			Output a formated string that displays the base priority, the filler text, and the computer priority.
			The computed priority is determined by passing the linked node's base pri value to a function pointed to by prio.

	sortList(IORB* head, int(*prio)(int)) (sort_list(IORB* list_root, int(*prio)(int))):
		Copy the list root into a new variable that is used for looping over the list.
		While the node pointed at by the link of the pointer (ptr->link) isn't null:
			Copy the current pointer into a variable, which is used to traverse the unsorted nodes of a list.
			Create a new variable that contains the current parent node of the IORB node with the lowest computed base priority in the remaining unsorted nodes.
			While the node pointed at by the link of the current pointer (cur_ptr->link) isn't null:
				Compare the computed priority of the node pointed to by the current pointer with the computed priority of the parent of the current minimum node. This priority is computed by subtracting the base priority from 100.
				If the node pointed to by the current pointer has a lower computed priority then store the current pointer in the cur_min_pointer value.
				Set the current pointer to the next node in the list.

				Pass the ptr to the highest sorted node and cur_min_parent to the move node function.
				Store the node with the minimum computed priorit in min node.
				Check if the min node is the last node in the list by check if it's link point to NULL.
				If the min node is not the last node in the list, set the link of the min_node_parent to the link of the minimum node, fixing the link that is going to be broken by moving the min node.
				Set the link of the min node to be the node pointed to by the current min root.
				Set the link of the min root the the min node.
			Advance the ptr to the next node in the list.	

	Driver Code:
		seed the random number generator
		Check if the number of arguments supplied is greater than 1
			If it is, check if the first argument is "-test" and if it is, run the tests.
			If it isn't, create a pointer to the compute priority function.
			Create an IORB pointer and allocate memory for it.
			Continually ask the user to choose a menu item.
			If they choose 0, terminate the program.
			If they choose 1, build a list of 10 IORB nodes.
			If they choose 2, sort the list of IORB nodes.
			If they choose 3, display all the nodes in the list (with the exception of the root node)
			If they don't choose one of the above options, display an error message.

	Computing Priority (compute_priority(int base)):
		Given an integer that represents a node's base_priority, return 100 - the base priority.

Test Plan:
I have created a test header file which runs a variety of tests which check different cases that I felt should be considered. These test also help me check for any regressions in my code if I change something.

The outcomes of these tests can be seen by running

./build/main -test

The test cases that I considered were:
Does building a list with a length of 0 work without failure, and does it create a list of no nodes (excluding the root node) (build_empty_list())
Does building a list with a length of 1 work without failure, and does it create a list with a single node (excluding the root node) (build_empty_list())
Is the program able to receive an empty list to sort, and execute without error? (empty_node_sort())
Is the program able to receive a list with a single IORB node to sort, and does it execute without error (single_node_sort())
Is the program able to receive a list with only two IORB nodes to sort, and does it execute without error, while also sorting the nodes correctly (two_node_sort())
Is the program able handle a list with two nodes that are next two each other that have the same computed priority and still sort the list without error while also sorting the list correctly. (same_prio_sort())
Is the program able to receive a list with multiple IORB nodes (>2) and sort the list properly without issue (multi_node_sort())
Is the program able to receive a very large list of IROB nodes (>10,000) and still execute without issue - including building and sorting the list. (large_list_sort())

My test code can be found in src/tests.h

Running the program with the following command './build/main -test' has the following output:

[ RUNNING TESTS ]

[ TEST ] build_empty_list          :: OK
[ TEST ] build_single_node_list    :: OK
[ TEST ] empty_node_sort           :: OK
[ TEST ] single_node_sort          :: OK
[ TEST ] two_node_sort             :: OK
[ TEST ] same_prio_sort            :: OK
[ TEST ] multi_node_sort           :: OK
[ TEST ] large_list_sort           :: OK

[ ALL TESTS PASSED ]

Test Logic:
	build_empty_list():
		This function creates a list of 0 nodes using the build list function in the same way the actual program would call it.
		It then runs the list length function which traverses the list counting each node.
		Then the function compares the length of the list to what we expect it to be (which is 0 in this case).
		If the length isn't 0, the function prints a failure message, and returns 0, which will not increment the total counter that checks if all the tests have passed.

	build_single_node_list():
		This function creates a list of 1 node using the build list function in the same way the actual program would call it.
		It then runs the list length function which traverses the list counting each node.
		Then the function compares the length of the list to what we expect it to be (which is 1 in this case).
		If the length isn't 1, the function prints a failure message, and returns 0, which will not increment the total counter that checks if all the tests have passed.

	empty_list_sort():
		This function creates an empty list using the build list function. Checks that it properly built the list by checking it's length, and then runs the sort list function to ensure that the program is able to sort an empty list. It then runs a function that checks if the list is sorted by traversing the list and check that each node is greater than the previous node.

	single_node_sort():
		This function creates a list with a single node  using the build list function. Checks that it properly built the list by checking it's length, and then runs the sort list function to ensure that the program is able to sort a list with just one node. It then runs a function that checks if the list is sorted by traversing the list and check that each node is greater than the previous node.

	two_node_sort():
		This function creates a list with two nodes using the build list function. Checks that it properly built the list by checking it's length, and then runs the sort list function to ensure that the program is able to sort a list with only two nodes. It then runs a function that checks if the list is sorted by traversing the list and check that each node is greater than the previous node.

		This test is mainly used to make sure that the swapping of the nodes works properly and that it handles the minimum node being the last node.

	same_prio_sort():
		This function creates a list with two nodes that both have the same base priority. It then checks to ensure that the program is able to sort a list with nodes that have the same priority. It then runs a function that checks if the list is sorted by traversing the list and check that each node is greater than the previous node.

		This test is mainly used to make sure that the comparison of computed priorites works correctly.

	multi_node_sort():
		This function creates a list with multiple nodes using the build list function. Checks that it properly built the list by checking it's length, and then runs the sort list function to ensure that the program is able to sort a list. It then runs a function that checks if the list is sorted by traversing the list and check that each node is greater than the previous node.

		This test is mainly used to check the typical use case of the program is working properly.

	large_list_sort():
		This function creates a list with multiple nodes using the build list function. Checks that it properly built the list by checking it's length, and then runs the sort list function to ensure that the program is able to sort a list. It then runs a function that checks if the list is sorted by traversing the list and check that each node is greater than the previous node.

		This function is used to check that the function can work with a large amount of data without failing. Ideally there would be a time limit imposed on this test, but I'm not sure what a reasonable time limit would be, and I'm also now sure how large these lists can actually get. I used 30, 000 as the size of my list.

Limitations:
For very large lists >10,000, the execution of the program takes a very long time (possibly even failing, though I have not waited long enough to see any error message)

Additionally, my program can't handle the user inputting a character when selecting an option in the main loop. Doing this will result in the program spamming the terminal with output and can only be cancelled by pressing Ctrl + C.
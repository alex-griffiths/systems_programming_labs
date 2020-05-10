#include <assert.h>

int build_empty_list();
int build_single_node_list();
int empty_list_sort();
int single_node_sort();
int two_node_sort();
int same_prio_sort();
int multi_node_sort();
int large_list_sort();

void run_tests() {
	printf("[ RUNNING TESTS ]\r\n\r\n");
	int (*prio)();
	prio = &compute_priority;
	int passing_count = 0;
	int total_tests = 8;
	
	if(build_empty_list()) {
		printf("[ TEST ] %-25s :: \033[1;32mOK\033[0m\r\n", "build_empty_list");
		passing_count++;
	}
	
	if(build_single_node_list()) {
		printf("[ TEST ] %-25s :: \033[1;32mOK\033[0m\r\n", "build_single_node_list");
		passing_count++;
	}
	
	if(empty_list_sort(prio)) {
		printf("[ TEST ] %-25s :: \033[1;32mOK\033[0m\r\n", "empty_node_sort");
		passing_count++;
	}
	
	if (single_node_sort(prio)) {
		printf("[ TEST ] %-25s :: \033[1;32mOK\033[0m\r\n", "single_node_sort");
		passing_count++;
	}
	
	if (two_node_sort(prio)) {
		printf("[ TEST ] %-25s :: \033[1;32mOK\033[0m\r\n", "two_node_sort");
		passing_count++;
	}
	
	if (same_prio_sort(prio)) {
		printf("[ TEST ] %-25s :: \033[1;32mOK\033[0m\r\n", "same_prio_sort");
		passing_count++;
	}
	
	if (multi_node_sort(prio)) {
		printf("[ TEST ] %-25s :: \033[1;32mOK\033[0m\r\n", "multi_node_sort");
		passing_count++;
	}
	
	if (large_list_sort(prio)) {
		printf("[ TEST ] %-25s :: \033[1;32mOK\033[0m\r\n", "large_list_sort");
		passing_count++;
	}
	
	if(passing_count == total_tests) {
		printf("\r\n\033[1;32m[ ALL TESTS PASSED ]\033[0m\r\n");
	} else {
		printf("\r\n\033[1;31m[ TESTS FAILED ]\033[0m\r\n");
	}
}

// Get the length of the list.
void list_length(IORB *list_root, int *length) {
	IORB *ptr = list_root->link;
	if (list_root->link == NULL) {
		*length = 0;
		return;
	} else if (ptr->link == NULL) {
		*length = 1;
		return;
	}
	
	*length = 0;
	ptr = list_root;
	while (ptr->link != NULL) {
		*length = *length + 1;
		ptr = ptr->link;
	}
}

// Check that a list is actually sorted.
int sorted(IORB *list_root, int (*prio)(int)) {
	IORB *ptr = list_root->link;
	if (list_root->link == NULL) {
		return 1; // An empty list is still a sorted list.
	} 
	if (ptr->link == NULL) {
		return 1; // A single node is still a sorted list.
	}
	
	int min_prio = prio(ptr->link->base_pri);
	while(ptr->link != NULL) {
		if (prio(ptr->base_pri) > prio(ptr->link->base_pri)) {
			return 0;
		} 
		
		// Check if two nodes have identical priorities. If they do, advance the ptr to the next links link.
		if (prio(ptr->base_pri) == prio(ptr->link->base_pri)) {
			if (ptr->link->link != NULL) {
				ptr = ptr->link->link;
			} else {
				ptr = ptr->link;
			}
		} else {
			min_prio = prio(ptr->base_pri);
			ptr = ptr->link;
		}
	}
	
	return 1;
}
// Tests is the program is able to build a list without any nodes, and verifies that by checking the number of nodes in the list.
int build_empty_list() {
	IORB *list_root = (IORB *)malloc(sizeof(IORB));
	build_list(list_root, 0);
	
	int length;
	list_length(list_root, &length);
	if (length != 0) {
		printf("[ TEST ] %-25s :: \033[1;31mFAIL\033[0m - Invalid Length\r\n", "build_empty_list");
		return 0;
	}
	
	return 1;
}

// Tests if the program is able to build a list with only a single node, and verifies that by checking the number of nodes in the list.
int build_single_node_list() {
	IORB *list_root = (IORB *)malloc(sizeof(IORB));
	build_list(list_root, 1);
	
	int length;
	list_length(list_root, &length);
	if (length != 1) {
		printf("[ TEST ] %-25s :: \033[1;31mFAIL\033[0m - Invalid Length\r\n", "build_single_node_list");
		return 0;
	}
	
	return 1;
}

// Tests the programs handling of an empty list.
// Checks the the length of the list is 0 as expected
// Checks the list is considered sorted as expected.
int empty_list_sort(int(*prio)(int)) {
	IORB *list_root = (IORB *)malloc(sizeof(IORB));
	build_list(list_root, 0);
	// Check length of list.
	int length;
	list_length(list_root, &length);
	if(length == 1) {
		printf("[ TEST ] %-25s :: \033[1;31mFAIL\033[0m - Invalid Length\r\n", "empty_node_sort");
		return 0;
	}
	
	// Check order of list.
	sort_list(list_root, (*prio));
	if(!sorted(list_root, prio)){
		printf("[ TEST ] %-25s :: \033[1;31mFAIL\033[0m - Sort Failed\r\n", "empty_node_sort");
		return 0;
	}
	
	return 1;
}

// Tests the programs handling of a list with a single node (excluding the head)
// Checks the list is considered sorted as expected
int single_node_sort(int (*prio)(int)) {
	IORB *list_root = (IORB *)malloc(sizeof(IORB));
	build_list(list_root, 1);
	
	// Check order of list.
	sort_list(list_root, (*prio));
	if (!sorted(list_root, prio)) {
		printf("[ TEST ] %-25s :: \033[1;31mFAIL\033[0m - Sort Failed\r\n", "single_node_sort");
		return 0;
	}
	
	return 1;
}

// Tests the programs handling of a list with 2 nodes (excluding the head)
// Checks that the list is considered sorted, and sorts correctly as expected
int two_node_sort(int (*prio)(int)) {
	IORB *list_root = (IORB *)malloc(sizeof(IORB));
	build_list(list_root, 2);
	
	// Check order of list.
	sort_list(list_root, (*prio));
	if (!sorted(list_root, prio)) {
		printf("[ TEST ] %-25s :: \033[1;31mFAIL\033[0m - Sort Failed\r\n", "two_node_sort");
		return 0;
	}
	
	return 1;
}

// Tests the programs handling of a list with 2 nodes (excluding the head) that have 
// the same priority 
// Checks the length of the list is 2 as expected
// Checks that the list is considered sorted, and sorts correctly as expected
int same_prio_sort(int (*prio)(int)) {
	IORB *list_root = (IORB *)malloc(sizeof(IORB));
	
	IORB *ptr = (IORB *)malloc(sizeof(IORB));
	IORB *ptr2 = (IORB *)malloc(sizeof(IORB));
	
	// Fill ptr
	sprintf(ptr->filler, "Test content");
	ptr->base_pri = 50;
	ptr->link = ptr2;
	
	// Fill ptr2
	sprintf(ptr2->filler, "Test content 2");
	ptr2->base_pri = 50;
	ptr2->link = NULL;
	
	list_root->link = ptr;
	// Check order of list.
	sort_list(list_root, (*prio));
	if (!sorted(list_root, (*prio))) {
		printf("[ TEST ] %-25s :: \033[1;31mFAIL\033[0m - Sort Failed\r\n", "same_prio_sort");
		return 0;
	}
	
	return 1;
}

int multi_node_sort(int (*prio)(int)) {
	IORB *list_root = (IORB *)malloc(sizeof(IORB));
	build_list(list_root, 10);
	sort_list(list_root, (*prio));
	if (!sorted(list_root, (*prio))) {
		printf("[ TEST ] %-25s :: \033[1;31mFAIL\033[0m - Sort Failed\r\n", "multi_node_sort");
		return 0;
	}
	return 1;
}

int large_list_sort(int (*prio)(int)) {
	IORB *list_root = (IORB *)malloc(sizeof(IORB));
	build_list(list_root, 30000);
	sort_list(list_root, (*prio));
	if (!sorted(list_root, (*prio))) {
		printf("[ TEST ] %-25s :: \033[1;31mFAIL\033[0m - Sort Failed\r\n", "large_list_sort");
		return 0;
	}
	return 1;
}
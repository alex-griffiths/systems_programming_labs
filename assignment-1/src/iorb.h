#ifndef IORB_H_
#define IORB_H_

typedef struct iorb {
	int base_pri;
	struct iorb *link;
	char filler[100];
} IORB;

// Moves the minimum node to the required position and repairs any broken links that
// arise as a result of moving the node.
void move_node(IORB *min_root, IORB *min_node_parent) {
	// We pass the parent node of the minimum node in the unsorted portion of the list, so this is how we get the actual minimum node.
	IORB *min_node = min_node_parent->link; 
	
	// Check if the minimum node is the last node in the list.
	if (min_node->link == NULL) { 
		// Set the parent node's link to NULL because it is now the last node.
		min_node_parent->link = NULL;
	} else {
		// Fix the severed link between the parent node and the min nodes' child
		// node.
		min_node_parent->link = min_node->link;
	}
	
	// Make the child node of the min root the child of the min node, and then make
 // the min node the child of the min root.
	min_node->link = min_root->link;
	min_root->link = min_node;
}

// This function traverses the list and outputs the values in each node.
// Because the head node isn't part of the actual list and is instead just there
// to be an access node into the list, we don't want to print anything from it
// So we start from it's link.
void display_list(IORB *list_root, int (*prio)(int)) {
	IORB *ptr = list_root;
	while(ptr->link != NULL){
		// %-3d just makes sure that our input is always aligned nicely by
		// padding up to 3 digits as required.
		printf("Base Pri: %-3d | Filler: %s | Priority: %d \r\n", ptr->link->base_pri, ptr->link->filler, prio(ptr->link->base_pri));
		
		// Advance the pointer.
		ptr = ptr->link;
	}
}

// This function performs a selection sort to sort the list in ascending order.
// It selects the smallest node out of the unsorted portion of the list, and moves it
// to the end of the sorted portion of the list.

// It does this until it reaches the end of the list, at which point it should have a
// produced a sorted list.
void sort_list(IORB *list_root, int (*prio)(int)) {
	IORB *ptr = list_root;
	
	while(ptr->link != NULL) {
		IORB *cur_ptr = ptr;
		IORB *cur_min_parent = ptr; // ptr is always the highest sorted position.
		
		while (cur_ptr->link != NULL) {
			// Compare unsorted nodes to find the minimum value in the list of
			// unsorted nodes.
			if(prio(cur_ptr->link->base_pri) < prio(cur_min_parent->link->base_pri)) {
				// Store parent node of the current minimum. 
				cur_min_parent = cur_ptr;
			}
			
			// Advance the current ptr;
			cur_ptr = cur_ptr->link;
		}
		
		// Run the move node function.
		move_node(ptr, cur_min_parent);
		// Advance the ptr. This will now be moving the ptr to the highest sorted
		// node.
		ptr = ptr->link;
	}
}

void build_list(IORB *list_root, int length) {
	// Create a new empty node. This will be filled in the first pass through the
 // loop.
	IORB* new_item;
	// This becomes the head of our list, and we append items to it bellow.
	IORB* cur_ptr = list_root;
	
	// Loop from 0 to the specified length, creating a new node each time and
 // inserting it at the end of the list.
	int i = 0;
	while(i < length) {
		// Create node and fill it with data.
		new_item = (IORB *)malloc(sizeof(IORB));
		new_item->base_pri = rand() % 100;
		new_item->link = NULL;
		sprintf(new_item->filler, "this is i/o request %d", i);
		
		// We set the link of the current pointer to the new item
		cur_ptr->link = new_item;
		// We set the current pointer to the new item so that doing the above step
		// doesn't cause a circular loop.
		cur_ptr = new_item;
		
		i++;
	}
}
#endif
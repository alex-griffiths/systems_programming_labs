#ifndef IORB_H_
#define IORB_H_

typedef struct iorb {
	int base_pri;
	struct iorb *link;
	char filler[100];
} IROB;


// Pass a function pointer
void sort_list(iorb *list_head) {
	
}
#endif
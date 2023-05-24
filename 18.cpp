#include <iostream>
#include <math.h>

using namespace std;

struct stack {
	int data;
	int * arr;
	int head;
};


struct stack * createStack(int disk) {								// creating poles with memory
	stack * n = (stack*)malloc(sizeof(stack));
	n->data = disk;
	n->arr = (int*)malloc(n->data * sizeof(int));
	n->head = -1;
	return n;
}

void push(struct stack* pole, int data) {								// function to push disks into poles
	if (pole->head == pole->data - 1)
		return;
	pole->arr[++pole->head] = data;
}

int pop(struct stack* pole) {										// function to pop disks from poles
	if (pole->head == -1)
		return -1;
	return pole->arr[pole->head--];
}

void movedisk(struct stack * spole, struct stack* dpole, char s, char d) {			// function to execute legal shift of disks
	int val1 = pop(spole);
	int val2 = pop(dpole);
	if (val1 == -1) {																// if source pole is empty
		push(spole, val2);
		printf("Disk %d shifted from %c to %c\n", val2, d, s);
	}
	else if (val2 == -1) {															// if destination pole is empty
		push(dpole, val1);
		printf("Disk %d shifted from %c to %c\n", val1, s, d);
	}
	else if (val1 > val2) {															// if source pole has larger disk
		push(spole, val1);
		push(spole, val2);
		printf("Disk %d shifted from %c to %c\n", val2, d, s);
	}
	else {																			// if source pole has smaller disk
		push(dpole, val2);
		push(dpole, val1);
		printf("Disk %d shifted from %c to %c\n", val1, s, d);
	}
}

void toh(int disks, struct stack* spole, struct stack* apole, struct stack* dpole) {			// function to determine order of shifts
	int moves;
	char dest = 'D', src = 'S', aux = 'A', temp;
	if (disks % 2 == 0) {																		// swap auxillary and destination disks if disks is even
		temp = dest;
		dest = aux;
		aux = temp;
	}
	moves = pow(2, disks) - 1;																	// number of moves to shift all disks
	for (int i = 1; i <= moves; i++) {
		if (i % 3 == 1)
			movedisk(spole, dpole, src, dest);
		else if (i % 3 == 2)
			movedisk(spole, apole, src, aux);
		else if (i % 3 == 0)
			movedisk(apole, dpole, aux, dest);
	}
}

int main() {
	struct stack * spole = NULL;																// initializing poles (stacks)
	struct stack * apole = NULL;
	struct stack * dpole = NULL;
	
	int disks;
	cout << "Enter number of disks: ";
	cin >> disks;
	spole = createStack(disks);																	// allocating memory for disks in stacks
	apole = createStack(disks);
	dpole = createStack(disks);
	for (int i = disks; i > 0; i--) {
		push(spole, i);																			// inserting disks into source pole
	}
	
	toh(disks, spole, apole, dpole);
	return 0;
}
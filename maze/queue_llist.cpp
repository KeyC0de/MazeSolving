#include <cstdio>
#include <cstdlib>
#include "queue_llist.h"


void initQueue(Queue *Q)
{
	Q->head = 0;
	Q->tail = 0;
	Q->size = 0;
}

int isEmpty(Queue *Q) { return Q->head == 0; }
int getQSize(Queue *Q) { return Q->size; }

// enqueue node at the end of the Queue
void enqueue(qType val, Queue *Q)
{
	Node *temp = (Node *)malloc(sizeof(Node));

	temp->value = val;
	temp->next = NULL;

	if (isEmpty(Q)) { // if Queue is empty
		Q->head = temp;
		Q->tail = temp;
	}
	else { // otherwise, insert new Node last and make it the tail node
		Q->tail->next = temp;
		Q->tail = temp;
	}
	Q->size++;
}

// dequeue the node from the head of the Queue
qType dequeue(Queue *Q)
{
	if (isEmpty(Q)) {
		printf("Attempt to remove value from an empty Queue - EPIC FAIL.\n");
		return {};
	}
	
	Node *temp = Q->head;		// holds the head Node of the Queue
	Q->head = Q->head->next;	// make the second Node the head Node of the Queue

	qType tempVal = temp->value;
	// Clear and free the first Node of the Queue
	temp->next = NULL;
	temp = NULL;
	free(temp);

	Q->size--;

	if (isEmpty(Q)) // If there was no other Node initialize the Queue
		initQueue(Q);

	return tempVal;
}

// returns value of head Node
qType peek(Queue *Q)
{
	if (!isEmpty(Q))
		return Q->head->value;
	
	return {};
}

// prints all values in the Queue (linked list)
void printLinkedQueue(Queue *Q)
{
	if (isEmpty(Q)) {
		printf("Queue is empty\n");
		return;
	}
	else {
		Node *temp = Q->head; // iterate through the Queue
		for (temp = Q->head; temp != NULL; temp = temp->next)
			printf("%c ", temp->value.ch);
	}
}

/*
int main(void)
{
	qType in, out;
	Queue Q;

	initQueue(&Q);

	for (int i = 1; i<=10; ++i) {
		in = 'a' + i - 1;
		enqueue(in, &Q);
	}

	out = peek(&Q);
	printf("Value %c has been removed.\n", out);

	printLinkedQueue(&Q);
}
*/

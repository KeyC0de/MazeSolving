#ifndef QUEUELLISTIMPL_H // Include guards
#define QUEUELLISTIMPL_H

typedef struct qType {
	char ch;
	size_t horizCoord;
	size_t vertCoord;
	_Bool visited;
	_Bool inPath;
} qType; // the storage type can be arbitrary

typedef struct Node {
	qType value;
	struct Node *next;
} Node;

typedef struct Queue {
	Node *head;
	Node *tail;
	int size;
} Queue;

// Function Declarations
void initQueue(Queue *Q);
int isEmpty(Queue *Q);
void enqueue(qType val, Queue *Q);
qType dequeue(Queue *Q);
int getQSize(Queue *Q);
qType peek(Queue *Q);

#endif // QUEUELLISTIMPL_H

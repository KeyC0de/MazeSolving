#pragma once


struct qType
{
	char ch;
	size_t horizCoord;
	size_t vertCoord;
	bool visited;
	bool inPath;
};// the storage type can be arbitrary

struct Node
{
	qType value;
	struct Node *next;
};

struct Queue
{
	Node *head;
	Node *tail;
	int size;
};

// Function Declarations
void initQueue(Queue *Q);
int isEmpty(Queue *Q);
void enqueue(qType val, Queue *Q);
qType dequeue(Queue *Q);
int getQSize(Queue *Q);
qType peek(Queue *Q);

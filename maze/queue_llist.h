#pragma once

#ifndef QUEUELLISTIMPL_H // Include guards
#define QUEUELLISTIMPL_H

 // the storage type can be arbitrary
typedef int qType;

typedef struct QNode {
	qType value;
	struct QNode *next;
} QNode;

typedef struct Queue {
	QNode *head;
	QNode *tail;
	int size;
} Queue;

// Function Declarations
void initQueue(Queue *Q);
int isQEmpty(Queue *Q);
void enqueue(qType val, Queue *Q);
qType dequeue(Queue *Q);
int getQSize(Queue *Q);
qType peek(Queue *Q);
void printLinkedQueue(Queue *Q);

#endif // QUEUELLISTIMPL_H
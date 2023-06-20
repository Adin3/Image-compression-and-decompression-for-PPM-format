/*NEACSU ADRIAN - 314CD*/

#include "tree.h"

// Structura pentru coada
typedef struct queueNode{
	Tree* tree;
	struct queueNode *next;
	struct queueNode *prev;
}queueNode;

typedef struct Queue{
	queueNode* head;
}Queue;

// initializeaza coada
extern Queue* createQueue();

// dealoca coada
extern void destroyQueue(Queue* queue);

// adauga un nod nou in coada
extern void enqueue(Queue* queue, Tree* tree);

// sterge primul nod din coada
extern void dequeue(Queue* queue);

// verifica daca coada e goala
extern int isQueueEmpty(Queue *queue);

// returneaza primul element din coada
extern Tree* front(Queue* queue);

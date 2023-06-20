/*NEACSU ADRIAN - 314CD*/

#include "queue.h"

extern Queue* createQueue(void){
	Queue* queue = (Queue*) malloc(sizeof(Queue));
	queue->head = (queueNode*) malloc(sizeof(queueNode));
	queue->head->next = queue->head->prev = queue->head;
	return queue;
}
extern void destroyQueue(Queue* queue){
	queueNode* it = queue->head->next;
	while(it != queue->head){
		queueNode* aux = it;
		it = it->next;
		free(aux);
	}
	free(queue->head);
	free(queue);
}
extern int isQueueEmpty(Queue *queue){
	return queue->head->next == queue->head;
}

extern void enqueue(Queue* queue, Tree* tree){
	queueNode* newNode = (queueNode*) malloc(sizeof(queueNode));
	newNode->tree = tree;

	newNode->next = queue->head->next;
	newNode->prev = queue->head;

	queue->head->next->prev = newNode;
	queue->head->next = newNode;
}

extern void dequeue(Queue* queue){
	queueNode* aux = queue->head->prev;
	queue->head->prev = queue->head->prev->prev;
	queue->head->prev->next = queue->head;
	free(aux);
}

extern Tree* front(Queue* queue){
	return queue->head->prev->tree;
}

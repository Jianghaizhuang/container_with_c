#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#define false 0
#define true 1
#define bool int
typedef struct Node {
	int val;
	struct Node* next;
}Node;

typedef struct Queue {
	struct Node* head;
	struct Node* tail;
}Queue;
Node* createNode(int v) {
	Node* ptr = (Node*)malloc(sizeof(Node));
	if (!ptr) {
		printf("内存空间不足");
		return NULL;
	}
	ptr->val = v;
	ptr->next = NULL;
	return ptr;
}

Queue* createQueue() {
	Queue* ptr = (Queue*)malloc(sizeof(Queue));
	if (!ptr) {
		printf("内存空间不足");
		return  NULL;
	}
	ptr->head = NULL;
	ptr->tail = NULL;
	return ptr;
}
void pushQueue(Queue* q,int val) {
	Node* ptr = createNode(val);
	if (q->head == NULL) {
		q->head = ptr;
		q->tail = ptr;
	}
	else {
		q->tail->next = ptr;
		q->tail = ptr;
	}
}
int popQueue(Queue* q) {
	if (q->head == NULL) {
		printf("队列空");
		return -1;
	}
	int val;
	if (q->head == q->tail) {
		val = q->head->val;
		free(q->head);
		q->head = NULL, q->tail = NULL;
	}
	else {
		val = q->head->val;
		Node* tmp = q->head->next;
		free(q->head);
		q->head = tmp;
	}
	return val;
}
bool isEmptyQueue(Queue* q) {
	if (!q->head) {
		return true;
	}
	return false;
}
int getQueueVal(Queue* q) {
	if (!q->head) {
		printf("队列空");
		return -1;
	}
	return q->head->val;
}
void destroyNode(Node* head, Node* tail) {
	if (head == tail) {
		free(head);
		return;
	}
	destroyNode(head->next, tail);
	free(head);
}

void destroyQueue(Queue* q) {
	destroyNode(q->head, q->tail);
    free(q);
}

int main()
{
	Queue* que = createQueue();
	for (int i = 0; i < 10; i++)
		pushQueue(que, i);	
	while (!isEmptyQueue(que))
		printf("%d,", popQueue(que));
	destroyQueue(que);
	return 0;
}
#include <stdlib.h>
#include <stdio.h>

struct queueNode;
struct queue {
	struct queueNode *first;
	int size;
};

struct queueNode {
	void *data;
	// struct queueNode *prev;
	struct queueNode *next;
};

struct queue *
queueInit()
{
	struct queue *tmp = (struct queue *) malloc(sizeof(struct queue));
	tmp->first = NULL;
	tmp->size = 0;
	return tmp;
}

void
queueAdd(struct queue *ptr, void *data)
{
	if (ptr->first == NULL) {
		struct queueNode *tmp = (struct queueNode *) malloc(sizeof(struct queueNode));
		tmp->data = data;
		tmp->next = NULL;
		ptr->first = tmp;
		ptr->size = 1;
	} else {
		struct queueNode *tmp = ptr->first;
		while (tmp->next) {
			tmp = tmp->next;
		}
		tmp->next = (struct queueNode *) malloc(sizeof(struct queueNode));
		(tmp->next)->data = data;
		(tmp->next)->next = NULL;
		ptr->size++;
	}
}

void *
queueShift(struct queue *ptr)
{
	if (ptr->size > 0) {
		struct queueNode *tmp = (ptr->first)->next;
		void *data = (ptr->first)->data;
		free(ptr->first);
		ptr->first = tmp;
		ptr->size--;
		return data;
	} else {
		return NULL;
	}
}

void 
queueFree(struct queue *ptr)
{
	struct queueNode *tmp = ptr->first;
	while (tmp) {
		tmp = tmp->next;
		free(ptr->first);
		ptr->first = tmp;
	}
	free(ptr);
}

int
queueSize(struct queue *ptr)
{
	return ptr->size;
}

int
main(int argc, char **argv)
{
	struct queue *q = queueInit();
	queueAdd(q, "Hello world");
	queueAdd(q, "Gooddam");
	printf("queue size is %d\n", queueSize(q));
	printf("%s\n", queueShift(q));
	printf("%s\n", queueShift(q));
	queueShift(q);
	printf("queue size is %d\n", queueSize(q));
}

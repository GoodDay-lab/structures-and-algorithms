/*	It's too bad that in C not a templates like in C++
 * 	But, there's a powerfull var casting.. That saves
 */

/*	At forum one programmer provided an idea to make an queue over array.
 *	I did it, the strongest advantage is a using with minimal heap memory, you shouldn't 
 *	malloc and free a elements every call of function. It does at init and exit.
 * */

#include <stdlib.h>
#include <stdio.h>

typedef struct {
	int empty;
	int size;
	void **array;
	int first, last;
} Queue;

Queue *
queueInit(int size)
{
	Queue *tmp = (Queue *)malloc(sizeof(Queue));
	tmp->size = size;
	tmp->empty = 1;
	tmp->array = (void **)malloc(sizeof(void *) * tmp->size);
	tmp->first = tmp->last = 0;
}

void
enqueue(Queue *ptr, void *data)
{
	if (!ptr->empty && ptr->first == ptr->last) { 
		printf("[Queue INFO] This queue is overweight\n");
		return;
   	}  // This a block of overwriting
	(ptr->array)[ptr->last] = data;
	ptr->last = (ptr->last + 1) % ptr->size;
	ptr->empty = 0;
}

void *
dequeue(Queue *ptr)
{
	if (ptr->empty) { 
		printf("[Queue INFO] This queue is empty\n");
		return NULL;
   	}
	void *data = (ptr->array)[ptr->first];
	ptr->first = (ptr->first + 1) % ptr->size;
	ptr->empty = ptr->first == ptr->last;
	return data;
}

void
rmqueue(Queue *ptr)
{
	free(ptr->array);
	free(ptr);
}

int main()
{
	Queue *q = queueInit(3);
	enqueue(q, "Hello world");
	enqueue(q, "Bad guy");
	enqueue(q, "Good guy");
	enqueue(q, "bug");
	printf("%s\n", dequeue(q));
	printf("%s\n", dequeue(q));
	dequeue(q);
	dequeue(q);
}

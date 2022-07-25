#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

struct stackNode;
struct stack {
	struct stackNode *first;
	int size;
};

struct stackNode {
	void *data;
	struct stackNode *next;
};

struct stack *
init()
{
	struct stack *tmp = (struct stack *) malloc(sizeof(struct stack));
	tmp->size = 0;
	tmp->first = NULL;
	return tmp;
}

void 
push(struct stack *ptr, void *data)
{
	struct stackNode *tmp = (struct stackNode *) malloc(sizeof(struct stackNode));
	tmp->next = ptr->first;
	ptr->first = tmp;
	tmp->data = data;
	ptr->size++;
}

void *
pop(struct stack *ptr)
{
	if (ptr->size > 0) {
		struct stackNode *tmp = (ptr->first)->next;
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
freeStack(struct stack *ptr)
{
	if (!ptr) return;
	struct stackNode *tmp = ptr->first;
	while (tmp) {
		ptr->first = (ptr->first)->next;
		free(tmp);
		tmp = ptr->first;
	}
	free(ptr);
}


int main() 
{
	struct stack *p = init();
	push(p, "Hello world");
	push(p, "Bad guy... Duh!");
	char *data = (char *)pop(p);
	printf("%s\n", data);
}

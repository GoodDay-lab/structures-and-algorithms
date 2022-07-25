#include <stdlib.h>
#include <stdio.h>

struct hashtableNode;
struct hashtable {
	int size;
	struct hashtableNode *array;
};

struct hashtableNode {
	int deleted;
	void *data;
};

unsigned int 
hash1(char *key, int size)
{
	int summary = 0;
	char *tmp = key;
	while (*tmp) {
		summary += *tmp;
		tmp++;
	}
	return summary % size;
}

unsigned int
hash2(char *key, int size)
{
	return 3;
}

struct hashtable *
hashtableInit(int size)
{
	struct hashtable *tmp = (struct hashtable *) malloc(sizeof(struct hashtable));
	tmp->size = size;
	tmp->array = malloc(sizeof(struct hashtableNode) * size);
}

void
hashtableAdd(struct hashtable *ptr, char *keyword, void *data)
{
	unsigned int hash1v = hash1(keyword, ptr->size);
	((ptr->array)[hash1v]).data = data;
	((ptr->array)[hash1v]).deleted = 0;
}

void *
hashtableGet(struct hashtable *ptr, char *keyword)
{
	unsigned int hash1v = hash1(keyword, ptr->size);
	return ((ptr->array)[hash1v]).data;
}

void
hashtableDelete(struct hashtable *ptr, char *keyword)
{
	unsigned int hash1v = hash1(keyword, ptr->size);
	((ptr->array)[hash1v]).deleted = 1;
}

void 
hashtableFree(struct hashtable *ptr)
{
	free(ptr->array);
	free(ptr);
}


int
main()
{
	struct hashtable *h = hashtableInit(100);
	hashtableAdd(h, "key1", "My friend is Dhamer");
	hashtableAdd(h, "little", "Goddam! That's so easy!");
	hashtableAdd(h, "kids", "Game");
	printf(hashtableGet(h, "key1"));
}

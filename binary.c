#include <stdlib.h>
#include <stdio.h>
#include <time.h>

struct bintreeNode;
struct bintree {
	struct bintreeNode *first;
	int size;
};

struct bintreeNode {
	int index;
	void *data;
	struct bintreeNode *left, *right;
};

struct bintree *
bintreeInit()
{
	struct bintree *tmp = (struct bintree *) malloc(sizeof(struct bintree));
	tmp->first = NULL;
	tmp->size = 0;
	return tmp;
}

void
bintreeAdd(struct bintree *ptr, int index, void *data)
{
	struct bintreeNode *tmp;
	if (ptr->first == NULL) {
		tmp = (struct bintreeNode *) malloc(sizeof(struct bintreeNode));
		ptr->first = tmp;
		tmp->index = index;
		tmp->data = data;
		tmp->left = tmp->right = NULL;
		ptr->size = 1;
	} else {
		tmp = ptr->first;
		while (tmp) {
			if (index > tmp->index) {
				if (!tmp->right) {
					tmp->right = (struct bintreeNode *) malloc(sizeof(struct bintreeNode));
					(tmp->right)->index = index;
					(tmp->right)->data = data;
					(tmp->right)->left = (tmp->right)->right = NULL;
					ptr->size++;
					return;
				};
				tmp = tmp->right;
			} else if (index < tmp->index) {
				if (!tmp->left) {
					tmp->left = (struct bintreeNode *) malloc(sizeof(struct bintreeNode));
					(tmp->left)->index = index;
					(tmp->left)->data = data;
					(tmp->left)->left = (tmp->left)->right = NULL;
					ptr->size++;
					return;
				};
				tmp = tmp->left;
			} else {
				tmp->data = data;
				return;
			}
		}
	}
}

void *
bintreeGet(struct bintree *ptr, int index)
{
	struct bintreeNode *tmp = ptr->first;
	while (tmp) {
		if (index > tmp->index) {
			tmp = tmp->right;
		} else if (index < tmp->index) {
			tmp = tmp->left;
		} else {
			return tmp->data;
		}
	}
	if (tmp) {
		return tmp->data;
	} else {
		return NULL;
	}
}

void
bintreeFree(struct bintree *ptr)
{
	void bintreeNodeFree(struct bintreeNode *root)
	{
		if (root->left) { bintreeNodeFree(root->left); }
		if (root->right) { bintreeNodeFree(root->right); }
		free(root);
	}
	
	ptr->size = 0;
	bintreeNodeFree(ptr->first);
	free(ptr);
}

int
main()
{
	struct bintree *b = bintreeInit();
	int number = 10;
	bintreeAdd(b, 4, "Hello world");
	bintreeAdd(b, 40, "Bye");
	bintreeAdd(b, 2, &number);
	bintreeAdd(b, 4, "Bitmaker");
	printf("%d\n", *((int *)bintreeGet(b, 2)));
	printf("%s\n", bintreeGet(b, 4));
}

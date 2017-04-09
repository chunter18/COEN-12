#include "tree.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

typedef struct tree{
	int data;
	struct tree *parent;
	struct tree *left;
	struct tree *right;
}tree;

tree *createTree(int data, tree *left, tree *right)
{
	tree *tp;
	tp = (tree*)malloc(sizeof(tree));
	assert(tp != NULL);
	
	tp->parent = NULL;
	tp->data = data;

	if(left == NULL)
		tp->left = left;
	else
		setLeft(tp, left);

	if(right == NULL)
		tp->right = right;
	else
		setRight(tp, right);
	
	return(tp);
}

void destroyTree(tree *root)
{

	if(root != NULL)
	{
		destroyTree(root->left);
		destroyTree(root->right);
		free(root);
	}
	return;	
}

int getData(tree *root)
{
	assert(root != NULL);
	return(root->data);
}

tree *getLeft(tree *root)
{
	assert(root != NULL);
	return(root->left);
}

tree *getRight(tree *root)
{
	assert(root != NULL);
	return(root->right);
}

tree *getParent(tree *root)
{
	assert(root != NULL);
	return(root->parent);
}

void setLeft(tree *root, tree *left)
{

	assert(root != NULL && left != NULL);
	root->left = left;
	left->parent = root;
	return;

}

void setRight(tree *root, tree *right)
{

	assert(root != NULL && right != NULL);
	root->right = right;
	right->parent = root;
	return;
}


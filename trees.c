#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "trees.h"

Node *init_node(int *data, int *memoryMalloc)
{
	Node *node = malloc(sizeof(Node));
	if (NULL == node)
	{
		printf("Error allocation memory");
		return NULL;
	}
	else
	{
		(*memoryMalloc)++;
		node->data = data;
		node->left = NULL;
		node->right = NULL;
		node->parent = NULL;
		node->color = BLACK;
		return node;
	}
}

Node *insert_newNode(int *data, Node *node, int *memoryMalloc)
{
	if (NULL == node)
	{
		return init_node(data, memoryMalloc);
	}

	Node *newNode = malloc(sizeof(Node));
	if (NULL == newNode)
	{
		printf("Error allocation memory");
		return NULL;
	}
	(*memoryMalloc)++;
	newNode->data = data;
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->parent = NULL;
	newNode->color = RED;

	Node *current = node;
	Node *parent = NULL;

	while (NULL != current)
	{
		parent = current;
		if (*(newNode->data) < *(current->data))
		{
			current = current->left;
		}
		else
		{
			current = current->right;
		}
	}

	newNode->parent = parent;
	if (NULL == parent)
	{
		return newNode;
	}
	else if (*data < *(parent->data))
	{
		parent->left = newNode;
		change_color(newNode);
	}
	else
	{
		parent->right = newNode;
		change_color(newNode);
	}

	return newNode;
}

void free_node(Node *node, int *memoryMalloc)
{
	if (node == NULL)
	{
		return;
	}
	free_node(node->left, memoryMalloc);
	free_node(node->right, memoryMalloc);
	free(node);
	(*memoryMalloc)--;
}

Color change_color(Node *newNode)
{
	if (newNode->parent->color == BLACK)
	{
		newNode->color = RED;
	}
	else
	{
		newNode->color = BLACK;
	}
}

int rootToLeftLeaf(Node *root, int *totalNode, int *numLeftBlack)
{
	if (NULL == root)
	{
		return 1;
	}

	Node *current = root->left;

	if (NULL != current)
	{
		while (NULL != current->left)
		{
			if (BLACK == current->color)
			{
				(*numLeftBlack)++;
			}
			(*totalNode)++;
			printf("Node data %d & node color %d\n", *(current->data), current->color);
			current = current->left;
		}
	}
	return 0;
}

void delete_node(Node *root, int *data)
{
	Node *current = root;
	Node *parent = NULL;

	if (NULL == current->left && NULL == current->right && *data == (*current->data))
	{
		free(current);
	}

	while (NULL != current && *data != *(current->data))
	{
		parent = current;
		if (*(current->data) < *data)
		{
			current = current->right;
		}
		else
		{
			current = current->left;
		}
	}
	if (NULL == current)
	{
		printf("Node not found");
		return;
	}

	if (NULL != current->left && NULL != current->right)
	{
		Node *successor = current->right;
		Node *successor_parent = current;

		while (NULL != successor->left)
		{
			successor_parent = successor;
			successor = successor->left;
		}

		current->data = successor->data;

		if (successor_parent != current)
			successor_parent->left = successor->right;
		else
			successor_parent->right = successor->right;

		free(successor);
	}
	else
	{
		Node *child = (NULL != current->left) ? current->left : current->right;

		if (NULL == parent)
		{
			root = child;
		}
		else if (current == parent->left)
		{
			parent->left = child;
		}
		else
		{
			parent->right = child;
		}
		if (NULL != child)
		{
			child->parent = parent;
		}
		free(current);
	}
}

#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum
{
	RED,
	BLACK
} Color;
typedef struct Node Node;

struct Node
{
	int *data;
	Color color;
	Node *left;
	Node *right;
	Node *parent;
};

Node *init_node(int *data, int *memoryMalloc);
Node *insert_newNode(int *data, Node *node, int *memoryMalloc);
void free_node(Node *node, int *memoryMalloc);
Color change_color(Node *newNode);
int rootToLeftLeaf(Node *root, int *totalNode, int *numLeftBlack);
void delete_node(Node *root, int *data);
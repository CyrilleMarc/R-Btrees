#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "trees.h"

int main()
{
	int data = 100;
	int i, size = 0;
	int numLeftBlack = 0;
	int numRightBlack = 0;
	int memoryMalloc = 0;
	int totalNode = 0;
	int numOfNode = 12;
	int newData[] = {12, 953, 56, 365, 999, 6523, 3214};
	size = sizeof(newData) / sizeof(int);
	Node *root = init_node(&data, &memoryMalloc);

	if (NULL != root)
	{
		printf("Root initialized successfully\n");
		printf("root data = %d\n", *(root->data));
		printf("root color = %d\n", root->color);

		for (i = 0; i < size; i++)
		{
			Node *newNode = insert_newNode(&newData[i], root, &memoryMalloc);

			if (NULL != newNode)
			{
				printf("******************************\n");
				printf("New node inserted successfully\n");
				printf("New node data: %d\n", *(newNode->data));
				if (NULL != newNode->right)
				{
					printf("New node right: %d\n", *(newNode->right->data));
				}
				if (NULL != newNode->left)
				{
					printf("New node left : %d\n", *(newNode->left->data));
				}
				printf("New node color: %d\n", newNode->color);
				printf("New node parent %d\n", *(newNode->parent->data));
				printf("******************************\n");
			}
			else
			{
				printf("Failed to insert new node\n");
			}
		}
	}
	else
	{
		printf("Failed to initialize root node\n");
	}

	rootToLeftLeaf(root, &totalNode, &numLeftBlack);
	printf("number of leftBranchNodeBlack -> %d\n", numLeftBlack);
	printf("\n");
	printf("size of newData->%d\n", size);
	printf("\n");

	delete_node(root, &numOfNode);
	printf("size of newData->%d\n", size);
	for (i = 0; i < size; i++)
	{
		printf("newData content -> %d\n", newData[i]);
	}

	free_node(root, &memoryMalloc);
	printf("remaining allocated memory  = %d\n", memoryMalloc);
	if (0 == memoryMalloc)
		printf("Memory is empty\n");
	else
	{
		printf("persistent memory leaks\n");
	}

	return 0;
}

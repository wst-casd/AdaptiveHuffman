#ifndef _ADAPTIVEHUFFMAN_H
#define _ADAPTIVEHUFFMAN_H

typedef struct Node_AHuf
{
	short	lchild, rchild, parent;
	char		element;
	char		isleaf;
	int		weight;
}AHufNode;


void initTree(AHufNode *tree, int *ind);

void split(AHufNode *tree, int *_0_Ind, int *curPos, const char sym);

int blockLeader(const AHufNode *tree, int curPos);

int hasNextBlockLeader(const AHufNode *tree, const int curNode);

int interchange(AHufNode *tree, const int curPos, const int curBlockLeader);

void swap(AHufNode *tree, const int v1, const int v2);

int search(const AHufNode *tree, const char symbol, const int _0_Ind, int *curSymLen);

void slide_increment(AHufNode *tree, int *p);

void encode(int *lenght, const char symbols[]);


#endif

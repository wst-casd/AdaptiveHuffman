
#include<stdlib.h>
#include"AdaptiveHuffman.h"

const int ALPHABET_SIZE = 256;

int occuredLetter[256];		//记录已经处理过的不同symbol,1表示处理过，0表示没处理过

void initTree(AHufNode *tree, int *ind)
{
	tree[ALPHABET_SIZE*2 - 1].parent = ALPHABET_SIZE*2;
	tree[ALPHABET_SIZE*2 - 1].lchild = tree[ALPHABET_SIZE*2 - 1].rchild = -1;
	tree[ALPHABET_SIZE*2 - 1].weight = 0;
	tree[ALPHABET_SIZE*2 - 1].isleaf = '1';
	*ind = ALPHABET_SIZE*2 - 1;
}

int search(const AHufNode *tree, const char symbol, const int _0_Ind, int *curSymLen)
{
	int num = 0;

	int pos;

	AHufNode temp;

	if (occuredLetter[(int)symbol] == 1)
	{	//该字符之前处理过
		for (int i = _0_Ind + 1; i <= ALPHABET_SIZE*2 - 1; i++)
		if (tree[i].element == symbol)
		{
			temp = tree[i];
			pos = i;
			break;
		}

		while (temp.parent != ALPHABET_SIZE*2)
		{
			num++;
			temp = tree[temp.parent];
		}
	}
	else
	{	//该字符之前没有处理过
		pos = _0_Ind;
		temp = tree[pos];
		occuredLetter[(int)symbol] = 1;

		while (temp.parent != ALPHABET_SIZE*2)
		{
			num++;
			temp = tree[temp.parent];
		}
	}

	*curSymLen = num;
	return pos;
}

int blockLeader(const AHufNode *tree, int curPos)
{
	int ind;
	for (ind = curPos+1; ind <= ALPHABET_SIZE*2 - 1; ind++)
	{
		if ((tree[curPos].isleaf == tree[ind].isleaf) && (tree[curPos].weight == tree[ind].weight))
			curPos += 1;
		else
		{
			break;
		}
	}

	return ind - 1;
}

int hasNextBlockLeader(const AHufNode *tree, const int curNode)
{
	int nextBlockleader = -1;
	if (curNode == ALPHABET_SIZE * 2 - 1)
		return nextBlockleader;
	else
	{
		if (tree[curNode + 1].weight > tree[curNode].weight + 1 )
			return nextBlockleader;
		else
		{
			if (tree[curNode].isleaf == tree[curNode+1].isleaf)
			{
				return nextBlockleader;
			}
			else
			{
				nextBlockleader = blockLeader(tree, curNode+1);
				return nextBlockleader;
			}
		}

	}
		
}

void split(AHufNode *tree, int *_0_Ind, int *curPos, const char sym)
{
	tree[*_0_Ind].lchild = *_0_Ind - 2;
	tree[*_0_Ind].rchild = *_0_Ind - 1;
	tree[*_0_Ind].isleaf = '0';
	tree[*_0_Ind - 2].lchild = tree[*_0_Ind - 2].rchild = -1;
	tree[*_0_Ind - 2].parent = *_0_Ind;
	tree[*_0_Ind - 2].weight = 0;
	tree[*_0_Ind - 2].isleaf = '1';
	tree[*_0_Ind - 1].lchild = tree[*_0_Ind - 1].rchild = -1;
	tree[*_0_Ind - 1].parent = *_0_Ind;
	tree[*_0_Ind - 1].weight = 1;
	tree[*_0_Ind - 1].isleaf = '1';
	tree[*_0_Ind - 1].element = sym;
	*curPos = *_0_Ind;

	*_0_Ind -= 2;
}

int interchange(AHufNode *tree, const int curPos, const int curBlockLeader)
{
	if (curPos != curBlockLeader)
	{
		int tempParent = tree[curPos].parent;

		AHufNode temp = tree[curPos];
		tree[curPos] = tree[curBlockLeader];
		tree[curBlockLeader] = temp;

		tree[curBlockLeader].parent = tree[curPos].parent;
		tree[curPos].parent = tempParent;
	}
	
	return  curBlockLeader;
}

void swap(AHufNode *tree, const int v1, const int v2)
{
	int tempParent = tree[v1].parent;
	if (tree[v2].isleaf == '0')
	{
		tree[tree[v2].lchild].parent = v1;
		tree[tree[v2].rchild].parent = v1;
	}
	tree[v1] = tree[v2];
	tree[v1].parent = tempParent;
}

void slide_increment(AHufNode *tree, int *p)
{
	int wt = tree[*p].weight;

	int nextBlockLeader = hasNextBlockLeader(tree, *p);

	if ( nextBlockLeader == -1 )
	{
		tree[*p].weight = wt + 1;
		*p = tree[*p].parent;
	}
	else
	{
		int priorParent = tree[*p].parent;

		AHufNode tempNode = tree[*p];
		for (int i = *p; i < nextBlockLeader; i++)
		{
			swap(tree, i, i + 1);
		}

		*p = nextBlockLeader;

		int tempParent = tree[nextBlockLeader].parent;
		if (tempNode.isleaf == '0')
		{
			tree[tempNode.lchild].parent = nextBlockLeader;
			tree[tempNode.rchild].parent = nextBlockLeader;
		}

		tree[nextBlockLeader] = tempNode;
		tree[nextBlockLeader].parent = tempParent;

		tree[*p].weight = wt + 1;
		if (tree[*p].isleaf == '1')
			*p = tree[*p].parent;
		else
			*p = priorParent;
	}
}

void encode(int *lenght, const char symbols[])
{
	*lenght = 0;

	char curSymbol;	//当前的symbol

	int symInd = 0;		//

	int _0_Ind;         //0-Node对应的位置

	int curSymLen;      //当前字符编码后的长度

	//初始时没有处理过任何symbol
	for (int i = 0; i <= ALPHABET_SIZE-1; i++)
		occuredLetter[i] = 0;

	struct Node_AHuf tree[512];

	initTree(tree, &_0_Ind);

	while ((curSymbol = symbols[symInd++]) != '\0')
	{
		int curPos = search(tree, curSymbol, _0_Ind, &curSymLen);

		if (curPos == _0_Ind)
		{
			curSymLen += 8;
			*lenght += curSymLen;
			curSymLen = 0;
			split(tree, &_0_Ind, &curPos, curSymbol);
		}
		else
		{
			*lenght += curSymLen;
			curPos = interchange(tree, curPos, blockLeader(tree, curPos));

			if (tree[tree[_0_Ind].parent].rchild == curPos)
			{
				tree[curPos].weight += 1;
				curPos = tree[curPos].parent;
			}
		}

		while (curPos < ALPHABET_SIZE*2)
		{
			slide_increment(tree, &curPos);
		} 		
	}
}





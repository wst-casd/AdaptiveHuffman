#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <time.h>
#include"AdaptiveHuffman.h"


int main(int argc, char * argv[])
{
	int compressionLenght = 0;
	int ind = 0;
	char ch;
	char *text = (char*)malloc(20000000*sizeof(char));

	if ( argc < 3 )
	{
		printf("���з�ʽ���ԣ�\n");
		exit(0);
	}

	FILE *fp;
	char *filename = argv[2];
	if ((fp = fopen(filename, "r")) == NULL)
	{
		printf("The file does not exist!\n");
		exit(0);
	}

	while ((ch = fgetc(fp)) != EOF)
	{
		text[ind++] = ch;
	}

	text[ind] = '\0';

	fclose(fp);

	clock_t start, finish;
	double  duration;

	if ( 0 == strcmp( argv[1], "-ah") )
	{
		start = clock();
		encode(&compressionLenght, text);
		finish = clock();
	}
	else
	{
		if ( 0 == strcmp(argv[1], "-sh" ) )
		{
			printf("�Բ���û��дStatic Huffman�Ĵ��룡\n");
		}
		else
		{
			printf("�Բ���û��д��������Ĵ��룡\n");
		}
	}


	duration = (double)(finish - start) / CLOCKS_PER_SEC;

	printf("�ļ�ѹ��ǰ��С��%d B\n", strlen(text));
	printf("�ļ�ѹ�����С��%d B\n", (7 + compressionLenght) / 8);
	printf("ѹ���ȣ�%f \n", strlen(text)*1.0 / ( (7 + compressionLenght) / 8) );
	printf("��ʱ��%f ��\n", duration);
	free(text);
	//system("pause");
	return 0;
}
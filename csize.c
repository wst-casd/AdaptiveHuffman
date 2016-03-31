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
		printf("运行方式不对！\n");
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
			printf("对不起，没有写Static Huffman的代码！\n");
		}
		else
		{
			printf("对不起，没有写关于这个的代码！\n");
		}
	}


	duration = (double)(finish - start) / CLOCKS_PER_SEC;

	printf("文件压缩前大小：%d B\n", strlen(text));
	printf("文件压缩后大小：%d B\n", (7 + compressionLenght) / 8);
	printf("压缩比：%f \n", strlen(text)*1.0 / ( (7 + compressionLenght) / 8) );
	printf("用时：%f 秒\n", duration);
	free(text);
	//system("pause");
	return 0;
}
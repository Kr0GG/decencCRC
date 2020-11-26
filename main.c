#include "decenc.h"      // подключаем заголовочный файл + stdio.h
#define INVALID_ARGUMENTS 1
#define FILE_NOT_FOUND -1
#define СANNOT_CREATE_FILE -2

int main(int argc, char* argv[])
{                               
	if (argc != 5) {
		printf("invalid number of arguments");
		return INVALID_ARGUMENTS;
	}
	if (strcmp(argv[1], "-i")) {
		printf("invalid key #1");
		return INVALID_ARGUMENTS;
	}
	if (strcmp(argv[3], "-o")) {
		printf("invalid key #2");
		return INVALID_ARGUMENTS;
	}
	FILE* input = fopen(argv[2], "r");
	if (input == NULL) {
		printf("Cannot open file with TNode for reading! \n");
		return FILE_NOT_FOUND;
	}
	FILE* output = fopen(argv[4], "w");
	if (output == NULL) {
		printf("Cannot create file for writing!\n");
		return СANNOT_CREATE_FILE;
	}
	int gx, m, e, k, ukstr, pos, r;
	int ch = fscanf(input, "%d%", &gx); 
	fscanf(input, "%d%", &m); //mes//m=l
	fscanf(input, "%d%", &e); //osh
	fscanf(input, "%d%", &k); //dlina
	int str[80];
	sprintf(str, "%d", m); 
	r= deg(gx);
	//r = pos = strlen(str) - strlen(ukstr-1);
	int end=encoderdecoder(gx, k, e, m, r);
	fprintf(output, "%d \n", end);
	//printf("Quotient is %d\n", divide(dividend, divisor));
	//printend();
	return 0;

}

#include "decenc.h"      // ���������� ������������ ���� + stdio.h
#define INVALID_ARGUMENTS 1
#define FILE_NOT_FOUND -1
#define СANNOT_CREATE_FILE -2

int main(int argc, char** argv){
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
        int gx, m, e;
        char* Gx, * M, * E;
        Gx = (char*)malloc(sizeof(char) * MSG_SIZE);
        M = (char*)malloc(sizeof(char) * MSG_SIZE);
        E = (char*)malloc(sizeof(char) * MSG_SIZE);
        fscanf(input, "%s", Gx);
        fscanf(input, "%s", M); //mes//m=l
        fscanf(input, "%s", E); //osh
        gx = toDec(Gx);
        m = toDec(M);
        e = toDec(E);
        printf("gx = %d\n", gx);
        printf("e = %d\n", e);
        printf("m = %d\n", m);
        //    printf("coder = %d\n",coder(gx,e,m));
        int end = coder(gx, e, m);

        end = Decoder(gx, end);
        if (end != 0) {
            printf("\nError decoding!\n");
        }
        if (end == 0 && e != 0) {
            printf("\nError not found! err!=0\n");
        }
        fprintf(output, "%d \n", end);
        free(Gx);
        free(M);
        free(E);
        return;
    }


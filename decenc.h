#ifndef main_h_included
#define main_h_included
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
#include <math.h>
#define MSG_SIZE 128
int n, tmp;
int deg(int copyg);
int divide(int dividend, int divisor);
int coder(int gx, int e, int m);
int Decoder(int gx, int bx);
char *toBinary(int num);
int toDec(char *bin);
#endif

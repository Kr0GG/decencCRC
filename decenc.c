#include "decenc.h"

int coder(int gx, int e, int m){
    int ax,bx,cx;
    ax=m;
    ax*=pow(2,deg(gx)-1);
    cx = divide(ax,gx);
    ax = ax^cx;
    bx = ax^e;

    char *Ax,*Bx,*Cx,*E, *M, *Gx;
    Ax = toBinary(ax);
    Bx = toBinary(bx);
    Cx = toBinary(cx);
    E = toBinary(e);
    Gx = toBinary(gx);
    M = toBinary(m);
    printf("\n\tEncoder\n");
    printf("m: %d  %s\n",m,M);
    printf("gx: %d  %s \n",gx,Gx);
    printf("ax: %d  %s \n",ax,Ax);
    printf("bx: %d  %s \n",bx,Bx);
    printf("cx: %d  %s \n",cx,Cx);
    printf("e: %d  %s \n",e,E);
    free(Ax);
    free(Bx);
    free(E);
    free(Cx);
    free(M);
    free(Gx);
    return bx;
}
int Decoder(int gx, int bx){
    int cx;
    cx = divide(bx,gx);
    char *Bx,*Cx,*Gx;
    Bx = toBinary(bx);
    Cx = toBinary(cx);
    Gx = toBinary(gx);
    printf("\n\tDecoder\n");
    printf("gx: %d  %s \n",gx,toBinary(gx));
    printf("bx: %d  %s \n",bx,Bx);
    printf("cx: %d  %s \n",cx,Cx);
    //printf("%d \n", strlen(Gx));
    free(Bx);
    free(Cx);
    free(Gx);
    return cx;
}


int deg(int copyg) {
    int x = 0;
    do{
        copyg /= 2;//copyg=copyg>>1;
        x++;
    }while(copyg > 0);
    return x;
}

int divide(int dividend, int divisor) {
	int div,dis;
	if(dividend==divisor){
        return 0;
	}
	div = deg(dividend);
	dis = deg(divisor);
	if(div<dis){
        return dividend;
	}
	int cicleCount = div-dis +1;
	int checkNull;
	char *msg = toBinary(dividend);
	char *d = toBinary(divisor);
	int k = 0;
 	for(int i = 0; i<cicleCount;i++) {
        if (msg[i] == '0') {
            continue;
        }
        for (int j = i; j < i + dis; j++) {
            if (msg[j] == d[k]) {
                msg[j] = '0';
            }else{
                msg[j] = '1';
            }
            k++;
        }
        checkNull = toDec(msg);
        if (checkNull == 0) {
            return 0;
        }
        k = 0;
    }
 	free(msg);
 	free(d);
    return checkNull;
}

char *toBinary(int num){
    int size = deg(num);
    int mod,j;
    char *bin;
    j = size -1;
    bin = (char*)malloc(sizeof(char)*(size));
    for(int i=0;i<size;i++){
        mod = num%2;
        num/=2;
        if(mod == 0){
            bin[j]='0';
        } else{
            bin[j]='1';
        }
        j--;
    }
    return bin;
}

int toDec(char* bin) {
    int tmp;
    int x = 0;
    int size = strlen(bin);
    int j = size-1;
    for(int i=0;i<size;i++){
//        printf("%c %d\n",bin[i],i);
        if(bin[i]=='1') {
            tmp = 2 << j;
            x += tmp;
        }
        j--;
    }
    return x;
}
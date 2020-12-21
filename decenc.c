#include "decenc.h"

int coder(int gx, int e, int m){
    int ax,bx,cx;
    ax=m;
    bx= 1 << (deg(gx)-1);
    ax *= bx;
   // ax*=pow(2,deg(gx)-1); //? 1<<(deg(gx)-1);
    cx = divide(ax, gx);
    ax = ax^cx;
    bx = ax^e;

    char *Ax,*Bx,*Cx,*E, *M, *Gx;
    Ax = toBinary(ax, gx, m);
    Bx = toBinary(bx, gx, m);
    Cx = toBinary(cx, gx, m);  //((deg(ax)-deg(cx))<<3)
    E = toBinary(e, gx, m);
    Gx = toBinary(gx, gx, m);
    M = toBinary(m, gx, m);
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
    //printf("%d BBBBBBBBBBBBBBBBB", bx);
    cx = divide(bx,gx);
    char *Bx,*Cx,*Gx;
    Bx = toBinary(bx, gx, gx); //bx->>mx+-
    Cx = toBinary(cx, gx, gx); //kostuli
    Gx = toBinary(gx, gx, gx);
    printf("\n\tDecoder\n");
    printf("gx: %d  %s \n",gx,toBinary(gx,gx,gx));
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
    do {
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
    //printf("cicleCount %d", cicleCount);
    int checkNull;
	char *msg = toBinary(dividend, divisor, 0);
    char *d = toBinary(divisor, divisor, 0);
    int k = 0;
    for(int i = 0; i<cicleCount;i++) {
       // printf(" msg=dividend  %s divisor %d k %s ", msg, d, k);
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
       // printf("checkNull %d", checkNull);
        if (checkNull == 0) {
            return 0;
        }
        k = 0;
    }
 	free(msg);
 	free(d);
    return checkNull;
}

char* toBinary(int number, int gx, int m){   
    int ks = deg(gx) - 1;  //kontr summa.dlina
    int n = deg(number);//n = 1 << number;
    //printf("\n ks = %d  n = %d  number = %d, m = %d gx = %d \n", ks, n, number, m, gx);// printf("\n %d divdis %d n \n", divdis, n);
    int i=n-1;
    if (deg(m) + ks > deg(number)) {
        i += ks+deg(m)-deg(number);
    }
    if (0 == number) {
        i = deg(m)-1 + ks;
    }
    ks = i + 1;
    char* numberArray = (int*)calloc(ks, sizeof(char)); //malloc+set_null(memset)
     for (i; i >= 0; --i, number /= 2){ //
        numberArray[i] = (number % 2) + '0';
    }
    return numberArray;
}

int toDec(char* bin) { //char_to_int-bin
    int tmp;
    int x = 0;
    double size = strlen(bin);
    int j = size-1;
    for(int i=0;i<size;i++){
//        printf("%c %d\n",bin[i],i);
        if(bin[i]=='1') {
            tmp = 1 << j;
            x += tmp;
        }
        j--;
    }
    return x;
}

int esearch(int m) {
    int gx1, gx2;
    gx1 = 29;//11101;//toDec(Gx);
    gx2 = 23;//10111;//toDec(Gx);
    int result1;
    int result2;
    int e_weight, ecopy, n;
   //  printf ("%s",toBinary(e)); // toBinary = to_mass
    for (int e = 1; deg(e) < MSG_SIZE; e++) { //e<<1
        n = 0;
        ecopy = e;
        while (ecopy != 0) {
            if ((ecopy % 2) == 1) { //if 0001&xxxx=1
                n++;
            }
            ecopy = ecopy >> 1;
        }
        if (1 == n % 2) {
            
            result1 = divide(e, gx1);
            result2 = divide(e, gx2);
            //printf("\n result1 = %d result2 = %d e = %d \n", result1, result2, e); //typicalDebug
            if (0 == result1 || 0 == result2) {
                int gx; 
                if (0 == result1)  gx = gx1;
                else gx = gx2;
                char* E;
                E = toBinary(e, gx, gx);
                printf("\n finally found this example, e = %d, in a binary type E = %s \n", e, E); 
                free(E);
                return 2;
            }
        }


    }
    printf("\n Cannot find this example, because there is no available any 'e' which will be included in space of coding words \n");
    return 0;
}
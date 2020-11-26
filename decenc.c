#include "decenc.h"   
int deg(int copyg) {
	int x = 0;
	//printf("%d", m);
	//int copyg = gx;
	//ukstr = strchr(str, "1");
	while (copyg != 0) {
		x++;
		copyg = copyg >> 3;
	};
	return (x - 1); // step. mn-na
}
int encoderdecoder(gx, k, e, m, r) {
	int cx, a, b, s, soom, sfa;
	printf("Counting Cx...");
	cx = divide((m << r), gx);
	printf("Counting a...");
	a = (m << r) + cx;
	printf("Counting b...");
	b = a ^ e;
	printf("Counting S...");
	int S = divide(b, gx);
	if (S != 0)
		printf("Found e");
	else
		printf("E is not found");
	return b;
	//oshipka(); //вычисление синдрома
}
int divide(int dividend, int divisor) {
	int tmp, tmp2;
	int deg1 = deg(dividend);
	int deg2 = deg(divisor);
	if (deg1 < deg2) {
		return dividend; //
	}
	tmp = divisor << (deg1 - deg2);
	tmp2 = (int*)malloc(sizeof(deg1));
	tmp2 = divide(dividend ^ tmp, divisor);
	dividend = tmp2;
	free(tmp2);
	return dividend;
}
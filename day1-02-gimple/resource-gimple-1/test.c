#include "stdio.h"
int main()
{
	int a,b=5,c=0;
	a = a+b;
	c = a+b;
	if(c == 5)
		if(a == 9)
			return 0;
		else
			printf("a != 9");
	else
		printf("c !=5 ");
	printf("b : %d, %d",b, a+b);
	return 0;
}

#include<stdio.h>

extern void f6();
extern void f5();

void f1()
{	
	printf("In f1\n");
	f5();
}

void f2(int c)
{
	f5();
        printf("In f2 %d\n",c);
}

void f3()
{
        printf("In f3\n");
	f6();
}

int main()
{
	f1();
	
	f2(5);

	f6();

	printf("In main\n");
	f5();
}

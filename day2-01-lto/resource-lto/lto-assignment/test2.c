#include<stdio.h>

extern void f1();
extern void f3();

void f4()
{
	f1();
        printf("In f4\n");
}

void f5()
{
	f4();
        printf("In f5\n");
	f1();
}

void f6()
{
	f1();
        printf("In f6\n");
	
	f3();
}

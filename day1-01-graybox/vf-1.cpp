#include <iostream>
using namespace std;

class A
{ 
       public:
               virtual void f() {cout << "\tA:f" << endl;}
               virtual void f(string i) {cout << "\tA:f." << i << endl;}
               virtual void g() {cout << "\tA:g" << endl;}
};

class B : public A
{     public:
              virtual void g() {cout << "\tB:g" << endl;}
              void f() {cout << "\tB:f" << endl;}
};

class C : public B
{ 
     public:
              void f() {cout<< "\tC:f" << endl;}
};

int main()
{ 
        A  a, *array[3];
        B  b;
        C  c;
        
        array[0]=&a;
        array[1]=&b;
        array[2]=&c;
        for (int i=0;i<3;i++)
        {
                cout << i ;
                array[i]->f();
                array[i]->f("x");
                array[i]->g();
         }
}         

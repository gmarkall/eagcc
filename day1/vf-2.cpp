class A
{ 
        public:
	        virtual void f() {int a;}
	        virtual void f(char i) {int b;char s=i;}
	        virtual void g() {int c;}         
};

class B : public A
{ 
        public:
        	virtual void g() {int a;}
        	void f() {int q;}
};

class C : public B
{ 
        public:
		void f() {int r=5;}
};

int main()
{       A  a, *array[3];
	B  b;
	C  c;
	array[0]=&a;
	array[1]=&b;
	array[2]=&c;
	for (int i=0;i<3;i++)
	{
                array[i]->f();
                array[i]->f('x');
               array[i]->g();
        }
}	

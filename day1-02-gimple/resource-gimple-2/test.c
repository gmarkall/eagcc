
int foo (int, int, int);

int main ()
{
        int a, b, c;
        char d;

        a = 2;
        b = c--;
        a = foo (a, b, c);
        if (b < (c+a)){
	        a = foo (a, b, c);
                c = ~c;
	}
        else if(b > (c+a)){
                c = a + 3;
        	a = foo (a, b, c);
	}
	else
        	a = foo (a, b, c);
        d = (char) b;
        return 0;
}

int foo (int p, int q, int r)
{
        q = p + r - 4;
        return 0;
}

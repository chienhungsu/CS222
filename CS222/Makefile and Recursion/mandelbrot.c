#include "complex.h"
#include "mandelbrot.h"

complex_t mandelbrot(int n,complex_t c)
{
	//complex_t va = mandelbrot(n-1,c);
	complex_t va;
	va.real=10000.00; 
	va.imag=10000.00;  
	complex_t tmp;
	complex_t s; 
	complex_t t=abs_complex(c);
	//draw mandelbrot set
	if(n==0)
	{
		s.real=c.real;
		s.imag=c.imag; 
		return s;
	}
	else if(t.real>10000.00) 
	{
		return va;
	}	
	else
	{
		tmp = mandelbrot(n-1,c);
		tmp = multiply_complex(tmp,tmp); 
		tmp = add_complex(tmp,c); 
		return tmp;	
	}
}


#include <stdio.h>
#include "complex.h"
#include "mandelbrot.h"
//starting point
#define start -1.12
#define start1 -2.00
//ending point
#define end 1.12
#define end1 0.47
int main()
{
	FILE *fp; 
	fp=fopen("s.bin","wb");
//declare the variables  for the  pixels 
complex_t c;
//c in the area from (-2.0, -1.12) to (0.47, 1.12)
for (c.imag = start; c.imag < end; c.imag += 0.077) /* number of rows are 30 */
{   
	for (c.real = start1; c.real < end1; c.real += 0.06175) /*number of columns are 40*/
	{
		//calculate the  real  and imaginary part for c	
	complex_t e= mandelbrot(15,c);
	complex_t s=abs_complex(e);
        //create  the mandelbrot  set	
	if (s.real< 10000.00)
	{	
	//mandelbrot  image char
	printf("#");
	// print in the file
	fprintf(fp,"#");
	}	
	else
	{
	//outside  of the mandelbrot draw will print  space  or  '-'
	printf("-");
	//print in the file
	fprintf(fp,"-");
	}
	
	}
//change  of  line to draw as  two dimensional array
printf("\n");
fprintf(fp,"\n");
}
fclose(fp);
return 0;
} 

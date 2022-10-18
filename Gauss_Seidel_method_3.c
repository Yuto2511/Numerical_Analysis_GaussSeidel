#include<stdio.h>

double get_x1(double, double);
double get_x2(double, double);
double get_x3(double, double);

int main()
{
	double x1, x2, x3;
	double buf_x1, buf_x2, buf_x3;
	int n = 0;

	x1 = x2 = x3 = 1.0;
	buf_x1 = buf_x2 = buf_x3 = 0.0;

	printf("round %d, (%12.10f, %12.10f, %12.10f)\n", 0, x1, x2, x3);
	while(n < 20)
	{
		n++;
		x1 = get_x1(x2, x3);
		x2 = get_x2(x1, x3);
		x3 = get_x3(x1, x2);

		
		printf("round %d, (%12.10f, %12.10f, %12.10f)", n, x1, x2, x3);

		//収束判定
		/*
		if(buf_x1 >= x1*0.99999999999 && buf_x1 <= x1*1.00000000001 
			&& buf_x2 >= x2*0.99999999999 && buf_x2 <= x2*1.00000000001
			&& buf_x3 >= x3*0.99999999999 && buf_x3 <= x3*1.00000000001) break;
		*/
		if(buf_x1 >= x1 * 0.999999999999 && buf_x1 <= x1 * 1.000000000001)
		{
			printf("  <= convergence\n");
			//break;
		}
		else printf("\n");

		//Bufferに格納
		buf_x1 = x1;
		buf_x2 = x2;
		buf_x3 = x3;
	}

	return 0;
}

double get_x1(double x2, double x3)
{
	return( (10 - x2 - x3) / 5 );
}

double get_x2(double x1, double x3)
{
	return( (12 - x1 - x3) / 4 );
}

double get_x3(double x1, double x2)
{
	return( (13 - 2*x1 - x2) / 3 );
}


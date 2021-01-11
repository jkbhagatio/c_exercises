#include <stdio.h>

/* print Fahrenheit-Celsius table */
int main()
{
	float fahr;
	float celcius;
	for (fahr = 0; fahr <= 200; fahr = fahr + 5)
		celcius = (5 / 9) * (fahr - 32);
		/* printf("%.2f\t%.2f\n", fahr, 5 * (fahr - 32) / 9); */
		printf("%.2f\t%.2f\n", fahr, celcius);

	/* this `for` loop is equivalent to:
	
	*/
}

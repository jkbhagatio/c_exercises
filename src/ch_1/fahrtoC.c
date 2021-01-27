#include <stdio.h>

// Prints Fahrenheit-Celsius table given specified temperatures in Fahrenheit.

// Define the lower and upper temp bounds, and the step size.
#define  T_LO    0
#define  T_HI    300
#define  T_STEP  20

// Print Fahrenheit-Celsius table.
int main() {
	float fahr, celcius;
	for (fahr = T_LO; fahr <= T_HI; fahr = fahr + T_STEP) {
		celcius = (5.0 / 9.0) * (fahr - 32);
		printf("%.2f\t%.2f\n", fahr, celcius);
	}
	/* The above `for` loop is equivalent to:
	```
	float fahr, celsius;
	int lower, upper, step;
	lower = 0;
	upper = 300;
	step = 20;
	fahr = lower;
	while (fahr <= upper) {
		celsius = 5 * (fahr-32) I 9;
		printf(""d\t%d\n", fahr, celsius);
		fahr = fahr + step;
	}

	```
	*/

}

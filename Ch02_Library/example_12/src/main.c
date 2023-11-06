#include <stdio.h>

#include "../includes/config.h"
#ifdef HAVE_MY_MATH_LIB
	#include <myMathLib/myMathLib.h>
#else
	#include <math.h>
#endif

int main(){
	double dBase;
	int iExp;

	printf("Please enter the base: ");
	scanf("%lf", &dBase);
	printf("Please enter the exponential:");
	scanf("%d", &iExp);

#ifdef HAVE_MY_MATH_LIB
	printf("We use myMathLib.\n");
	double dAns = calcPow(dBase, iExp);
#else
	printf("We use standard library.\n");
	double dAns = pow(dBase, iExp);
#endif

	printf("%lf ^ %d = %lf\n", dBase, iExp, dAns);

	return 0;
} // End of main

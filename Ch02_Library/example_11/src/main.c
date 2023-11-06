#include <stdio.h>
#include <myMathLib/myMathLib.h>

int main(){
	double dBase;
	int iExp;

	printf("Please enter the base: ");
	scanf("%lf", &dBase);
	printf("Please enter the exponential:");
	scanf("%d", &iExp);

	printf("%lf ^ %d = %lf\n", dBase, iExp, calcPow(dBase, iExp));
	return 0;
} // End of main

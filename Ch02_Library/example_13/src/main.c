#include <stdio.h>
#include <myMathLib/myMathLib.h>

int main(){
	double dBase, dAns;
	int iExp;
	
	printf("Please enter the base: ");
	scanf("%lf", &dBase);
	printf("Please enter the exponential: ");
	scanf("%d", &iExp);

	dAns = calcPow(dBase, iExp);
	printf("%lf ^ %d = %lf\n", dBase, iExp, dAns);
	return 0;
} // End of main

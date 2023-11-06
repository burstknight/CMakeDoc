#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/myMathLib.h"
#include "../includes/version.h"

int main(int argc, char** argv){
	if (argc < 3) {
		printf("Version: %d.%d\n", VERSION_MAJOR, VERSION_MINOR);
		printf("Usage: %s base exponential\n\tbase\t\tGive a float number as the base.\n\texponential\tGive an integer as the exponential.\n", argv[0]);
		exit(1);
	} // End of if-condition

	double dBase = atof(argv[1]);
	int iExp = atoi(argv[2]);

	printf("%.4f ^ %d is %.4f\n", dBase, iExp, calcPow(dBase, iExp));

	return 0;
} // End of main

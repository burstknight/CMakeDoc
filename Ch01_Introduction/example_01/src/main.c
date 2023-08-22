#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv){
	if (argc < 3) {
		printf("Usage: %s base exponential\n", argv[0]);
		exit(1);
	} // End of if-condition

	double dBase = atof(argv[1]);
	int iExp = atoi(argv[2]);

	printf("%f^%d = %f\n", dBase, iExp, calcPow(dBase, iExp));

	return 0;
} // End of main

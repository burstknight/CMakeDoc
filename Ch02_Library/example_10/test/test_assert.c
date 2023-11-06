#include "../includes/myMathLib.h"
#include <assert.h>
#include <math.h>
#include <stdlib.h>

void test_calcPow(double dX, int iExp, double dResult);

int main(int argc, char** argv){
	test_calcPow(5, 2, 25);
	test_calcPow(10, 2, 100);
	test_calcPow(2, 10, 1024);

	return 0;
} // End of main

void test_calcPow(double dX, int iExp, double dResult){
	/* 
	 * 計算函數`calcPow()`的結果與給定的結果`dResult`之間的差距，
	 * 來判斷該函數的計算結果是否正確
	 */
	double dGrap = fabs(calcPow(dX, iExp) - dResult);

	/*
	 * 使用標頭檔`assert.h`提供的巨集`assert()`來判斷函數`calcPow()`
	 * 的計算過程是否正確
	 */
	assert(dGrap < 1e-6);
} // End of test_calcPow

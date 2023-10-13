#include "config.h"
#ifdef USE_COLOR_PRINT
	#include "./ColorPrint/myPrint.h"
#else
	#include <stdio.h>
#endif

int main(){
#ifdef USE_COLOR_PRINT
	showMessage(Info, "Hello world!\n");
	showMessage(Error, "Error message!\n");
#else
	printf("Hello world!\n");
	printf("Error message!\n");
#endif

	return 0;
} // End of main

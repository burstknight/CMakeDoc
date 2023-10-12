#include "myPrint.h"
#include <string.h>
#include <stdarg.h>

int print(const char* pcColor, const char* pcMessage, va_list args){
	int iLength = 0;

	iLength = fprintf(stdout, pcColor);

	iLength += vfprintf(stdout, pcMessage, args);

	iLength += fprintf(stdout, "\x1b[0m");

	return  iLength;
} // End of print

int showMessage(enum LevelMode mode, const char* pcMessage, ...){
	char acColor[10];
	switch (mode) {
		case Warning:
			sprintf(acColor, "\x1b[33m");
			break;
		case  Error:
			sprintf(acColor, "\x1b[31m");
			break;
		case  Info:
		default:
			sprintf(acColor, "\x1b[0m");
			break;
	} // End of switch

	va_list args, args_data;
	va_start(args, pcMessage);
	va_copy(args_data, args);

	int iLength = print(acColor, pcMessage, args);

	va_end(args);
	va_end(args_data);

	return iLength;
} // End of showMessage

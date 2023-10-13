#ifndef MY_PRINT_H
#define MY_PRINT_H

#include <stdio.h>

enum LevelMode{
	Info = 0,
	Warning,
	Error
};

/**
 * @brief Like printf() but it can show color message.
 *
 * @param mode: Set the level for the message.
 * @param pcMessage: Give teh message to show on the screen.
 * @param ...
 *
 * @return Return the number of the given message.
 */
int showMessage(enum LevelMode mode, const char* pcMessage, ...);

#endif

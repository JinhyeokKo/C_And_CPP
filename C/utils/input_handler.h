#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include "common.h"

bool Input_GetInteger(const char* prompt, int* value);
bool Input_GetString(const char* prompt, char** buffer);
void Input_ClearBuffer(void);
void Input_WaitForEnter(void);

#endif // INPUT_HANDLER_H
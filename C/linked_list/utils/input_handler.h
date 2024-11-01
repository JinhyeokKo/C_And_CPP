#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include "common.h"

bool Input_GetInteger(const char* prompt, int* value);
void Input_ClearBuffer(void);
void Input_WaitForEnter(void);

#endif // INPUT_HANDLER_H
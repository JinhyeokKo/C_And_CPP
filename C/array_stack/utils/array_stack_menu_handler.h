#ifndef MENU_HANDLER_H
#define MENU_HANDLER_H

#include "common.h"
#include "array_stack.h"

typedef enum {
    MENU_EXIT = 0,
    MENU_PUSH,
    MENU_POP,
    MENU_PEEK,
    MENU_GET_SIZE,
    MENU_PRINT_ALL,
    MENU_CLEAR
} AS_MenuChoice;

void AS_Menu_DisplayOptions(void);
ErrorCode AS_Menu_ProcessChoice(ArrayStack* stack, AS_MenuChoice choice);

#endif //MENU_HANDLER_H

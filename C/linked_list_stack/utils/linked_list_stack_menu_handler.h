#ifndef LINKED_LIST_STACK_MENU_HANDLER_H
#define LINKED_LIST_STACK_MENU_HANDLER_H

#include "common.h"
#include "linked_list_stack.h"

typedef enum {
    MENU_EXIT = 0,
    MENU_PUSH,
    MENU_POP,
    MENU_PEEK,
    MENU_GET_COUNT,
    MENU_PRINT_ALL,
    MENU_CLEAR
} LLS_MenuChoice;

void LLS_Menu_DisplayOptions(void);
ErrorCode LLS_Menu_ProcessChoice(LinkedListStack* stack, LLS_MenuChoice choice);

#endif //LINKED_LIST_STACK_MENU_HANDLER_H

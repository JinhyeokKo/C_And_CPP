#ifndef MENU_HANDLER_H
#define MENU_HANDLER_H

#include "common.h"
#include "linked_list.h"

typedef enum {
    MENU_EXIT = 0,
    MENU_APPEND,
    MENU_INSERT_AFTER,
    MENU_INSERT_HEAD,
    MENU_REMOVE,
    MENU_GET_AT,
    MENU_GET_COUNT,
    MENU_PRINT_ALL,
    MENU_CLEAR
} LL_MenuChoice;

void LL_Menu_DisplayOptions(void);
ErrorCode LL_Menu_ProcessChoice(LinkedList* list, LL_MenuChoice choice);

#endif // MENU_HANDLER_H
#ifndef BOOT_HANDLER_H
#define BOOT_HANDLER_H

#include "common.h"
#include "array_stack.h"
#include "circular_queue.h"
#include "linked_list.h"
#include "linked_list_stack.h"
#include "linked_queue.h"
#include "menu_handler.h"

typedef enum {
    BOOT_EXIT = 0,
    BOOT_LINKED_LIST,
    BOOT_ARRAY_STACK,
    BOOT_LINKED_LIST_STACK,
    BOOT_CIRCULAR_QUEUE,
    BOOT_LINKED_QUEUE
} BootChoice;

void Boot_DisplayOptions(void);
int Boot_ProcessChoice(BootChoice choice);
int Boot_Structure(void* structure, MenuHandler* handler);

#endif //BOOT_HANDLER_H

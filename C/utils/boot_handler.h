#ifndef BOOT_HANDLER_H
#define BOOT_HANDLER_H

#include "common.h"
#include "linked_list_boot.h"
#include "array_stack_boot.h"

typedef enum {
    BOOT_EXIT = 0,
    BOOT_LINKED_LIST,
    BOOT_ARRAY_STACK
} BootChoice;

void Boot_DisplayOptions(void);
int Boot_ProcessChoice(BootChoice choice);

#endif //BOOT_HANDLER_H

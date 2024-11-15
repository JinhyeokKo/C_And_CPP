#ifndef MENU_HANDLER_H
#define MENU_HANDLER_H

#include "common.h"

typedef enum {
    MENU_EXIT = 0,
    MENU_INPUT,
    MENU_OUTPUT,
    MENU_PEEK,
    MENU_COUNT,
    MENU_PRINT,
    MENU_CLEAR
} MenuChoice;

typedef struct {
    bool (*value)(const char*, ElementType*);

    struct {
        ErrorCode (*input)(void *structure, ElementType);
        ErrorCode (*list_append)(void *structure, ElementType);
        ErrorCode (*list_insert_after)(void *structure, ElementType, ElementType);
        ErrorCode (*list_insert_head)(void *structure, ElementType);
    } input;

    struct {
        ErrorCode (*output)(void *structure);
        ErrorCode (*list_remove)(void *structure, ElementType);
    } output;

    struct {
        ErrorCode (*peek)(void *structure);
        ErrorCode (*list_get_at)(void *structure, ElementType);
    } peek;

    size_t (*count)(void *structure);
    void (*print)(void *structure);
    void (*clear)(void *structure);
    void (*destroy)(void *structure);

    enum {
        TYPE_LINKED_LIST,
        TYPE_LINKED_LIST_STACK,
        TYPE_ARRAY_STACK,
        TYPE_CIRCULAR_QUEUE,
        TYPE_LINKED_QUEUE
    } structure_type;

} MenuHandler;

extern MenuHandler arrayStackHandler;
extern MenuHandler linkedListStackHandler;
extern MenuHandler circularQueueHandler;
extern MenuHandler linkedQueueHandler;
extern MenuHandler linkedListHandler;

extern const char* STRUCTURE_TYPE_STRINGS[];

void Menu_DisplayOptions(const char* type);
ErrorCode Menu_ProcessChoice(void *structure, MenuChoice choice, MenuHandler *handler);

#endif //MENU_HANDLER_H

 #ifndef LINKED_LIST_STACK_H
#define LINKED_LIST_STACK_H

#include "common.h"

typedef struct LLS_Node {
    char* Data;
    struct LLS_Node *Link;
}LLS_Node;

typedef struct {
    LLS_Node* Top;
    size_t Count;
} LinkedListStack;

LinkedListStack* LLS_Create(void);
void LLS_Destroy(LinkedListStack* stack);
void LLS_DestroyNode(LLS_Node* node);

ErrorCode LLS_Push(LinkedListStack* stack, const char* data);
ErrorCode LLS_Pop(LinkedListStack* stack);
ErrorCode LLS_Peek(const LinkedListStack* stack);
size_t LLS_GetCount(const LinkedListStack* stack);

void LLS_Clear(LinkedListStack* stack);
bool LLS_IsEmpty(const LinkedListStack* stack);
void LLS_Print(const LinkedListStack* stack);

#endif //LINKED_LIST_STACK_H
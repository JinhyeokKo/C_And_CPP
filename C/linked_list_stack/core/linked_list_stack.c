#include "linked_list_stack.h"

static LLS_Node* CreateNode(const char* data) {
    LLS_Node* new_node = (LLS_Node*)malloc(sizeof(LLS_Node));
    if (!new_node) return NULL;

    new_node->Data = (char*)malloc(strlen(data) + 1);
    if (!new_node->Data) {
        free(new_node);
        return NULL;
    }
    strcpy(new_node->Data, data);
    new_node->Link = NULL;

    return new_node;
}

LinkedListStack* LLS_Create(void){
    LinkedListStack* stack = (LinkedListStack*)malloc(sizeof(LinkedListStack));
    stack->Top = NULL;
    stack->Count = 0;
    return stack;
}

void LLS_Destroy(LinkedListStack* stack) {
    if(!stack) return;

    LLS_Clear(stack);
    free(stack);
}

void LLS_DestroyNode(LLS_Node* node) {
    if(!node) return;
    free(node->Data);
    free(node);
}

void LLS_Clear(LinkedListStack* stack) {
    if(!stack || !stack->Top) return;

    while (!LLS_IsEmpty(stack)) {
        LLS_Pop(stack);
    }
}

ErrorCode LLS_Push(LinkedListStack* stack,const char* data) {
    if (!stack) return ERROR_INVALID_PARAMETER;

    LLS_Node* new_node = CreateNode(data);
    if (!new_node) return ERROR_MEMORY_ALLOCATION;

    new_node->Link = stack->Top;
    stack->Top = new_node;
    stack->Count++;

    return SUCCESS;
}

ErrorCode LLS_Pop(LinkedListStack* stack) {
    if (!stack) return ERROR_INVALID_PARAMETER;
    if (LLS_IsEmpty(stack)) return ERROR_OUT_OF_RANGE;

    LLS_Node* top = stack->Top;
    stack->Top = stack->Top->Link;
    stack->Count--;
    LLS_DestroyNode(top);

    return SUCCESS;
}

ErrorCode LLS_Peek(const LinkedListStack* stack) {
    if (!stack) return ERROR_INVALID_PARAMETER;
    if (LLS_IsEmpty(stack)) return ERROR_OUT_OF_RANGE;

    printf("최상단의 데이터: %s",stack->Top->Data);
    return SUCCESS;
}

size_t LLS_GetCount(const LinkedListStack* stack) {
    return stack ? stack->Count : 0;
}

bool LLS_IsEmpty(const LinkedListStack* stack) {
    return stack->Count == 0;
}

void LLS_Print(const LinkedListStack* stack) {
    if(!stack || LLS_IsEmpty(stack)) {
        printf("스택이 비어있습니다.\n");
        return;
    }

    printf("스택 내용:");
    LLS_Node* node = stack->Top;

    do {
        printf("%s", node->Data);
        if (node->Link) {
            printf(" -> ");
        }
        node = node->Link;
    }
    while (node);

    printf("\n총 데이터 개수: %zu\n", stack->Count);
}
#include "linked_list_stack.h"

static LLS_Node* CreateNode(ElementType data) {
    LLS_Node* new_node = (LLS_Node*)malloc(sizeof(LLS_Node));
    if (!new_node) return NULL;

    new_node->data.string = (char*)malloc(strlen(data.string) + 1);
    if (!new_node->data.string) {
        free(new_node);
        return NULL;
    }
    strcpy(new_node->data.string, data.string);
    new_node->link = NULL;

    return new_node;
}

LinkedListStack* LLS_Create(void){
    LinkedListStack* stack = (LinkedListStack*)malloc(sizeof(LinkedListStack));
    stack->top = NULL;
    stack->count = 0;
    return stack;
}

void LLS_Destroy(LinkedListStack* stack) {
    if(!stack) return;

    LLS_Clear(stack);
    free(stack);
}

void LLS_DestroyNode(LLS_Node* node) {
    if(!node) return;
    free(node->data.string);
    free(node);
}

void LLS_Clear(LinkedListStack* stack) {
    if(!stack || !stack->top) return;

    while (!LLS_IsEmpty(stack)) {
        LLS_Pop(stack);
    }
}

ErrorCode LLS_Push(LinkedListStack* stack,ElementType data) {
    if (!stack) return ERROR_INVALID_PARAMETER;

    LLS_Node* new_node = CreateNode(data);
    if (!new_node) return ERROR_MEMORY_ALLOCATION;

    new_node->link = stack->top;
    stack->top = new_node;
    stack->count++;

    return SUCCESS;
}

ErrorCode LLS_Pop(LinkedListStack* stack) {
    if (!stack) return ERROR_INVALID_PARAMETER;
    if (LLS_IsEmpty(stack)) return ERROR_OUT_OF_RANGE;

    LLS_Node* top = stack->top;
    stack->top = stack->top->link;
    stack->count--;
    LLS_DestroyNode(top);

    return SUCCESS;
}

ErrorCode LLS_Peek(const LinkedListStack* stack) {
    if (!stack) return ERROR_INVALID_PARAMETER;
    if (LLS_IsEmpty(stack)) return ERROR_OUT_OF_RANGE;

    printf("최상단의 데이터: %s",stack->top->data.string);
    return SUCCESS;
}

size_t LLS_GetCount(const LinkedListStack* stack) {
    return stack ? stack->count : 0;
}

bool LLS_IsEmpty(const LinkedListStack* stack) {
    return stack->count == 0;
}

void LLS_Print(const LinkedListStack* stack) {
    if(!stack || LLS_IsEmpty(stack)) {
        printf("스택이 비어있습니다.\n");
        return;
    }

    printf("스택 내용:");
    LLS_Node* node = stack->top;

    do {
        printf("%s", node->data.string);
        if (node->link) {
            printf(" -> ");
        }
        node = node->link;
    } while (node);

    printf("\n총 데이터 개수: %zu\n", stack->count);
}
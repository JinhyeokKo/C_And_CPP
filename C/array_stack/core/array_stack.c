#include "array_stack.h"

ArrayStack* AS_Create(size_t capacity) {
    ArrayStack* stack = (ArrayStack*)malloc(sizeof(ArrayStack));
    stack->Nodes = (AS_Node*)malloc(sizeof(AS_Node) * capacity);
    stack->Capacity = capacity;
    stack->Top = -1;
    return stack;
}

void AS_Destroy(ArrayStack* stack) {
    if(!stack) return;

    AS_Clear(stack);
    free(stack->Nodes);
    free(stack);
}

void AS_Clear(ArrayStack* stack) {
    if(!stack) return;
    stack->Top = -1;
}

ErrorCode AS_Push(ArrayStack* stack, ElementType data) {
    if (!stack) return ERROR_INVALID_PARAMETER;
    if (AS_IsFull(stack)) return ERROR_OUT_OF_RANGE;

    stack->Top++;
    stack->Nodes[stack->Top].Data = data;
    return SUCCESS;
}

ErrorCode AS_Pop(ArrayStack* stack) {
    if (!stack) return ERROR_INVALID_PARAMETER;
    if (AS_IsEmpty(stack)) return ERROR_OUT_OF_RANGE;

    int position = stack->Top--;
    printf("제거된 값: %d", stack->Nodes[position].Data);
    return SUCCESS;
}

ErrorCode AS_Peek(ArrayStack* stack) {
    if (!stack) return ERROR_INVALID_PARAMETER;
    if (AS_IsEmpty(stack)) return ERROR_OUT_OF_RANGE;

    printf("최상단의 데이터: %d",stack->Nodes[stack->Top].Data);
    return SUCCESS;
}

int AS_GetCount(const ArrayStack* stack) {
    return stack ? stack->Top + 1 : 0;
}

void AS_Print(const ArrayStack* stack) {
    if (!stack || AS_IsEmpty(stack)) {
        printf("스택이 비어있습니다.\n");
        return;
    }

    printf("스택 내용:");
    for (int i = stack->Top; i >=0 ; i--) {
        printf("%d", stack->Nodes[i].Data);
        if (i) {
            printf(" -> ");
        }
    }
    printf("\n총 데이터 개수: %d\n", stack->Top + 1);
    printf("스택의 크기: %zu\n", stack->Capacity);
}

bool AS_IsEmpty(const ArrayStack* stack) {
    return stack->Top == -1;
}

bool AS_IsFull(const ArrayStack* stack) {
    return stack->Top == stack->Capacity - 1;
}
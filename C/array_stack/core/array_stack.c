#include "array_stack.h"

ArrayStack* AS_Create(size_t capacity) {
    ArrayStack* stack = (ArrayStack*)malloc(sizeof(ArrayStack));
    if (!stack) {
        return NULL;
    }
    stack->nodes = (AS_Node*)malloc(sizeof(AS_Node) * capacity);
    if (!stack->nodes) {
        free(stack);
    }else {
        stack->capacity = capacity;
        stack->top = -1;
    }
    return stack;
}

void AS_Destroy(ArrayStack* stack) {
    if(!stack) return;

    AS_Clear(stack);
    free(stack->nodes);
    free(stack);
}

void AS_Clear(ArrayStack* stack) {
    if(!stack) return;
    stack->top = -1;
}

ErrorCode AS_Push(ArrayStack* stack, ElementType data) {
    if (!stack) return ERROR_INVALID_PARAMETER;
    if (AS_IsFull(stack)) return ERROR_OUT_OF_RANGE;

    stack->top++;
    stack->nodes[stack->top].data = data;
    return SUCCESS;
}

ErrorCode AS_Pop(ArrayStack* stack) {
    if (!stack) return ERROR_INVALID_PARAMETER;
    if (AS_IsEmpty(stack)) return ERROR_OUT_OF_RANGE;

    int position = stack->top--;
    printf("제거된 값: %d", stack->nodes[position].data.integer);
    return SUCCESS;
}

ErrorCode AS_Peek(ArrayStack* stack) {
    if (!stack) return ERROR_INVALID_PARAMETER;
    if (AS_IsEmpty(stack)) return ERROR_OUT_OF_RANGE;

    printf("최상단의 데이터: %d",stack->nodes[stack->top].data.integer);
    return SUCCESS;
}

size_t AS_GetCount(const ArrayStack* stack) {
    return stack ? stack->top + 1 : 0;
}

void AS_Print(const ArrayStack* stack) {
    if (!stack || AS_IsEmpty(stack)) {
        printf("스택이 비어있습니다.\n");
        return;
    }

    printf("스택 내용:");
    for (int i = stack->top; i >=0 ; i--) {
        printf("%d", stack->nodes[i].data.integer);
        if (i) {
            printf(" -> ");
        }
    }
    printf("\n총 데이터 개수: %zu\n", AS_GetCount(stack));
    printf("스택의 크기: %zu\n", stack->capacity);
}

bool AS_IsEmpty(const ArrayStack* stack) {
    return stack->top == -1;
}

bool AS_IsFull(const ArrayStack* stack) {
    return stack->top == stack->capacity - 1;
}
#ifndef ARRAY_STACK_H
#define ARRAY_STACK_H

#include "common.h"

typedef struct AS_Node{
    ElementType data;
} AS_Node;

typedef struct {
    AS_Node* nodes;
    size_t capacity;
    int top;
} ArrayStack;

// 생성자/소멸자
ArrayStack* AS_Create(size_t capacity);
void AS_Destroy(ArrayStack* stack);

// 기본연산
ErrorCode AS_Push(ArrayStack* stack, ElementType element);
ErrorCode AS_Pop(ArrayStack* stack);
ErrorCode AS_Peek(ArrayStack* stack);
size_t AS_GetCount(const ArrayStack* stack);

// 유틸리티 함수
bool AS_IsEmpty(const ArrayStack* stack);
bool AS_IsFull(const ArrayStack* stack);
void AS_Clear(ArrayStack* stack);
void AS_Print(const ArrayStack* stack);

#endif //ARRAY_STACK_H

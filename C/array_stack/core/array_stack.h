#ifndef ARRAY_STACK_H
#define ARRAY_STACK_H

#include "common.h"

typedef struct Array_Node{
    ElementType Data;
} Array_Node;

typedef struct {
    Array_Node* Nodes;
    size_t Capacity;
    int Top;
} ArrayStack;

// 생성자/소멸자
ArrayStack* AS_Create(size_t capacity);
void AS_Destroy(ArrayStack* stack);

// 기본연산
ErrorCode AS_Push(ArrayStack* stack, ElementType element);
ErrorCode AS_Pop(ArrayStack* stack);
ErrorCode AS_Peek(ArrayStack* stack);
int AS_GetSize(const ArrayStack* stack);

// 유틸리티 함수
bool AS_IsEmpty(const ArrayStack* stack);
bool AS_IsFull(const ArrayStack* stack);
void AS_Clear(ArrayStack* stack);
void AS_Print(const ArrayStack* stack);

#endif //ARRAY_STACK_H

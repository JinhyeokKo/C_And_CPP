#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "common.h"

typedef struct LL_Node {
    ElementType Data;
    struct LL_Node *PrevNode;
    struct LL_Node *NextNode;
} LL_Node;

typedef struct {
    LL_Node* Head;
    size_t Count;
} LinkedList;

// 생성자/소멸자
LinkedList* LL_Create(void);
void LL_Destroy(LinkedList* list);

// 기본 연산
ErrorCode LL_Append(LinkedList* list, ElementType data);
ErrorCode LL_InsertAfter(LinkedList* list, size_t position, ElementType data);
ErrorCode LL_InsertHead(LinkedList* list, ElementType data);
ErrorCode LL_Remove(LinkedList* list, size_t position);
ErrorCode LL_GetAt(const LinkedList* list, size_t position, ElementType* out_data);
size_t LL_GetCount(const LinkedList* list);

// 유틸리티 함수
bool LL_IsEmpty(const LinkedList* list);
void LL_Clear(LinkedList* list);
void LL_Print(const LinkedList* list);

#endif //LINKED_LIST_H

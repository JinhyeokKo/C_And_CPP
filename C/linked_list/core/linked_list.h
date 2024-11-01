#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "common.h"

typedef int ElementType;

typedef struct tagNode {
    ElementType Data;
    struct tagNode *PrevNode;
    struct tagNode *NextNode;
} Node;

typedef struct {
    Node* Head;
    size_t Count;
} LinkedList;

// 생성자/소멸자
LinkedList* SLL_Create(void);
void SLL_Destroy(LinkedList* list);

// 기본 연산
ErrorCode SLL_Append(LinkedList* list, ElementType data);
ErrorCode SLL_InsertAfter(LinkedList* list, size_t position, ElementType data);
ErrorCode SLL_InsertHead(LinkedList* list, ElementType data);
ErrorCode SLL_Remove(LinkedList* list, size_t position);
ErrorCode SLL_GetAt(const LinkedList* list, size_t position, ElementType* out_data);
size_t SLL_GetCount(const LinkedList* list);

// 유틸리티 함수
bool SLL_IsEmpty(const LinkedList* list);
void SLL_Clear(LinkedList* list);
void SLL_Print(const LinkedList* list);

#endif //LINKED_LIST_H

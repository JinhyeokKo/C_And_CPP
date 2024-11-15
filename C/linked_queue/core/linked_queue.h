#ifndef LINKED_QUEUE_H
#define LINKED_QUEUE_H

#include "common.h"

typedef struct LQ_Node {
    ElementType data;
    struct LQ_Node* next;
} LQ_Node;

typedef struct{
    LQ_Node* front;
    LQ_Node* rear;
    size_t count;
} LinkedQueue;

LinkedQueue* LQ_Create(void);
void LQ_Destroy(LinkedQueue* queue);
void LQ_DestroyNode(LQ_Node* queue);

ErrorCode LQ_Enqueue(LinkedQueue* queue, ElementType data);
ErrorCode LQ_Dequeue(LinkedQueue* queue);
ErrorCode LQ_Peek(const LinkedQueue* queue);
size_t LQ_GetCount(const LinkedQueue* queue);

void LQ_Clear(LinkedQueue* queue);
void LQ_Print(const LinkedQueue* queue);
bool LQ_IsEmpty(const LinkedQueue* queue);

#endif //LINKED_QUEUE_H

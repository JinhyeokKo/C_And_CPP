#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H

#include "common.h"

typedef struct CQ_Node {
    ElementType data;
} CQ_Node;

typedef struct {
    size_t capacity;
    size_t front;
    size_t rear;
    CQ_Node *nodes;
} CircularQueue;

CircularQueue* CQ_Create(size_t capacity);
void CQ_Destroy(CircularQueue *queue);
void CQ_Clear(CircularQueue *queue);
ErrorCode CQ_Enqueue(CircularQueue *queue, ElementType data);
ErrorCode CQ_Dequeue(CircularQueue *queue);
ErrorCode CQ_Peek(const CircularQueue *queue);
size_t CQ_GetSize(const CircularQueue *queue);
void CQ_Print(const CircularQueue *queue);
bool CQ_IsEmpty(const CircularQueue *queue);
bool CQ_IsFull(const CircularQueue *queue);

#endif //CIRCULAR_QUEUE_H
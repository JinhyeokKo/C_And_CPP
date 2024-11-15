#include "circular_queue.h"

CircularQueue* CQ_Create(size_t capacity) {
    CircularQueue* queue = (CircularQueue*)malloc(sizeof(CircularQueue));
    if (!queue) {
        return NULL;
    }

    queue->nodes = (CQ_Node*)malloc(sizeof(CQ_Node) * (capacity + 1));
    queue->capacity = capacity;
    queue->front = 0;
    queue->rear = 0;
    return queue;
}

void CQ_Destroy(CircularQueue *queue) {
    if(!queue) return;

    CQ_Clear(queue);
    free(queue->nodes);
    free(queue);
}

void CQ_Clear(CircularQueue *queue) {
    if(!queue) return;
    queue->front = 0;
    queue->rear = 0;
}

ErrorCode CQ_Enqueue(CircularQueue *queue, ElementType data) {
    if(!queue) return ERROR_INVALID_PARAMETER;
    if(CQ_IsFull(queue)) return ERROR_OUT_OF_RANGE;

    queue->nodes[queue->rear].data = data;
    queue->rear = (queue->rear + 1) % (queue->capacity + 1);

    return SUCCESS;
}

ErrorCode CQ_Dequeue(CircularQueue *queue) {
    if(!queue) return ERROR_INVALID_PARAMETER;
    if(CQ_IsEmpty(queue)) return ERROR_OUT_OF_RANGE;

    size_t position = queue->front;
    queue->front = (queue->front + 1) % (queue->capacity + 1);
    printf("제거된 데이터: %d", queue->nodes[position].data.integer);

    return SUCCESS;
}

ErrorCode CQ_Peek(const CircularQueue *queue) {
    if(!queue) return ERROR_INVALID_PARAMETER;
    if(CQ_IsEmpty(queue)) return ERROR_OUT_OF_RANGE;

    printf("선입 데이터: %d", queue->nodes[queue->front].data.integer);
    return SUCCESS;
}

size_t CQ_GetSize(const CircularQueue *queue) {
    if(!queue) return 0;

    if(queue->front <= queue->rear) {
        return queue->rear - queue->front;
    } else {
        return queue->rear + (queue->capacity - queue->front) + 1;
    }
}

void CQ_Print(const CircularQueue *queue) {
    if(!queue || CQ_IsEmpty(queue)) {
        printf("큐가 비어있습니다.\n");
        return;
    }
    printf("큐 내용:");
    size_t position = queue->front;
    while(true) {
        printf("%d", queue->nodes[position].data.integer);
        position = (position + 1) % (queue->capacity + 1);

        if (position == queue->rear) {
            break;
        }

        printf(" -> ");
    }
    printf("\n총 데이터 개수: %zu\n", CQ_GetSize(queue));
    printf("큐의 크기: %zu\n", queue->capacity);
}

bool CQ_IsEmpty(const CircularQueue *queue) {
    return queue->front == queue->rear;
}

bool CQ_IsFull(const CircularQueue *queue) {
    if(queue->front < queue->rear) {
        return (queue->rear - queue->front) == queue->capacity;
    } else {
        return (queue->rear + 1) == queue->front;
    }
}
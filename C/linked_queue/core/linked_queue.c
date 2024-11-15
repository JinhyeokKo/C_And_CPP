#include "linked_queue.h"

static LQ_Node* CreateNode(ElementType data) {
    LQ_Node* new_node = (LQ_Node*)malloc(sizeof(LQ_Node));
    if(!new_node) return NULL;

    new_node->data.string = (char*)malloc(strlen(data.string) + 1);
    if(!new_node->data.string) {
        free(new_node);
        return NULL;
    }
    strcpy(new_node->data.string, data.string);
    new_node->next = NULL;

    return new_node;
}

LinkedQueue* LQ_Create(void) {
    LinkedQueue* queue = (LinkedQueue*)malloc(sizeof(LinkedQueue));
    if(!queue) {
        return NULL;
    }

    queue->count = 0;
    queue->front = NULL;
    queue->rear = NULL;

    return queue;
}

void LQ_Destroy(LinkedQueue* queue) {
    if(!queue) return;

    LQ_Clear(queue);
    free(queue);
}

void LQ_DestroyNode(LQ_Node* node) {
    if(!node) return;
    free(node->data.string);
    free(node);
}

ErrorCode LQ_Enqueue(LinkedQueue* queue, ElementType data) {
    if(!queue) return ERROR_INVALID_PARAMETER;

    LQ_Node* new_node = CreateNode(data);
    if(!new_node) return ERROR_MEMORY_ALLOCATION;

    if(queue->front == NULL || queue->rear == NULL) {
        queue->front = new_node;
        queue->rear = new_node;
        queue->count++;
    } else {
        queue->rear->next = new_node;
        queue->rear = new_node;
        queue->count++;
    }

    return SUCCESS;
}

ErrorCode LQ_Dequeue(LinkedQueue* queue) {
    if(!queue) return ERROR_INVALID_PARAMETER;
    if(LQ_IsEmpty(queue)) return ERROR_OUT_OF_RANGE;

    LQ_Node* node = queue->front;

    if (queue->front->next == NULL) {
        queue->front = NULL;
        queue->rear = NULL;
    } else {
        queue->front = queue->front->next;
    }

    queue->count--;
    LQ_DestroyNode(node);

    return SUCCESS;
}

ErrorCode LQ_Peek(const LinkedQueue* queue) {
    if(!queue) return ERROR_INVALID_PARAMETER;
    if(LQ_IsEmpty(queue)) return ERROR_OUT_OF_RANGE;

    printf("선입 데이터: %s", queue->front->data.string);
    return SUCCESS;
}

size_t LQ_GetCount(const LinkedQueue* queue) {
    return queue ? queue->count : 0;
}

void LQ_Clear(LinkedQueue* queue) {
    if(!queue || !queue->front) return;

    while(!LQ_IsEmpty(queue)) {
        LQ_Dequeue(queue);
    }
}

void LQ_Print(const LinkedQueue* queue) {
    if(!queue || LQ_IsEmpty(queue)) {
        printf("큐가 비어있습니다.\n");
        return;
    }

    printf("큐 내용:");
    LQ_Node* node = queue->front;
    do {
        printf("%s", node->data.string);
        if(node->next) {
            printf(" -> ");
        }
        node = node->next;
    } while (node);

    printf("\n총 데이터 개수: %zu\n", queue->count);
}

bool LQ_IsEmpty(const LinkedQueue* queue) {
    return queue->count == 0;
}
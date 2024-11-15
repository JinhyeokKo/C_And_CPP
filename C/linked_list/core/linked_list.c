#include "linked_list.h"

static LL_Node* CreateNode(ElementType data) {
    LL_Node* new_node = (LL_Node*)malloc(sizeof(LL_Node));
    if(!new_node) {
        return NULL;
    }

    new_node->data = data;
    // 단순 및 더블에서
    // new_node->PrevNode = NULL;
    // new_node->NextNode = NULL;
    // 환형에서
    new_node->PrevNode = new_node;
    new_node->NextNode = new_node;

    return new_node;
}

LinkedList* LL_Create(void) {
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    if (!list) {
        return NULL;
    }

    list->head = NULL;
    list->count = 0;
    return list;
}

void LL_Destroy(LinkedList* list) {
    if (!list) return;

    LL_Clear(list);
    free(list);
}

void LL_Clear(LinkedList* list) {
    if (!list || !list->head) return;

    LL_Node* current = list->head;

    do {
        LL_Node* next = current->NextNode;
        free(current);
        current = next;
    } while (current && current != list->head);

    list->head = NULL;
    list->count = 0;
}

ErrorCode LL_Append(LinkedList* list, ElementType data) {
    if (!list) return ERROR_INVALID_PARAMETER;

    LL_Node* tail = CreateNode(data);
    if (!tail) return ERROR_MEMORY_ALLOCATION;

    if (list->head == NULL) {
        list->head = tail;
    } else {
        LL_Node* current = list->head;
        // 단순 및 더블에서
        // while (current->NextNode) {
        //     current = current->NextNode;
        // }
        // tail->PrevNode = current;
        // current->NextNode = tail;

        // 환형에서
        tail->PrevNode = current->PrevNode;
        tail->NextNode = current;
        current->PrevNode->NextNode = tail;
        current->PrevNode = tail;
    }

    list->count++;
    return SUCCESS;
}

ErrorCode LL_InsertAfter(LinkedList* list, ElementType position, ElementType data) {
    if (!list) return ERROR_INVALID_PARAMETER;
    if ((size_t)position.integer >= list->count) return ERROR_OUT_OF_RANGE;

    LL_Node* current = list->head;
    for (int i = 0; i < position.integer; i++) {
        current = current->NextNode;
    }

    LL_Node* new_node = CreateNode(data);
    if (!new_node) return ERROR_MEMORY_ALLOCATION;

    new_node->PrevNode = current;
    new_node->NextNode = current->NextNode;
    new_node->NextNode->PrevNode = new_node;
    current->NextNode = new_node;
    list->count++;

    return SUCCESS;
}

ErrorCode LL_InsertHead(LinkedList* list, ElementType data) {
    if (!list) return ERROR_INVALID_PARAMETER;

    LL_Node* head = CreateNode(data);
    if (!head) return ERROR_MEMORY_ALLOCATION;

    if(list->head == NULL) {
        list->head = head;
    }else {
        head->NextNode = list->head;
        head->PrevNode = list->head->PrevNode;
        list->head->PrevNode->NextNode = head;
        list->head->PrevNode = head;
        list->head = head;
    }

    list->count++;
    return SUCCESS;
}

ErrorCode LL_Remove(LinkedList* list, ElementType position) {
    if (!list || !list->head) return ERROR_INVALID_PARAMETER;
    if ((size_t)position.integer >= list->count) return ERROR_OUT_OF_RANGE;

    LL_Node* to_remove = list->head;

    if (position.integer == 0) {
        // 단순 및 더블에서
        // list->head = list->head->NextNode;
        // list->head->PrevNode = NULL;
        // 환형에서
        if (list->count == 1) {
            list->head = NULL;
        } else {
            LL_Node* tail = list->head->PrevNode;
            list->head = list->head->NextNode;
            list->head->PrevNode = tail;
            tail->NextNode = list->head;
        }
    } else {
        for (size_t i = 0; i < (size_t)position.integer; i++) {
            to_remove = to_remove->NextNode;
        }
        to_remove->PrevNode->NextNode = to_remove->NextNode;
        to_remove->NextNode->PrevNode = to_remove->PrevNode;
    }

    free(to_remove);
    list->count--;
    return SUCCESS;
}

ErrorCode LL_GetAt(const LinkedList* list, ElementType position) {
    if (!list) return ERROR_INVALID_PARAMETER;
    if ((size_t)position.integer >= list->count) return ERROR_OUT_OF_RANGE;

    LL_Node* current = list->head;
    for (size_t i = 0; i < (size_t)position.integer; i++) {
        current = current->NextNode;
    }
    printf("%zu번 위치의 데이터: %d\n", (size_t)position.integer, (int)current->data.integer);
    return SUCCESS;
}

size_t LL_GetCount(const LinkedList* list) {
    return list ? list->count : 0;
}

bool LL_IsEmpty(const LinkedList* list) {
    return list->count == 0;
}

void LL_Print(const LinkedList* list) {
    if (!list || LL_IsEmpty(list)) {
        printf("리스트가 비어있습니다.\n");
        return;
    }

    printf("리스트 내용: ");
    LL_Node* current = list->head;
    do {
        printf("%d -> ", (int)current->data.integer);
        current = current->NextNode;
    }while(current && current!=list->head);
    // 단순 및 더블에서
    // printf("NULL\n");
    // 환형에서
    printf("List head\n");
    printf("총 노드 개수: %zu\n", list->count);
}
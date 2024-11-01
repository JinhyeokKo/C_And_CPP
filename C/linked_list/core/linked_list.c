#include "linked_list.h"

static Node* CreateNode(ElementType data) {
    Node* new_node = (Node*)malloc(sizeof(Node));

    new_node->Data = data;
    // 단순 및 더블에서
    // new_node->PrevNode = NULL;
    // new_node->NextNode = NULL;
    // 환형에서
    new_node->PrevNode = new_node;
    new_node->NextNode = new_node;

    return new_node;
}

LinkedList* SLL_Create(void) {
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    if (!list) {
        return NULL;
    }

    list->Head = NULL;
    list->Count = 0;
    return list;
}

void SLL_Destroy(LinkedList* list) {
    if (!list) return;

    SLL_Clear(list);
    free(list);
}

void SLL_Clear(LinkedList* list) {
    if (!list) return;

    Node* current = list->Head;
    while (current) {
        Node* next = current->NextNode;
        free(current);
        current = next;
    }

    list->Head = NULL;
    list->Count = 0;
}

ErrorCode SLL_Append(LinkedList* list, ElementType data) {
    if (!list) return ERROR_INVALID_PARAMETER;

    Node* tail = CreateNode(data);
    if (!tail) return ERROR_MEMORY_ALLOCATION;

    if (list->Head == NULL) {
        list->Head = tail;
    } else {
        Node* current = list->Head;
        // 단순 및 더블에서
        // while (current->NextNode) {
        //     current = current->NextNode;
        // }
        // tail->PrevNode = current;
        // current->NextNode = tail;

        // 환형에서
        current->PrevNode->NextNode = tail;
        tail->NextNode = current;
        tail->PrevNode = current->PrevNode;
        current->PrevNode = tail;
    }

    list->Count++;
    return SUCCESS;
}

ErrorCode SLL_InsertAfter(LinkedList* list, size_t position, ElementType data) {
    if (!list) return ERROR_INVALID_PARAMETER;
    if (position >= list->Count) return ERROR_OUT_OF_RANGE;

    Node* current = list->Head;
    for (size_t i = 0; i < position; i++) {
        current = current->NextNode;
    }

    Node* new_node = CreateNode(data);
    if (!new_node) return ERROR_MEMORY_ALLOCATION;

    new_node->PrevNode = current;
    new_node->NextNode = current->NextNode;
    new_node->NextNode->PrevNode = new_node;
    current->NextNode = new_node;
    list->Count++;

    return SUCCESS;
}

ErrorCode SLL_InsertHead(LinkedList* list, ElementType data) {
    if (!list) return ERROR_INVALID_PARAMETER;

    Node* head = CreateNode(data);
    if (!head) return ERROR_MEMORY_ALLOCATION;

    list->Head->PrevNode = head;
    head->NextNode = list->Head;
    list->Head = head;
    list->Count++;

    return SUCCESS;
}

ErrorCode SLL_Remove(LinkedList* list, size_t position) {
    if (!list || !list->Head) return ERROR_INVALID_PARAMETER;
    if (position >= list->Count) return ERROR_OUT_OF_RANGE;

    Node* to_remove = list->Head;

    if (position == 0) {
        // 단순 및 더블에서
        // list->Head = list->Head->NextNode;
        // list->Head->PrevNode = NULL;
        // 환형에서
        if (list->Count == 1) {
            list->Head = NULL;
        } else {
            Node* tail = list->Head->PrevNode;
            list->Head = list->Head->NextNode;
            list->Head->PrevNode = tail;
            tail->NextNode = list->Head;
        }
    } else {
        for (size_t i = 0; i < position; i++) {
            to_remove = to_remove->NextNode;
        }
        to_remove->PrevNode->NextNode = to_remove->NextNode;
        to_remove->NextNode->PrevNode = to_remove->PrevNode;
    }

    free(to_remove);
    list->Count--;
    return SUCCESS;
}

ErrorCode SLL_GetAt(const LinkedList* list, size_t position, ElementType* out_data) {
    if (!list || !out_data) return ERROR_INVALID_PARAMETER;
    if (position >= list->Count) return ERROR_OUT_OF_RANGE;

    Node* current = list->Head;
    for (size_t i = 0; i < position; i++) {
        current = current->NextNode;
    }

    *out_data = current->Data;
    return SUCCESS;
}

size_t SLL_GetCount(const LinkedList* list) {
    return list ? list->Count : 0;
}

bool SLL_IsEmpty(const LinkedList* list) {
    return !list || list->Count == 0;
}

void SLL_Print(const LinkedList* list) {
    if (!list || SLL_IsEmpty(list)) {
        printf("리스트가 비어있습니다.\n");
        return;
    }

    printf("리스트 내용: ");
    Node* current = list->Head;
    while (current) {
        printf("%d -> ", current->Data);
        current = current->NextNode;
    }
    printf("NULL\n");
    printf("총 노드 개수: %zu\n", list->Count);
}
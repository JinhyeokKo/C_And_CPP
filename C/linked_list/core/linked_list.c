#include "linked_list.h"

static LL_Node* CreateNode(ElementType data) {
    LL_Node* new_node = (LL_Node*)malloc(sizeof(LL_Node));

    new_node->Data = data;
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

    list->Head = NULL;
    list->Count = 0;
    return list;
}

void LL_Destroy(LinkedList* list) {
    if (!list) return;

    LL_Clear(list);
    free(list);
}

void LL_Clear(LinkedList* list) {
    if (!list || !list->Head) return;

    LL_Node* current = list->Head;

    do {
        LL_Node* next = current->NextNode;
        free(current);
        current = next;
    } while (current && current != list->Head);

    list->Head = NULL;
    list->Count = 0;
}

ErrorCode LL_Append(LinkedList* list, ElementType data) {
    if (!list) return ERROR_INVALID_PARAMETER;

    LL_Node* tail = CreateNode(data);
    if (!tail) return ERROR_MEMORY_ALLOCATION;

    if (list->Head == NULL) {
        list->Head = tail;
    } else {
        LL_Node* current = list->Head;
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

    list->Count++;
    return SUCCESS;
}

ErrorCode LL_InsertAfter(LinkedList* list, size_t position, ElementType data) {
    if (!list) return ERROR_INVALID_PARAMETER;
    if (position >= list->Count) return ERROR_OUT_OF_RANGE;

    LL_Node* current = list->Head;
    for (size_t i = 0; i < position; i++) {
        current = current->NextNode;
    }

    LL_Node* new_node = CreateNode(data);
    if (!new_node) return ERROR_MEMORY_ALLOCATION;

    new_node->PrevNode = current;
    new_node->NextNode = current->NextNode;
    new_node->NextNode->PrevNode = new_node;
    current->NextNode = new_node;
    list->Count++;

    return SUCCESS;
}

ErrorCode LL_InsertHead(LinkedList* list, ElementType data) {
    if (!list) return ERROR_INVALID_PARAMETER;

    LL_Node* head = CreateNode(data);
    if (!head) return ERROR_MEMORY_ALLOCATION;

    if(list->Head == NULL) {
        list->Head = head;
    }else {
        head->NextNode = list->Head;
        head->PrevNode = list->Head->PrevNode;
        list->Head->PrevNode->NextNode = head;
        list->Head->PrevNode = head;
        list->Head = head;
    }

    list->Count++;
    return SUCCESS;
}

ErrorCode LL_Remove(LinkedList* list, size_t position) {
    if (!list || !list->Head) return ERROR_INVALID_PARAMETER;
    if (position >= list->Count) return ERROR_OUT_OF_RANGE;

    LL_Node* to_remove = list->Head;

    if (position == 0) {
        // 단순 및 더블에서
        // list->Head = list->Head->NextNode;
        // list->Head->PrevNode = NULL;
        // 환형에서
        if (list->Count == 1) {
            list->Head = NULL;
        } else {
            LL_Node* tail = list->Head->PrevNode;
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

ErrorCode LL_GetAt(const LinkedList* list, size_t position, ElementType* out_data) {
    if (!list || !out_data) return ERROR_INVALID_PARAMETER;
    if (position >= list->Count) return ERROR_OUT_OF_RANGE;

    LL_Node* current = list->Head;
    for (size_t i = 0; i < position; i++) {
        current = current->NextNode;
    }

    *out_data = current->Data;
    return SUCCESS;
}

size_t LL_GetCount(const LinkedList* list) {
    return list ? list->Count : 0;
}

bool LL_IsEmpty(const LinkedList* list) {
    return list->Count == 0;
}

void LL_Print(const LinkedList* list) {
    if (!list || LL_IsEmpty(list)) {
        printf("리스트가 비어있습니다.\n");
        return;
    }

    printf("리스트 내용: ");
    LL_Node* current = list->Head;
    do {
        printf("%d -> ", current->Data);
        current = current->NextNode;
    }while(current && current!=list->Head);
    // 단순 및 더블에서
    // printf("NULL\n");
    // 환형에서
    printf("List Head\n");
    printf("총 노드 개수: %zu\n", list->Count);
}
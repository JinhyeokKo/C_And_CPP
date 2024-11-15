#include "menu_handler.h"
#include "linked_list.h"
#include "array_stack.h"
#include "circular_queue.h"
#include "linked_queue.h"
#include "input_handler.h"
#include "linked_list_stack.h"

void Menu_DisplayOptions(const char* type) {
    printf("\n=== %s 관리 프로그램 ===\n", type);
    printf("1. 데이터(노드) 추가\n");
    printf("2. 데이터(노드) 삭제\n");
    printf("3. 최상단 데이터(노드) 조회\n");
    printf("4. 데이터(노드) 개수 확인\n");
    printf("5. 전체 %s 출력\n", type);
    printf("6. %s 초기화\n", type);
    printf("0. 종료\n");
    printf("==============================\n");
}

MenuHandler linkedListStackHandler = {
    .value = (bool (*)(const char *, ElementType*))Input_GetString,
    .input.input = (ErrorCode (*)(void *, ElementType))LLS_Push,
    .output.output = (ErrorCode (*)(void *))LLS_Pop,
    .peek.peek = (ErrorCode (*)(void *))LLS_Peek,
    .count = (size_t (*)(void *))LLS_GetCount,
    .print = (void (*)(void *))LLS_Print,
    .clear = (void (*)(void *))LLS_Clear,
    .destroy = (void (*)(void *))LLS_Destroy,
    .structure_type = TYPE_LINKED_LIST_STACK
};

MenuHandler arrayStackHandler = {
    .value = (bool (*)(const char *, ElementType*))Input_GetInteger,
    .input.input = (ErrorCode (*)(void *, ElementType))AS_Push,
    .output.output = (ErrorCode (*)(void *))AS_Pop,
    .peek.peek = (ErrorCode (*)(void *))AS_Peek,
    .count = (size_t (*)(void *))AS_GetCount,
    .print = (void (*)(void *))AS_Print,
    .clear = (void (*)(void *))AS_Clear,
    .destroy = (void (*)(void *))AS_Destroy,
    .structure_type = TYPE_ARRAY_STACK
};

MenuHandler circularQueueHandler = {
    .value = (bool (*)(const char *, ElementType*))Input_GetInteger,
    .input.input = (ErrorCode (*)(void *, ElementType))CQ_Enqueue,
    .output.output = (ErrorCode (*)(void *))CQ_Dequeue,
    .peek.peek = (ErrorCode (*)(void *))CQ_Peek,
    .count = (size_t (*)(void *))CQ_GetSize,
    .print = (void (*)(void *))CQ_Print,
    .clear = (void (*)(void *))CQ_Clear,
    .destroy = (void (*)(void *))CQ_Destroy,
    .structure_type = TYPE_CIRCULAR_QUEUE
};

MenuHandler linkedQueueHandler = {
    .value = (bool (*)(const char *, ElementType*))Input_GetString,
    .input.input = (ErrorCode (*)(void *, ElementType))LQ_Enqueue,
    .output.output = (ErrorCode (*)(void *))LQ_Dequeue,
    .peek.peek = (ErrorCode (*)(void *))LQ_Peek,
    .count = (size_t (*)(void *))LQ_GetCount,
    .print = (void (*)(void *))LQ_Print,
    .clear = (void (*)(void *))LQ_Clear,
    .destroy = (void (*)(void *))LQ_Destroy,
    .structure_type = TYPE_LINKED_QUEUE
};

MenuHandler linkedListHandler = {
    .value = (bool (*)(const char *, ElementType*))Input_GetInteger,
    .input = {
        .list_append = (ErrorCode (*)(void *, ElementType))LL_Append,
        .list_insert_after = (ErrorCode (*)(void *, ElementType, ElementType))LL_InsertAfter,
        .list_insert_head = (ErrorCode (*)(void *, ElementType))LL_InsertHead,
    },
    .output.list_remove = (ErrorCode (*)(void *, ElementType))LL_Remove,
    .peek.list_get_at = (ErrorCode (*)(void *, ElementType))LL_GetAt,
    .count = (size_t (*)(void *))LL_GetCount,
    .print = (void (*)(void *))LL_Print,
    .clear = (void (*)(void *))LL_Clear,
    .destroy = (void (*)(void *))LL_Destroy,
    .structure_type = TYPE_LINKED_LIST
};

const char* STRUCTURE_TYPE_STRINGS[] = {
    "연결 리스트",
    "연결 리스트 스택",
    "배열 스택",
    "순환 큐",
    "연결 큐"
};

ErrorCode Menu_ProcessChoice(void *structure, MenuChoice choice, MenuHandler *handler) {
    if (!structure || !handler) return ERROR_INVALID_PARAMETER;

    ElementType value, position;

    switch (choice) {
        case MENU_INPUT:
            if (!handler->value("추가할 데이터: ", &value)) {
                printf("잘못된 입력입니다.\n");
                return ERROR_INVALID_PARAMETER;
            }
            if (handler == &linkedListHandler) {
                printf("1. 끝에 추가\n2. 특정 위치 다음에 추가\n3. 처음에 추가\n");
                if (!Input_GetInteger("선택: ", (ElementType*)&choice)) {
                    printf("잘못된 입력입니다. 다시 시도해주세요.\n");
                }
                switch (choice) {
                    case 1:
                        return handler->input.list_append(structure, value);
                    case 2:
                        if (!Input_GetInteger("추가할 위치: ", &position)) {
                            printf("잘못된 입력입니다.\n");
                            return ERROR_INVALID_PARAMETER;
                        }
                        return handler->input.list_insert_after(structure, position, value);
                    case 3:
                        return handler->input.list_insert_head(structure, value);
                    default:
                        printf("잘못된 선택입니다.\n");
                        return ERROR_INVALID_PARAMETER;
                }
            }
            return handler->input.input(structure, value);

        case MENU_OUTPUT:
            if (handler == &linkedListHandler) {
                if (!Input_GetInteger("삭제할 위치: ", &position)) {
                    printf("잘못된 입력입니다.\n");
                    return ERROR_INVALID_PARAMETER;
                }
                return handler->output.list_remove(structure, position);
            }
            return handler->output.output(structure);

        case MENU_PEEK:
            if (handler == &linkedListHandler) {
                if (!Input_GetInteger("조회할 위치: ", &position)) {
                    printf("잘못된 입력입니다.\n");
                    return ERROR_INVALID_PARAMETER;
                }
                return handler->peek.list_get_at(structure, position);
            }
            return handler->peek.peek(structure);

        case MENU_COUNT:
            printf("현재 데이터의 개수: %zu \n", handler->count(structure));
            return SUCCESS;

        case MENU_PRINT:
            handler->print(structure);
            return SUCCESS;

        case MENU_CLEAR:
            handler->clear(structure);
            return SUCCESS;

        default:
            printf("잘못된 메뉴 선택입니다.\n");
            return ERROR_INVALID_PARAMETER;
    }
}

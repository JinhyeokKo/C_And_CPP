#include "linked_list_stack_menu_handler.h"
#include "input_handler.h"

void LLS_Menu_DisplayOptions(void) {
    printf("\n=== 연결 리스트 스택 관리 프로그램 ===\n");
    printf("1. 데이터 추가 (끝)\n");
    printf("2. 데이터 삭제\n");
    printf("3. 최상단 데이터 조회\n");
    printf("4. 데이터 개수 확인\n");
    printf("5. 전체 스택 출력\n");
    printf("6. 스택 초기화\n");
    printf("0. 종료\n");
    printf("===============================\n");
}

ErrorCode LLS_Menu_ProcessChoice(LinkedListStack* stack, LLS_MenuChoice choice) {
    if(!stack) return ERROR_INVALID_PARAMETER;

    char* value = NULL;

    switch(choice) {
        case MENU_PUSH:
            if (!Input_GetString("추가할 데이터: ", &value)) {
                printf("잘못된 입력입니다.\n");
                return ERROR_INVALID_PARAMETER;
            }
        return LLS_Push(stack, value);

        case MENU_POP:
            return LLS_Pop(stack);

        case MENU_PEEK:
            return LLS_Peek(stack);

        case MENU_GET_COUNT:
            printf("현재 데이터의 개수: %zu", LLS_GetCount(stack));
        return SUCCESS;

        case MENU_PRINT_ALL:
            LLS_Print(stack);
        return SUCCESS;

        case MENU_CLEAR:
            LLS_Clear(stack);
        printf("스택이 초기화되었습니다.\n");
        return SUCCESS;

        default:
            printf("잘못된 메뉴 선택입니다.\n");
        return ERROR_INVALID_PARAMETER;
    }
}
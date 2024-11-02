#include "array_stack_menu_handler.h"
#include "input_handler.h"

void AS_Menu_DisplayOptions(void) {
    printf("\n=== 배열 스택 관리 프로그램 ===\n");
    printf("1. 데이터 추가 (끝)\n");
    printf("2. 데이터 삭제\n");
    printf("3. 최상단 데이터 조회\n");
    printf("4. 데이터 개수 확인\n");
    printf("5. 전체 스택 출력\n");
    printf("6. 스택 초기화\n");
    printf("0. 종료\n");
    printf("===============================\n");
}

ErrorCode AS_Menu_ProcessChoice(ArrayStack *stack, AS_MenuChoice choice) {
    if(!stack) return ERROR_INVALID_PARAMETER;

    int value;

    switch(choice) {
        case MENU_PUSH:
            if (!Input_GetInteger("추가할 데이터: ", &value)) {
                printf("잘못된 입력입니다.\n");
                return ERROR_INVALID_PARAMETER;
            }
            return AS_Push(stack, value);

        case MENU_POP:
            return AS_Pop(stack);

        case MENU_PEEK:
            return AS_Peek(stack);

        case MENU_GET_SIZE:
            printf("현재 데이터의 개수: %d", AS_GetSize(stack));
            return SUCCESS;

        case MENU_PRINT_ALL:
            AS_Print(stack);
            return SUCCESS;

        case MENU_CLEAR:
            AS_Clear(stack);
            printf("스택이 초기화되었습니다.\n");
            return SUCCESS;

        default:
            printf("잘못된 메뉴 선택입니다.\n");
            return ERROR_INVALID_PARAMETER;
    }
}
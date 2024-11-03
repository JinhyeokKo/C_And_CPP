#include "linked_list_stack_boot.h"
#include "input_handler.h"
#include "linked_list_stack_menu_handler.h"

int Boot_LinkedListStack(void) {

    LinkedListStack* stack = LLS_Create();
    if (!stack) {
        printf("스택 생성에 실패했습니다.\n");
        return EXIT_FAILURE;
    }

    LLS_MenuChoice choice;

    do {
        LLS_Menu_DisplayOptions();

        if (!Input_GetInteger("선택: ", (int*)&choice)) {
            printf("잘못된 입력입니다. 다시 시도해주세요.\n");
            continue;
        }

        if (choice == MENU_EXIT) break;

        ErrorCode result = LLS_Menu_ProcessChoice(stack, choice);
        if (result != SUCCESS) {
            switch (result) {
                case ERROR_INVALID_PARAMETER:
                    printf("잘못된 매개변수입니다.\n");
                break;

                case ERROR_MEMORY_ALLOCATION:
                    printf("메모리 할당에 실패했습니다.\n");
                break;

                case ERROR_OUT_OF_RANGE:
                    printf("범위를 벗어났습니다.\n");
                break;

                default:
                    printf("알 수 없는 오류가 발생했습니다.\n");
            }
        }

        Input_WaitForEnter();

    } while (true);

    LLS_Destroy(stack);
    printf("연결 리스트 스택을 종료합니다.\n");

    return SUCCESS;
}
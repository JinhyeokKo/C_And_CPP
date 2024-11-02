#include "common.h"
#include "linked_list.h"
#include "input_handler.h"
#include "menu_handler.h"

int main(void) {
    // 버퍼링 비활성화(디버깅용)
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    LinkedList* list = LL_Create();
    if (!list) {
        fprintf(stderr, "리스트 생성에 실패했습니다.\n");
        return EXIT_FAILURE;
    }

    MenuChoice choice;

    do {
        Menu_DisplayOptions();

        if (!Input_GetInteger("선택: ", (int*)&choice)) {
            printf("잘못된 입력입니다. 다시 시도해주세요.\n");
            continue;
        }

        if (choice == MENU_EXIT) break;

        ErrorCode result = Menu_ProcessChoice(list, choice);
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

    LL_Destroy(list);
    printf("프로그램을 종료합니다.\n");
    return EXIT_SUCCESS;
}

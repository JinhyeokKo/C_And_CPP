#include "common.h"
#include "input_handler.h"
#include "boot_handler.h"

int main(void) {
    // 버퍼링 비활성화(디버깅용)
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    BootChoice choice;

    do {
        Boot_DisplayOptions();

        if (!Input_GetInteger("선택: ", (ElementType*)&choice)) {
            printf("잘못된 입력입니다. 다시 시도해주세요.\n");
            continue;
        }

        if (choice == BOOT_EXIT) break;

        int result = Boot_ProcessChoice(choice);

        if(result == EXIT_FAILURE) {
            return EXIT_FAILURE;
        }

        Input_WaitForEnter();

    } while (true);

    printf("프로그램을 종료합니다.\n");
    return EXIT_SUCCESS;
}

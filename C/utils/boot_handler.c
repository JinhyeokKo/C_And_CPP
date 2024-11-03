#include "boot_handler.h"

#include <linked_list_stack_boot.h>

void Boot_DisplayOptions(void) {
    printf("\n=== 자료구조 선택하기 ===\n");
    printf("1. 연결 리스트\n");
    printf("2. 배열 스택\n");
    printf("3. 연결 리스트 스택\n");
    printf("0. 종료\n");
    printf("======================\n");
}

int Boot_ProcessChoice(BootChoice choice) {
    switch (choice) {
        case BOOT_LINKED_LIST:
            return Boot_LinkedList();

        case BOOT_ARRAY_STACK:
            return Boot_ArrayStack();

        case BOOT_LINKED_LIST_STACK:
            return Boot_LinkedListStack();

        default:
            printf("잘못된 메뉴 선택입니다.\n");
        return 0;
    }
}
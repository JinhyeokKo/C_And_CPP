#include "boot_handler.h"
#include "input_handler.h"

void Boot_DisplayOptions(void) {
    printf("\n=== 자료구조 선택하기 ===\n");
    printf("1. 연결 리스트\n");
    printf("2. 배열 스택\n");
    printf("3. 연결 리스트 스택\n");
    printf("4. 순환 큐\n");
    printf("5. 연결 큐\n");
    printf("0. 종료\n");
    printf("======================\n");
}

static void CapacitySet(int* capacity) {
    int temp;
    do {
        if (!Input_GetInteger("크기: ", (ElementType*)&temp)) {
            printf("잘못된 입력입니다. 다시 시도해주세요.\n");
            continue;
        }
        *capacity = temp;
    } while (!temp);
}

int Boot_ProcessChoice(BootChoice choice) {
    int capacity = 0;
    switch (choice) {
        case BOOT_LINKED_LIST:
            LinkedList* list = LL_Create();
            return Boot_Structure(list, &linkedListHandler);

        case BOOT_ARRAY_STACK:
            CapacitySet(&capacity);
            ArrayStack* stack = AS_Create(capacity);
            return Boot_Structure(stack, &arrayStackHandler);

        case BOOT_LINKED_LIST_STACK:
            LinkedListStack* linked_list_stack = LLS_Create();
            return Boot_Structure(linked_list_stack, &linkedListStackHandler);

        case BOOT_CIRCULAR_QUEUE:
            CapacitySet(&capacity);
            CircularQueue* queue = CQ_Create(capacity);
            return Boot_Structure(queue, &circularQueueHandler);

        case BOOT_LINKED_QUEUE:
            LinkedQueue* linked_queue = LQ_Create();
            return Boot_Structure(linked_queue, &linkedQueueHandler);

        default:
            printf("잘못된 메뉴 선택입니다.\n");
            return EXIT_FAILURE;
    }
}

int Boot_Structure(void* structure, MenuHandler* handler) {
    if (!structure) {
        printf("구조체 생성에 실패했습니다.\n");
        return EXIT_FAILURE;
    }

    MenuChoice choice;
    const char* type = STRUCTURE_TYPE_STRINGS[handler->structure_type];

    do {
        Menu_DisplayOptions(type);

        if (!Input_GetInteger("선택: ", (ElementType*)&choice)) {
            printf("잘못된 입력입니다. 다시 시도해주세요.\n");
            continue;
        }

        if (choice == MENU_EXIT) break;

        ErrorCode result = Menu_ProcessChoice(structure, choice, handler);
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

    handler->destroy(structure);
    printf("%s를 종료합니다.\n", type);
    return SUCCESS;
}
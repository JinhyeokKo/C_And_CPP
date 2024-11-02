#include "menu_handler.h"
#include "input_handler.h"

void Menu_DisplayOptions(void) {
    printf("\n=== 링크드 리스트 관리 프로그램 ===\n");
    printf("1. 노드 추가 (끝)\n");
    printf("2. 특정 위치 뒤에 노드 추가\n");
    printf("3. 노드 추가 (머리)\n");
    printf("4. 노드 삭제\n");
    printf("5. 특정 위치 노드 조회\n");
    printf("6. 노드 개수 확인\n");
    printf("7. 전체 리스트 출력\n");
    printf("8. 리스트 초기화\n");
    printf("0. 종료\n");
    printf("===============================\n");
}

ErrorCode Menu_ProcessChoice(LinkedList* list, MenuChoice choice) {
    if (!list) return ERROR_INVALID_PARAMETER;
    
    int value, position;
    ElementType data;
    ErrorCode result;
    
    switch (choice) {
        case MENU_APPEND:
            if (!Input_GetInteger("추가할 데이터: ", &value)) {
                printf("잘못된 입력입니다.\n");
                return ERROR_INVALID_PARAMETER;
            }
            return LL_Append(list, value);
            
        case MENU_INSERT_AFTER:
            if (!Input_GetInteger("추가할 데이터: ", &value)) {
                printf("잘못된 입력입니다.\n");
                return ERROR_INVALID_PARAMETER;
            }
            if (!Input_GetInteger("추가할 위치: ", &position)) {
                printf("잘못된 입력입니다.\n");
                return ERROR_INVALID_PARAMETER;
            }
            return LL_InsertAfter(list, position, value);
            
        case MENU_INSERT_HEAD:
            if (!Input_GetInteger("추가할 데이터: ", &value)) {
                printf("잘못된 입력입니다.\n");
                return ERROR_INVALID_PARAMETER;
            }
            return LL_InsertHead(list, value);
            
        case MENU_REMOVE:
            if (!Input_GetInteger("삭제할 위치: ", &position)) {
                printf("잘못된 입력입니다.\n");
                return ERROR_INVALID_PARAMETER;
            }
            return LL_Remove(list, position);
            
        case MENU_GET_AT:
            if (!Input_GetInteger("조회할 위치: ", &position)) {
                printf("잘못된 입력입니다.\n");
                return ERROR_INVALID_PARAMETER;
            }
            result = LL_GetAt(list, position, &data);
            if (result == SUCCESS) {
                printf("%d번 위치의 데이터: %d\n", position, data);
            }
            return result;
            
        case MENU_GET_COUNT:
            printf("현재 노드 개수: %zu\n", LL_GetCount(list));
            return SUCCESS;
            
        case MENU_PRINT_ALL:
            LL_Print(list);
            return SUCCESS;
            
        case MENU_CLEAR:
            LL_Clear(list);
            printf("리스트가 초기화되었습니다.\n");
            return SUCCESS;
            
        default:
            printf("잘못된 메뉴 선택입니다.\n");
            return ERROR_INVALID_PARAMETER;
    }
}
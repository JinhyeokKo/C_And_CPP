#include "input_handler.h"

bool Input_GetInteger(const char* prompt, int* value) {
    printf("%s", prompt);
    
    if (fscanf(stdin,"%d", value) != 1) {
        Input_ClearBuffer();
        return false;
    }
    
    Input_ClearBuffer();
    return true;
}

void Input_ClearBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void Input_WaitForEnter(void) {
    printf("\n계속하려면 Enter를 누르세요...");
    Input_ClearBuffer();
}
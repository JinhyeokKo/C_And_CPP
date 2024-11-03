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

bool Input_GetString(const char* prompt, char** buffer) {
    size_t buffer_size = 0;

    printf("%s", prompt);

    ssize_t read = getline(buffer, &buffer_size, stdin);

    if (read == -1) {
        return false;
    }

    char* str = *buffer;

    if (str[read - 1] == '\n') {
        str[read - 1] = '\0';
    }

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
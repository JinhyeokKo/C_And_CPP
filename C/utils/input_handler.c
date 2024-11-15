#include "input_handler.h"

bool Input_GetInteger(const char* prompt, ElementType* value) {
    char* temp = malloc(sizeof(char*));
    if(!temp) return false;

    printf("%s", prompt);

    if(fgets(temp, sizeof(temp), stdin) == NULL) {
        free(temp);
        return false;
    }

    long swap = strtol(temp, NULL, 10);
    free(temp);
    value->integer = (int)swap;

    return true;
}

bool Input_GetString(const char* prompt, ElementType* value) {
    char* buffer = NULL;
    size_t buffer_size = 0;

    printf("%s", prompt);

    ssize_t read = getline(&buffer, &buffer_size, stdin);

    if (read == -1) {
        free(buffer);
        return false;
    }

    if (buffer[read - 1] == '\n') {
        buffer[read - 1] = '\0';
    }

    value->string = buffer;

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
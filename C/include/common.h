#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

// 에러 코드 정의
typedef enum {
    SUCCESS = 0,
    ERROR_INVALID_PARAMETER = -1,
    ERROR_MEMORY_ALLOCATION = -2,
    ERROR_NOT_FOUND = -3,
    ERROR_OUT_OF_RANGE = -4
} ErrorCode;

// 디버그 매크로
#ifdef DEBUG
#define DEBUG_LOG(fmt, ...) fprintf(stderr, "[DEBUG] %s:%d " fmt "\n", \
__FILE__, __LINE__, ##__VA_ARGS__)
#else
#define DEBUG_LOG(fmt, ...)
#endif

#endif // COMMON_H
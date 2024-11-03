cmake_minimum_required(VERSION 3.22)
project(C C)

# 디버그 모드 설정
set(CMAKE_BUILD_TYPE Debug)

# CLion에서 디버그 출력을 위한 설정
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(DEBUG)
    # 버퍼링 비활성화
    add_compile_definitions(_IONBF)
endif()

# 헤더 파일 디렉토리 설정
include_directories(
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/utils
        ${PROJECT_SOURCE_DIR}/linked_list/boot
        ${PROJECT_SOURCE_DIR}/linked_list/core
        ${PROJECT_SOURCE_DIR}/linked_list/utils
        ${PROJECT_SOURCE_DIR}/array_stack/boot
        ${PROJECT_SOURCE_DIR}/array_stack/core
        ${PROJECT_SOURCE_DIR}/array_stack/utils
        ${PROJECT_SOURCE_DIR}/linked_list_stack/boot
        ${PROJECT_SOURCE_DIR}/linked_list_stack/core
        ${PROJECT_SOURCE_DIR}/linked_list_stack/utils
)

# 소스 파일 목록 설정
set(BOOT_SOURCES
        utils/boot_handler.c
        linked_list/boot/linked_list_boot.c
        array_stack/boot/array_stack_boot.c
        linked_list_stack/boot/linked_list_stack_boot.c
)

set(CORE_SOURCES
        linked_list/core/linked_list.c
        array_stack/core/array_stack.c
        linked_list_stack/core/linked_list_stack.c
)

set(UTILS_SOURCES
        utils/input_handler.c
        linked_list/utils/linked_list_menu_handler.c
        array_stack/utils/array_stack_menu_handler.c
        linked_list_stack/utils/linked_list_stack_menu_handler.c

)

# 라이브러리 생성
add_library(boot STATIC ${BOOT_SOURCES})
add_library(core STATIC ${CORE_SOURCES})
add_library(utils STATIC ${UTILS_SOURCES})



set(CMAKE_C_STANDARD 99)

# 실행 파일 생성
add_executable(C main.c)
target_link_libraries(C
        PRIVATE
        boot
        core
        utils
)
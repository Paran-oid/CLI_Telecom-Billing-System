cmake_minimum_required(VERSION 3.31.0)

# project init
set(PROJECT_NAME TBS)
project(${PROJECT_NAME})

# debug section
set(CMAKE_BUILD_TYPE Debug)
add_compile_options(-Wall -Wextra -pedantic -Werror)

# C version
set(CMAKE_C_STANDARD 23)

# work directories
set(INCLUDE_DIR include)
set(MODEL_DIR models)
set(SRC_FILES 
    main.c
    src/program.c
    src/fileIO.c
    src/billing.c
    src/userService.c
    )


# project linking
include_directories(${INCLUDE_DIR} ${MODEL_DIR})
add_executable(${PROJECT_NAME} ${SRC_FILES})

add_custom_target(run ALL
    DEPENDS main
    COMMAND echo ""
    COMMAND ./TBS
    COMMAND echo ""
)
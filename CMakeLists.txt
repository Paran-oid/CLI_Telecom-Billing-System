cmake_minimum_required(VERSION 3.31.0) 
set(PROJECT_NAME TBS) 
set(CMAKE_BUILD_TYPE Debug) 
set(CMAKE_C_STANDARD 23) 

project(${PROJECT_NAME}) 

add_compile_options(-Wall -Wextra -pedantic -Werror) 

set(INCLUDE_DIR include)
set(MODEL_DIR models)
set(
    SRC_FILES 
    main.c 
    tests.c
    src/program.c 
    src/fileIO.c 
    src/billing.c 
    src/userService.c
) 

include_directories(${INCLUDE_DIR} ${MODEL_DIR}) 
add_executable(${PROJECT_NAME} ${SRC_FILES}) 
add_custom_target(
  run ALL 
  DEPENDS TBS 
  COMMAND echo
  COMMAND ./TBS 
  COMMAND echo
)
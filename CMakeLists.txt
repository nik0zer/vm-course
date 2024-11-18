project(VM)
cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(FRAME_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Frame)
set(EXECUTOR_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Executor)
set(EMITTER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Emitter)
set(MAIN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/main)

set(VM_SRC
${MAIN_DIR}/main.cpp
${EXECUTOR_DIR}/executor.cpp
${FRAME_DIR}/method.cpp
${EMITTER_DIR}/emitter.cpp
)

set(VM_LIB_DIRS
${FRAME_DIR}
${EMITTER_DIR}
${EXECUTOR_DIR}
)

add_executable(vm ${VM_SRC})
target_include_directories(vm PRIVATE ${VM_LIB_DIRS})
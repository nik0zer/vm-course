project(VM)
cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(INSTRUCTIONS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Instructions)
set(FRAME_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Frame)
set(EXECUTOR_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Executor)
set(EMITTER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Emitter)
set(MAIN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/main)

set(VM_SRC
${MAIN_DIR}/main.cpp
${INSTRUCTIONS_DIR}/instructions.cpp
${EXECUTOR_DIR}/executor.cpp
${FRAME_DIR}/method.cpp
${EMITTER_DIR}/emitter.cpp
)

set(VM_LIB_DIRS
${INSTRUCTIONS_DIR}
${FRAME_DIR}
${EMITTER_DIR}
${EXECUTOR_DIR}
)

add_executable(vm ${VM_SRC})
target_include_directories(vm PRIVATE ${VM_LIB_DIRS})
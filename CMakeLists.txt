cmake_minimum_required(VERSION 3.12)
project(ZSharpLLVM C CXX)

find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})

add_subdirectory(src)

add_executable(ZSharpLLVM src/main.cpp)
target_link_libraries(ZSharpLLVM LexerParser HelperVisitors)
set_property(TARGET ZSharpLLVM PROPERTY CXX_STANDARD 17)
set_property(TARGET ZSharpLLVM PROPERTY ENABLE_EXPORTS 1)

if(MSVC)
  target_compile_options(ZSharpLLVM PRIVATE /W4 /WX)
else()
  target_compile_options(ZSharpLLVM PRIVATE -Wall -Wextra -Wpedantic)
endif()
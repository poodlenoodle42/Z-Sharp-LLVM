add_library(SymbolTable STATIC 
            SymbolTable.cpp
            )

target_include_directories(SymbolTable PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(SymbolTable AST LLVM)

if(MSVC)
  target_compile_options(SymbolTable PRIVATE /W4 /WX)
else()
  target_compile_options(SymbolTable PRIVATE -Wall -Wextra -Wpedantic)
endif()
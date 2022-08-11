add_library(HelperVisitors STATIC 
            Printer.cpp
            )

target_include_directories(HelperVisitors PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(HelperVisitors AST)

if(MSVC)
  target_compile_options(HelperVisitors PRIVATE /W4 /WX)
else()
  target_compile_options(HelperVisitors PRIVATE -Wall -Wextra -Wpedantic)
endif()
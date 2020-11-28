set(HEADER_FILES
    include/compiler/lexer.h
    include/compiler/token.h
    )

set(SOURCE_FILES
    src/compiler.cpp
    src/lexer.cpp
    src/token.cpp
    )

base_add_executable(compiler ${SOURCE_FILES})
target_include_directories(compiler PRIVATE include)
target_link_libraries(compiler PRIVATE vm)

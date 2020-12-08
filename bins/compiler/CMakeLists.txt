set(HEADER_FILES
    include/compiler/assembler.h
    include/compiler/ast.h
    include/compiler/disassembler.h
    include/compiler/lexer.h
    include/compiler/parser.h
    include/compiler/range.h
    include/compiler/token.h
    include/compiler/token_iterator.h
    include/compiler/token_type.h
    )

set(SOURCE_FILES
    src/assembler.cpp
    src/ast.cpp
    src/compiler.cpp
    src/disassembler.cpp
    src/lexer.cpp
    src/parser.cpp
    src/token_type.cpp
    )

base_add_executable(compiler ${SOURCE_FILES})
target_include_directories(compiler PRIVATE include)
target_link_libraries(compiler PRIVATE vm)

set(HEADER_FILES
    include/compiler/compiler.h
    include/compiler/parser.h
    )

set(SOURCE_FILES
    src/compiler.cpp
    src/parser.cpp
    )

base_add_library(compiler ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(compiler PUBLIC base)

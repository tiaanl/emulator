set(HEADER_FILES
    )

set(SOURCE_FILES
        src/compiler.cpp
    )

base_add_library(compiler ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(compiler PUBLIC kernel)

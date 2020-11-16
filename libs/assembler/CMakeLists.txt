set(HEADER_FILES
    )

set(SOURCE_FILES
        src/compiler.cpp
    )

base_add_library(assembler ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(assembler PUBLIC kernel)

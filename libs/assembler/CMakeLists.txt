set(HEADER_FILES
    include/assembler/assembler.h
    )

set(SOURCE_FILES
    src/assembler.cpp
    )

base_add_library(assembler ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(assembler PUBLIC kernel)

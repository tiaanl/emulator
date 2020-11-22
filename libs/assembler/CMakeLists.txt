set(HEADER_FILES
    include/assembler/assembler.h
    include/assembler/disassembler.h
    )

set(SOURCE_FILES
    src/assembler.cpp
    src/disassembler.cpp
    )

base_add_library(assembler ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(assembler PUBLIC emulator)

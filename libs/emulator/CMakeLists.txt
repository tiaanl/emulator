set(HEADER_FILES
    include/emulator/cpu.h
    include/emulator/memory.h
    include/emulator/op_codes.h
    include/emulator/vm.h
    )

set(SOURCE_FILES
    src/cpu.cpp
    src/memory.cpp
    src/op_codes.cpp
    src/vm.cpp
    )

base_add_library(kernel ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(kernel PUBLIC base)

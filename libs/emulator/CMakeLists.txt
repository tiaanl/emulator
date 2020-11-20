set(HEADER_FILES
    include/emulator/cpu.h
    include/emulator/memory.h
    include/emulator/op_codes.h
    )

set(SOURCE_FILES
    src/cpu.cpp
    src/memory.cpp
    src/op_codes.cpp
    )

set(TEST_FILES
    tests/cpu_tests.cpp
    )

base_add_library(emulator ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(emulator PUBLIC base)

base_add_executable(emulator_tests ${TEST_FILES})
target_link_libraries(emulator_tests PRIVATE emulator assembler)

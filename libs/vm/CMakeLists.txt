set(HEADER_FILES
    include/vm/cpu.h
    include/vm/emulator.h
    include/vm/instruction.h
    include/vm/memory.h
    include/vm/op_codes.h
    include/vm/registers.h
    )

set(SOURCE_FILES
    src/cpu.cpp
    src/emulator.cpp
    src/instruction.cpp
    src/memory.cpp
    src/op_codes.cpp
    src/registers.cpp
    )

base_add_library(vm ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(vm PUBLIC base)

set (TEST_FILES
    tests/address_tests.cpp
    tests/cpu_tests.cpp
    tests/instruction_tests.cpp
    tests/vm_tests.cpp
    )

base_add_executable(vm_tests ${TEST_FILES})
target_link_libraries(vm_tests PRIVATE vm)
target_link_libraries(vm_tests PRIVATE Catch2::Catch2)

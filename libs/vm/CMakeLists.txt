set(HEADER_FILES
    include/vm/assembler/assembler.h
    include/vm/assembler/disassembler.h
    include/vm/compiler/compiler.h
    include/vm/compiler/parser.h
    include/vm/emulator/bus.h
    include/vm/emulator/cpu.h
    include/vm/emulator/memory.h
    include/vm/emulator/op_codes.h
    include/vm/emulator/registers.h
    include/vm/object_pool.h
    include/vm/platform.h
    )

set(SOURCE_FILES
    src/assembler/assembler.cpp
    src/assembler/disassembler.cpp
    src/compiler/compiler.cpp
    src/compiler/parser.cpp
    src/emulator/bus.cpp
    src/emulator/cpu.cpp
    src/emulator/memory.cpp
    src/emulator/op_codes.cpp
    src/emulator/registers.cpp
    )

base_add_library(vm ${HEADER_FILES} ${SOURCE_FILES})
target_precompile_headers(vm PUBLIC include/vm/platform.h)
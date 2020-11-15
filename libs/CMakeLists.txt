set(HEADER_FILES
    include/cpu.h
    include/op_codes.h
    include/platform.h
    )

set(SOURCE_FILES
    src/cpu.cpp
    src/op_codes.cpp
    )

add_library(lib ${HEADER_FILES} ${SOURCE_FILES})
target_include_directories(lib PUBLIC include)
set_target_properties(lib
    PROPERTIES
    CMAKE_CXX_STANDARD 17
    )

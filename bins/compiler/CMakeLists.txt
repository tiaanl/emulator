set(HEADER_FILES
    )

set(SOURCE_FILES
    src/main.cpp
    )

base_add_executable(compiler ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(compiler PRIVATE lib)
set_target_properties(compiler
    PROPERTIES
    CMAKE_CXX_STANDARD 17
    )

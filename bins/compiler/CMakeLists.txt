set(SOURCE_FILES
    src/assembler.cpp
    )

base_add_executable(compiler ${SOURCE_FILES})
target_link_libraries(compiler PRIVATE base)

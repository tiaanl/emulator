set(SOURCE_FILES
    src/test_compiler.cpp
    )

base_add_executable(test_compiler ${SOURCE_FILES})
target_link_libraries(test_compiler PRIVATE compiler)

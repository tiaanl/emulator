set(SOURCE_FILES
    src/ec.cpp
    )

base_add_executable(ec ${SOURCE_FILES})
target_link_libraries(ec PRIVATE vm)

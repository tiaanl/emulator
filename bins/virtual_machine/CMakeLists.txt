set(SOURCE_FILES
    src/virtual_machine.cpp
    )

base_add_executable(virtual_machine ${SOURCE_FILES})
target_link_libraries(virtual_machine PRIVATE X11)

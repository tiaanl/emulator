set(HEADER_FILES
    include/virtual_machine/graphics_mode.h
    )

set(SOURCE_FILES
    src/virtual_machine.cpp
    src/graphics_mode.cpp
    )

base_add_executable(virtual_machine ${HEADER_FILES} ${SOURCE_FILES})
target_include_directories(virtual_machine PRIVATE include)
target_link_libraries(virtual_machine PRIVATE vm)
target_link_libraries(virtual_machine PRIVATE glfw)
target_link_libraries(virtual_machine PRIVATE glad::glad)

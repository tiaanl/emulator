set(HEADER_FILES
    include/base/data.h
    include/base/object_pool.h
    include/base/platform.h
    )

set(SOURCE_FILES
    src/dummy.cpp
    )

base_add_library(base ${HEADER_FILES} ${SOURCE_FILES})
target_precompile_headers(base PUBLIC include/base/platform.h)

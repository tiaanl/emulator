set(HEADER_FILES
    include/base/object_pool.h
    include/base/platform.h
    include/base/range.h
    )

set(SOURCE_FILES
    src/base.cpp
    )

base_add_library(base ${HEADER_FILES} ${SOURCE_FILES})
target_precompile_headers(base PUBLIC include/base/platform.h)

set (SOURCES
    util.cc
    )

add_library(channet ${SOURCES})

add_subdirectory(tests)
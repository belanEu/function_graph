cmake_minimum_required(VERSION 3.5)

project(function_plot)

set(SOURCES
        main.cpp
        vertex.cpp
        screen.cpp
        coordinatesystemxy.cpp
)

set(HEADERS
        vertex.hpp
        screen.hpp
        coordinatesystemxy.hpp
)

set(LINKS -lncurses)

add_executable(test ${SOURCES} ${HEADERS})

target_link_libraries(test PRIVATE ${LINKS})

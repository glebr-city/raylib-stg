cmake_minimum_required(VERSION 3.5)
project(raylib_stg)
add_executable(raylib_stg src/main.cpp
        src/StepThinker.cpp
        include/StepThinker.h
        src/Player.cpp
        include/Player.h
        include/GlobalVariables.h
)


set(CMAKE_CXX_STANDARD 26)

add_library(raylib STATIC IMPORTED)
set_target_properties(raylib PROPERTIES
        IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/libraylib.a
        INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_SOURCE_DIR}/include
        INTERPROCEDURAL_OPTIMIZATION TRUE
)

target_include_directories(raylib_stg PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_directories(raylib_stg PRIVATE ${CMAKE_SOURCE_DIR}/lib)

target_link_libraries(raylib_stg PRIVATE libraylib.a)

add_custom_command(TARGET raylib_stg PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources/ $<TARGET_FILE_DIR:raylib_stg>/resources/)

target_compile_options(raylib_stg PUBLIC
        -ffunction-sections
        -fdata-sections
)

target_link_options(raylib_stg PUBLIC
        -Wl,--gc-sections
)

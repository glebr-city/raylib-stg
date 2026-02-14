cmake_minimum_required(VERSION 3.5)
project(raylib_stg)
add_executable(raylib_stg src/main.cpp
        src/StepThinker.cpp
        include/StepThinker.h
        src/Player.cpp
        include/Player.h
        include/GlobalVariables.h
        src/InputHandler.cpp
        include/InputHandler.h
        include/Bullet.h
        src/SimpleBullet.cpp
        include/SimpleBullet.h
        src/SpriteHandler.cpp
        include/SpriteHandler.h
        src/SimpleBullet1.cpp
        include/SimpleBullet1.h
        src/GameObject.cpp
        include/GameObject.h
        src/SimpleBullet2.cpp
        include/SimpleBullet2.h
        include/SimpleBullet2.h
        include/PoolingVector.h
        include/PhaseHelper.h
        src/TestPhase1.cpp
        include/TestPhase1.h
        include/DamageHandler.h
        src/GlobalVariables.cpp
        include/PlayerBullet.h
        include/GrazeConstants.h
        include/PlayerBullets.h
        src/PlayerBullets.cpp
        include/Enemy.h
        include/SpawnedEnemies.h
        src/SpawnedEnemies.cpp
        include/TestPhase2.h
        include/OrbEnemy1.h
        include/ScoreItem.h
        include/Spawnable.h
)

target_sources(raylib_stg
        PUBLIC
        src/main.cpp
)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

cmake_policy(SET CMP0076 NEW)



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

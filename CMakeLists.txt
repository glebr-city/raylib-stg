cmake_minimum_required(VERSION 3.5)
project(raylib_stg)
add_executable(raylib_stg src/main.cpp
        include/StepThinker.h
        src/Player.cpp
        include/Player.h
        include/GlobalVariables.h
        src/InputHandler.cpp
        include/InputHandler.h
        include/Bullet.h
        include/SimpleBullet.h
        src/SpriteHandler.cpp
        include/SpriteHandler.h
        include/SimpleBullet1.h
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
        include/ScoreItemHandler.h
        src/ScoreItemHandler.cpp
        include/ScoreHandler.h
        src/ScoreHandler.cpp
        include/HUDHandler.h
        src/HUDHandler.cpp
        include/LifeHandler.h
        src/LifeHandler.cpp
        src/DamageHandler.cpp
        include/GameHandler.h
        src/GameHandler.cpp
        include/DiagonalTankPhase1.h
        include/DiagonalTank.h
        include/Enemy1.h
        include/RNGHandler.h
        include/BigEnemy1.h
        include/SimpleBullet3.h
        include/SoundHandler.h
        src/SoundHandler.cpp
        include/GlobalPools.h
        src/GlobalPools.cpp
        include/BackgroundHandler.h
        src/BackgroundHandler.cpp
        include/Phase2.h
        include/PlayerHandler.h
        src/PlayerHandler.cpp
        include/StreetlightEnemy.h
        include/SimpleBullet1Fast.h
        include/Boss.h
        include/Boss1Phase1.h
        include/Boss1.h
        include/Boss1SmallBullet.h
        include/Boss1Phase2.h
        include/Boss1Phase3.h
        include/Boss1Phase4.h
        include/Boss1FastBurstBullet.h
        include/SimpleBullet1Slow.h
        include/EphemeraHandler.h
        include/Ephemera.h
        src/EphemeraHandler.cpp
        include/Boss1Phase5.h
        include/MenuHandler.h
        include/PauseHandler.h
        src/PauseHandler.cpp
        include/MenuOptions.h
        src/MenuHandler.cpp
        include/SoundData.h
        src/RNGHandler.cpp
        include/ConfigHandler.h
        include/Menus.h
        include/KeyNameDictionary.h
        include/MenuList.h
        include/Stage.h
        include/MainLoopHandler.h
        src/MainLoopHandler.cpp
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
target_include_directories(raylib_stg PRIVATE ${CMAKE_SOURCE_DIR}/include/raylib)
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

target_compile_definitions(raylib_stg PRIVATE DEBUG_BUILD=false)

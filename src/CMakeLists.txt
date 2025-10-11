cmake_minimum_required(VERSION 3.20)

include(FetchContent)

FetchContent_Declare(
    glm
    GIT_REPOSITORY  https://github.com/g-truc/glm.git
    GIT_TAG         1.0.1       
)
FetchContent_MakeAvailable(glm)

add_library(gamelib 
    game.cpp
    entity/player.cpp
    entity/target.cpp
    map/forest_tile.cpp
    map/snow_tile.cpp)

target_link_libraries(gamelib glm::glm)
target_include_directories(gamelib PUBLIC ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/entity)
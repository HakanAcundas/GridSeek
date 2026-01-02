cmake_minimum_required(VERSION 3.20)

include(FetchContent)

FetchContent_Declare(
    glm
    GIT_REPOSITORY  https://github.com/g-truc/glm.git
    GIT_TAG         1.0.1       
)
FetchContent_MakeAvailable(glm)

add_library(gridseeklib 
    "grid.cpp"
    "entity/target.cpp"
    "map/forest_tile.cpp"
    "map/snow_tile.cpp"
    "path_handler/path_handler.cpp"
    "application/application.cpp")

target_link_libraries(gridseeklib glm::glm)
target_include_directories(gridseeklib PUBLIC ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/entity)
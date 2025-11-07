cmake_minimum_required(VERSION 3.16)
project(sfml-backend LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  gui_interfaces
  GIT_REPOSITORY https://github.com/NeIIor/zemax-gui-interface
  GIT_TAG        my-architecture-improvements
)
FetchContent_MakeAvailable(gui_interfaces)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SFML REQUIRED sfml-graphics sfml-window)

add_library(sfml-backend SHARED
    src/backend.cpp
    src/window.cpp  
    src/texture.cpp
    src/image.cpp
    src/font.cpp      
    src/rectangle.cpp 
    src/text.cpp      
)

target_include_directories(sfml-backend PRIVATE 
    ${gui_interfaces_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

target_link_libraries(sfml-backend PRIVATE ${SFML_LIBRARIES})

set_target_properties(sfml-backend PROPERTIES
    PREFIX ""
    OUTPUT_NAME "dr4_sfml_backend"
)
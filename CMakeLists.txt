cmake_minimum_required(VERSION 3.20)
# set(CMAKE_TOOLCHAIN_FILE "D:\\PROGS\\vcpkg\\scripts\\buildsystems\\vcpkg.cmake" CACHE STRING "Path to the vcpkg toolchain file")

project(iam-engine VERSION 1.0)
project(iam-engine VERSION 1.0 LANGUAGES CXX)
message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
# fix windows no shared dll sdl3
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# if(NOT CMAKE_BUILD_TYPE)
#     set(CMAKE_BUILD_TYPE Release)
# endif()

set(OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
file(RELATIVE_PATH BIN_TO_BUILD_PATH ${CMAKE_BINARY_DIR}/bin ${CMAKE_BINARY_DIR})
add_compile_definitions(BIN_TO_BUILD_PATH="${BIN_TO_BUILD_PATH}")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${LIBRARY_DIRECTORY})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${OUTPUT_DIRECTORY})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${OUTPUT_DIRECTORY})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${OUTPUT_DIRECTORY})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${LIBRARY_DIRECTORY})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${LIBRARY_DIRECTORY})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set(CMAKE_CXX_FLAGS_RELEASE "-O3")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

# set(PROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)

set(ENGINE_DIR ${PROJECT_SOURCE_DIR}/Engine)
file(GLOB SOURCES
    ${ENGINE_DIR}/*.cpp
    ${ENGINE_DIR}/Graphics/*.cpp
    ${ENGINE_DIR}/ACS/*.cpp
    ${ENGINE_DIR}/Inputs/*.cpp
    ${ENGINE_DIR}/Physics/*.cpp
    ${ENGINE_DIR}/common/*.cpp
)

# set(Engine ${PROJECT_NAME})
set(Engine Engine)

# set(GAME_NAME "HelloWorld")
set(GAME_NAME "DescentLike")
set(GAME_DIR ${PROJECT_SOURCE_DIR}/${GAME_NAME})
file(GLOB GAME_SOURCES ${GAME_DIR}/*.cpp)
list(FILTER SOURCES EXCLUDE REGEX "^.*/__.*\.cpp$")
message(STATUS "SOURCES: ${SOURCES}")
message(STATUS "GAME_SOURCES: ${GAME_SOURCES}")

# set_target_properties(${PROJECT_NAME} PROPERTIES
# RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_DIRECTORY}"
# LIBRARY_OUTPUT_DIRECTORY "${OUTPUT_DIRECTORY}"
# ARCHIVE_OUTPUT_DIRECTORY "${LIBRARY_DIRECTORY}"
# )

add_executable(${PROJECT_NAME} ${GAME_DIR}/${GAME_NAME}.cpp ${GAME_SOURCES} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR})
# target_precompile_headers(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/Engine/pch.hpp)

# target_include_directories(${PROJECT_NAME} PUBLIC Engine)
add_library(${Engine} SHARED ${SOURCES})
target_precompile_headers(${Engine} PRIVATE ${CMAKE_SOURCE_DIR}/Engine/pch.hpp)
target_precompile_headers(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/Engine/pch.hpp)
target_include_directories(${Engine} PUBLIC Engine)
target_link_libraries(${PROJECT_NAME} ${Engine})

# // ACS try lib
# set(ACS_lib ACS)
# set(ACS_lib_DIRS ${PROJECT_SOURCE_DIR}/Engine/ACS)
# file(GLOB ACS_lib_SOURCES ${ACS_lib_DIRS}/*)
# message(STATUS "ACS_lib_DIRS: ${ACS_lib_DIRS}")
# message(STATUS "ACS_lib_SOURCES: ${ACS_lib_SOURCES}")
# add_library(${ACS_lib}Objects OBJECT ${ACS_lib_SOURCES})
# target_include_directories(${ACS_lib}Objects PUBLIC ${ACS_lib_DIRS})
# add_library(${ACS_lib}Static STATIC $<TARGET_OBJECTS:${ACS_lib}Objects>)
# add_library(${ACS_lib}Shared SHARED $<TARGET_OBJECTS:${ACS_lib}Objects>)
# target_link_libraries(${PROJECT_NAME} ${ACS_lib}Shared)

# include_directories(./ext/)

# include_directories(${PROJECT_SOURCE_DIR})

# target_compile_definitions(${PROJECT_NAME} PRIVATE IS_WIN=$<BOOL:${WIN32}> IS_MAC=$<BOOL:${APPLE}> IS_LINUX=$<BOOL:${LINUX}>)


# !!!!!! -- LIBS
include(FetchContent)

# SDL3
set(SDL3_VERSION 3.2.2)
find_package(SDL3 ${SDL3_VERSION} QUIET) # QUIET or REQUIRED
if (NOT SDL3_FOUND) # If there's none, fetch and build SDL3
    include(FetchContent)
    if (UNIX)
        FetchContent_Declare(
                SDL3
                URL https://github.com/libsdl-org/SDL/archive/refs/tags/release-${SDL3_VERSION}.tar.gz
        )
        FetchContent_MakeAvailable(SDL3)
    elseif (WIN32)
        FetchContent_Declare(
                SDL3
                URL https://github.com/libsdl-org/SDL/archive/refs/tags/release-${SDL3_VERSION}.zip
        )
        FetchContent_MakeAvailable(SDL3)
    endif()
endif()
target_link_libraries(${Engine} SDL3::SDL3)

# GLM
FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm.git
  GIT_TAG bf71a834948186f4097caa076cd2663c69a10e1e #refs/tags/1.0.1
)
FetchContent_MakeAvailable(glm)
target_link_libraries(${Engine} glm::glm)

target_include_directories(${Engine} PUBLIC "${CMAKE_SOURCE_DIR}/ext/glad/include")

add_library(GLAD "ext/glad/src/glad.c")
target_link_libraries(${Engine} GLAD)
target_include_directories(GLAD PRIVATE "${CMAKE_SOURCE_DIR}/ext/glad/include")

# !!!!!! JSON
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json
    GIT_TAG        v3.11.3
)
FetchContent_MakeAvailable(nlohmann_json)
target_link_libraries(${Engine} nlohmann_json::nlohmann_json)

# Fetch ImGui
FetchContent_Declare(
    ImGui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG v1.91.8-docking
)
FetchContent_MakeAvailable(ImGui)

add_library(imgui STATIC
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_demo.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl3.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

target_include_directories(${Engine} PUBLIC
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
)

# target_include_directories(imgui INTERFACE
#   $<BUILD_INTERFACE:${imgui_SOURCE_DIR}>
#   $<BUILD_INTERFACE:${imgui_SOURCE_DIR}/backends>
# )
target_include_directories(imgui PUBLIC
  ${imgui_SOURCE_DIR}
  ${imgui_SOURCE_DIR}/backends
)

target_link_libraries(imgui PUBLIC SDL3::SDL3 GLAD)

target_link_libraries(${Engine} imgui)

# !!!!!! following libs installed with VCPKG or BREW
# how to install it https://learn.microsoft.com/en-au/vcpkg/get_started/get-started?pivots=shell-cmd
# instead of adding environments manualy try to "vcpkg integrate install"
# run in this folder: "vcpkg install" to install deps

# !!!!!! Bullet
# brew install bullet
# set(BULLET_USE_SHARED_LIBS ON)
# FetchContent_Declare(
#     Bullet
#     GIT_REPOSITORY https://github.com/bulletphysics/bullet3.git
#     GIT_TAG master
# )
# FetchContent_MakeAvailable(Bullet)
find_package(Bullet REQUIRED)
include_directories(${BULLET_INCLUDE_DIRS})
target_link_libraries(${Engine} ${BULLET_LIBRARIES})

# !!!!!! ASSIMP
# brew install assimp@5.4.3
find_package(assimp REQUIRED)
message(
    STATUS "ASSIMP_INCLUDE_DIRS: ${ASSIMP_INCLUDE_DIRS}\n"
    "ASSIMP_LIBRARIES: ${assimp_LIBRARIES}\n"
    "ASSIMP_VERSION: ${assimp_VERSION}"
) # check assimp version
include_directories(${ASSIMP_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${ASSIMP_LIBRARIES})
target_link_libraries(${PROJECT_NAME} assimp::assimp)

target_link_libraries(${Engine} ${ASSIMP_LIBRARIES})
target_link_libraries(${Engine} assimp::assimp)

# !!!!!! RESOURCES

add_custom_target(copy_resources ALL
    # COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/resources ${CMAKE_BINARY_DIR}/resources
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${GAME_DIR}/resources ${CMAKE_BINARY_DIR}/resources
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${ENGINE_DIR}/resources ${CMAKE_BINARY_DIR}/resources
    # COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/config.json ${CMAKE_BINARY_DIR}/resources/config.json

    # Fix WIN32 SDL3 shared lib not found just run it twice (it will work after 1st try SDL3 build)

    DEPENDS ${RESOURCE_FILES}
    COMMENT "Copying resource files to build directory"
)

if(WIN32)
    add_custom_target(fix_win32_sdl3-shared ALL
        COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_BINARY_DIR}/_deps/sdl3-build/CMakeFiles/SDL3-shared.dir/src/core/windows/version.rc.res.res ${PROJECT_BINARY_DIR}/_deps/sdl3-build/CMakeFiles/SDL3-shared.dir/src/core/windows/version.rc.res
        COMMENT "fix_win32_sdl3-shared"
    )
endif()
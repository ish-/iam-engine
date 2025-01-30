cmake_minimum_required(VERSION 3.20)

project(iam-engine VERSION 1.0)
project(iam-engine VERSION 1.0 LANGUAGES CXX)
message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")

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

file(GLOB SOURCES
    ${PROJECT_SOURCE_DIR}/Engine/*.cpp
    ${PROJECT_SOURCE_DIR}/Engine/Graphics/*.cpp
    ${PROJECT_SOURCE_DIR}/Engine/ACS/*.cpp
    ${PROJECT_SOURCE_DIR}/Engine/Inputs/*.cpp
    ${PROJECT_SOURCE_DIR}/Engine/Physics/*.cpp
    ${PROJECT_SOURCE_DIR}/Engine/common/*.cpp
)

set(SAMPLE_NAME "HelloWorld")
set(SAMPLE_DIR ${PROJECT_SOURCE_DIR}/${SAMPLE_NAME})
file(GLOB SAMPLE_SOURCES ${SAMPLE_DIR}/*.cpp)
list(FILTER SOURCES EXCLUDE REGEX "^.*/__.*\.cpp$")
message(STATUS "SOURCES: ${SOURCES}")
message(STATUS "SAMPLE_SOURCES: ${SAMPLE_SOURCES}")

# set_target_properties(${PROJECT_NAME} PROPERTIES
# RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_DIRECTORY}"
# LIBRARY_OUTPUT_DIRECTORY "${OUTPUT_DIRECTORY}"
# ARCHIVE_OUTPUT_DIRECTORY "${LIBRARY_DIRECTORY}"
# )

add_executable(${PROJECT_NAME} ${SAMPLE_DIR}/${SAMPLE_NAME}.cpp ${SOURCES} ${SAMPLE_SOURCES})

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

# !!!!!! copy resources
# set(RESOURCE_FILES
#     ${PROJECT_SOURCE_DIR}/shaders
# )
set(CREATE_SYMLINKS OFF)
if(NOT WIN32 AND CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CREATE_SYMLINKS ON)
endif()

if (CREATE_SYMLINKS)
    add_custom_target(symlink_config ALL
        # COMMAND ${CMAKE_COMMAND} -E rm resources/config.json
        COMMAND ${CMAKE_COMMAND} -E create_symlink ${PROJECT_SOURCE_DIR}/resources ./resources
        COMMENT "Symlinking config.json"
    )
else()
    add_custom_target(copy_resources ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/resources ${CMAKE_BINARY_DIR}/resources
        # COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/config.json ${CMAKE_BINARY_DIR}/resources/config.json
        DEPENDS ${RESOURCE_FILES}
        COMMENT "Copying resource files to build directory"
    )
endif()


# !!!!!! -- LIBS
include(FetchContent)

# SDL3
set(SDL3_VERSION 3.1.6)
find_package(SDL3 ${SDL3_VERSION} QUIET) # QUIET or REQUIRED
if (NOT SDL3_FOUND) # If there's none, fetch and build SDL3
    include(FetchContent)
    if (UNIX)
        FetchContent_Declare(
                SDL3
                URL https://github.com/libsdl-org/SDL/archive/refs/tags/preview-${SDL3_VERSION}.tar.gz
        )
        FetchContent_MakeAvailable(SDL3)
    elseif (WIN32)
        FetchContent_Declare(
                SDL3
                URL https://github.com/libsdl-org/SDL/archive/refs/tags/preview-${SDL3_VERSION}.zip
        )
        FetchContent_MakeAvailable(SDL3)
    endif()
endif()
target_link_libraries(${PROJECT_NAME} SDL3::SDL3)

# GLM
FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm.git
  GIT_TAG bf71a834948186f4097caa076cd2663c69a10e1e #refs/tags/1.0.1
)
FetchContent_MakeAvailable(glm)
target_link_libraries(${PROJECT_NAME} glm::glm)

target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/ext/glad/include")

add_library(GLAD "ext/glad/src/glad.c")
target_link_libraries(${PROJECT_NAME} GLAD)
target_include_directories(GLAD PRIVATE "${CMAKE_SOURCE_DIR}/ext/glad/include")

# # !!!!!! JSON
# FetchContent_Declare(
#     nlohmann_json
#     GIT_REPOSITORY https://github.com/nlohmann/json
#     GIT_TAG        v3.11.3
# )
# FetchContent_MakeAvailable(nlohmann_json)
# target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)

# Fetch ImGui
FetchContent_Declare(
    ImGui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG v1.91.7
)
FetchContent_MakeAvailable(ImGui)

add_library(imgui STATIC
    ${imgui_SOURCE_DIR}/imgui.cpp
    # ${imgui_SOURCE_DIR}/imgui_demo.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl3.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
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

target_link_libraries(${PROJECT_NAME} imgui)

# !!!!!! Bullet

# add_subdirectory(${CMAKE_SOURCE_DIR}/ext/bullet3/build_cmake/src)
# add_subdirectory(${CMAKE_SOURCE_DIR}/ext/bullet3/build_cmake/src/Bullet3Common)
# set(BULLET_ROOT ${CMAKE_SOURCE_DIR}/ext/bullet3)
# set(BULLET_INCLUDE_DIR ${BULLET_ROOT}/src)
# set(BULLET_LIBRARIES ${BULLET_ROOT}/lib)

# brew install bullet
find_package(Bullet REQUIRED)
include_directories(${BULLET_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${BULLET_LIBRARIES})

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
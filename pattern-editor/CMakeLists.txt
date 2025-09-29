##########################################################################################
# Project Setup
##########################################################################################

cmake_minimum_required(VERSION 4.0)
project(BulletJSONPatternEditor)
add_compile_definitions(GAME_NAME="${PROJECT_NAME}")

# Set default platform
if (NOT DEFINED PLATFORM)
    set(PLATFORM "Desktop")
endif()

# Setup c++ std version
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)

# Generate compile_commands.json, helps vscode to resolve imports
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add OS macros
if(MINGW)
    add_compile_definitions(IS_OS_BUILD_WINDOWS="TRUE")
    set(OS_BUILD_TYPE "Windows")
elseif(EMSCRIPTEN)
    add_compile_definitions(IS_OS_BUILD_WEB="TRUE")
    set(OS_BUILD_TYPE "Web")
else()
    add_compile_definitions(IS_OS_BUILD_LINUX="TRUE")
    set(OS_BUILD_TYPE "Linux")
endif()

##########################################################################################
# Pre build
##########################################################################################

add_custom_target(
    PreBuildTasks
    COMMAND ${CMAKE_SOURCE_DIR}/pre-build.sh ${PROJECT_NAME} ${OS_BUILD_TYPE}
    COMMENT "Running pre-build script..."
)

##########################################################################################
# Files
##########################################################################################

# Include directories on /src/*
set(SRC_DIRECTORY ${CMAKE_SOURCE_DIR}/src)
include_directories(${SRC_DIRECTORY})

# Include directories on /lib
set(LIB_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
include_directories(${LIB_DIRECTORY}/raylib/src)
include_directories(${LIB_DIRECTORY}/json)
include_directories(${LIB_DIRECTORY}/imgui)
include_directories(${LIB_DIRECTORY}/rlimgui)
include_directories(${LIB_DIRECTORY}/ImGuiColorTextEdit)

# Add all source files
file(
    GLOB_RECURSE
    SOURCE_FILES
    CONFIGURE_DEPENDS
    "src/*.hpp" "src/*.cpp"
)

# Disable terminal and open in graphical mode on Windows
if(MINGW)
    set(CMAKE_WIN32_EXECUTABLE ON)
endif()

# Add executable target
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
add_dependencies(${PROJECT_NAME} PreBuildTasks)

##########################################################################################
# Libraries
##########################################################################################

# Raylib
add_subdirectory(lib/raylib)

# Json
# file(GLOB JSON_FILES "lib/json/*.hpp")
# add_library(json STATIC ${JSON_FILES})
# set_target_properties(json PROPERTIES LINKER_LANGUAGE CXX)

# Imgui
file(GLOB IMGUI_FILES "lib/imgui/*.h" "lib/imgui/*.cpp")
add_library(imgui STATIC ${IMGUI_FILES})

# rlImGui
file(GLOB RLIMGUI_FILES "lib/rlimgui/*.h" "lib/rlimgui/*.cpp")
add_library(rlImGui STATIC ${RLIMGUI_FILES})

# ImGuiColorTextEdit
file(GLOB ImGuiColorTextEdit_FILES "lib/ImGuiColorTextEdit/*.h" "lib/ImGuiColorTextEdit/*.cpp")
add_library(ImGuiColorTextEdit STATIC ${ImGuiColorTextEdit_FILES})

# Link libraries
target_link_libraries(${PROJECT_NAME} raylib)
# target_link_libraries(${PROJECT_NAME} json)
target_link_libraries(${PROJECT_NAME} imgui)
target_link_libraries(${PROJECT_NAME} rlImGui)
target_link_libraries(${PROJECT_NAME} ImGuiColorTextEdit)

##########################################################################################
# Web Build Config
##########################################################################################

## Fix WEB build problem related to GLFW3 (https://github.com/raysan5/raylib/wiki/Working-for-Web-(HTML5)#23-using-cmake)
if (EMSCRIPTEN)
    message(STATUS "Building with EmScripten")

    include_directories("~/emsdk/upstream/emscripten/cache/sysroot/include/")

    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY -s EXPORTED_RUNTIME_METHODS=ccall --preload-file ${CMAKE_SOURCE_DIR}/final-builds/Web/assets@assets --shell-file ${CMAKE_SOURCE_DIR}/lib/raylib/src/minshell.html")
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif ()


##########################################################################################
# Windows Build Config
##########################################################################################

if(MINGW)
    message(STATUS "Building with mingw-w64")

    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -static")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")
endif()


##########################################################################################
# Post build
##########################################################################################

add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_SOURCE_DIR}/post-build.sh ${PROJECT_NAME} ${OS_BUILD_TYPE} ${CMAKE_BUILD_TYPE}
    COMMENT "Running post build script..."
)
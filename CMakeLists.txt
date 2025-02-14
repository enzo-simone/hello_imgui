
cmake_minimum_required(VERSION 3.14)
project(HelloImGui)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(COMPILE_IMGUI_DEMO "compiles and shows imgui demo window" OFF)
option(USE_GLAD "use GLAD" OFF)

# Check OS
message("Os: ${CMAKE_SYSTEM_NAME}")

# check for linux mint
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(LINUX_INFO "")
    if(EXISTS "/etc/os-release")
        file(STRINGS "/etc/os-release" LINUX_DISTRO REGEX "^ID=")
        string(APPEND LINUX_INFO "${LINUX_DISTRO}")
        if(LINUX_DISTRO STREQUAL "ID=linuxmint")
            string(APPEND LINUX_INFO ", Linux Mint detected!")
            set(IS_LINUX_MINT TRUE)
        else()
            string(APPEND LINUX_INFO ", Not Linux Mint.")
        endif()
    else()
        message(FATAL_ERROR "missing /etc/os-release")
    endif()
    message("  Linux info: ${LINUX_INFO}")

    # alternative
    execute_process(
        COMMAND lsb_release -a
        OUTPUT_VARIABLE LINUX_DISTRO
        OUTPUT_STRIP_TRAILING_WHITESPACE
        ERROR_QUIET
    )
    message("Detected Linux Distribution (alternative approach):")
    message("${LINUX_DISTRO}\n")
endif()

# Set options according to OS
if(IS_LINUX_MINT)
    set(USE_GLAD ON CACHE BOOL "Force GLAD usage" FORCE)
    set(GLFW_BUILD_WAYLAND OFF CACHE BOOL "Force unset WAYLAND" FORCE)
endif()

# already installed dependencies
find_package(OpenGL REQUIRED)

# dependencies to be fetched
include(FetchContent)
FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG master
)
FetchContent_MakeAvailable(imgui)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG master
)
FetchContent_MakeAvailable(glfw)

# Add executable
set(TARGET hello_imgui)

add_executable(${TARGET} main.cpp)

target_include_directories(${TARGET} PRIVATE ${imgui_SOURCE_DIR})

target_sources(${TARGET} PRIVATE
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp

    ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

target_link_libraries(${TARGET} PRIVATE glad glfw OpenGL::GL)

if(COMPILE_IMGUI_DEMO)
    message("Demo window is compiled")
    target_compile_definitions(${TARGET} PRIVATE COMPILE_IMGUI_DEMO=1)
    target_sources(${TARGET} PRIVATE
        ${imgui_SOURCE_DIR}/imgui_demo.cpp)
else()
    message("Demo window is not compiled")
endif()

if(USE_GLAD)
    message("Using GLAD")
    FetchContent_Declare(
        glad
        GIT_REPOSITORY https://github.com/Dav1dde/glad.git
        GIT_TAG master  # You can specify a particular version or tag if needed
    )
    FetchContent_MakeAvailable(glad)
    target_compile_definitions(${TARGET} PRIVATE USE_GLAD=1)
endif()

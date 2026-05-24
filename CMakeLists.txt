cmake_minimum_required(VERSION 4.0.2)
project(password_manager)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

FetchContent_Declare(
        imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui.git
        GIT_TAG v1.91.9b
)
FetchContent_MakeAvailable(imgui)

FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.4
)
FetchContent_MakeAvailable(glfw)

# imgui source
set(IMGUI_SOURCES
        ${imgui_SOURCE_DIR}/imgui.cpp
        ${imgui_SOURCE_DIR}/imgui_draw.cpp
        ${imgui_SOURCE_DIR}/imgui_tables.cpp
        ${imgui_SOURCE_DIR}/imgui_widgets.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

include_directories(
        .
        ${imgui_SOURCE_DIR}
        ${imgui_SOURCE_DIR}/backends
)

add_executable(password_manager
        main.cpp
        PasswordEntry.h
        Vault.cpp
        Vault.h
        picosha2.h
        ${IMGUI_SOURCES}
        Gui.h
        Gui.cpp
)

find_package(OpenGL REQUIRED)

target_link_libraries(
        password_manager
        glfw
        OpenGL::GL
)

if(MINGW)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -static-libgcc -static-libstdc++")
    target_link_libraries(password_manager imm32 dwmapi)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set_target_properties(password_manager PROPERTIES WIN32_EXECUTABLE TRUE)
endif()

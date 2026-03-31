cmake_minimum_required(VERSION 4.0.2)
project(password_manager)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(password_manager
        main.cpp
        PasswordEntry.h
        Vault.cpp
        Vault.h
        picosha2.h)

if(MINGW)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -static-libgcc -static-libstdc++")
endif()

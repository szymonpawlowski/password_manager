cmake_minimum_required(VERSION 4.0.2)
project(password_manager)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(password_manager
        main.cpp
        PasswordEntry.cpp
        PasswordEntry.h
        Vault.cpp
        Vault.h)

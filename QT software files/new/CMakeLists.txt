cmake_minimum_required(VERSION 3.16)
project(BankSystem VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(BankSystem
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    # Add your logic file here if you keep it separate,
    # or just paste the logic into mainwindow.cpp
)

target_link_libraries(BankSystem PRIVATE Qt6::Widgets)

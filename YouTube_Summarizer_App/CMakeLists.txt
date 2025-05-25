cmake_minimum_required(VERSION 3.5)

project(YoutubeSummarizer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)  # ✅ Required for Q_OBJECT macro
set(CMAKE_AUTOUIC ON)  # ✅ Required for .ui files
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(YoutubeSummarizer
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
)

target_link_libraries(YoutubeSummarizer Qt5::Widgets)


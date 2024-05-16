cmake_minimum_required(VERSION 3.28)
project(untitled6)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(untitled6 main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        tree_space.cpp
        tree_space.h
        tree_space.ui
        kurevo.cpp
        kurevo.h
        avl.cpp
        avl.h
        Item.cpp
        Item.h
        splay.cpp
        splay.h
        rb.cpp
        rb.h
)
target_link_libraries(untitled6
        Qt::Core
        Qt::Gui
        Qt::Widgets
)


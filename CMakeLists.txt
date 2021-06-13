cmake_minimum_required(VERSION 3.13)
project(mp3_gui)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)
include_directories(tests)

link_libraries(stdc++fs)

add_executable(mp3_gui
        src/FileExplorer.cpp
        src/FileExplorer.hpp
        src/menus.cpp
        src/build_files_db.hpp src/build_files_db.cpp src/external_sort.cpp src/external_sort.hpp src/parse_filenames.cpp src/parse_filenames.hpp src/FileExplorerUI.cpp src/FileExplorerUI.hpp src/AbstractUI.hpp src/AbstractScreen.hpp src/reverse.hpp src/Player.cpp src/Player.hpp)

add_executable(mp3_gui_test
        src/FileExplorer.cpp
        src/FileExplorer.hpp
        tests/catch.hpp
        tests/hippomocks.h
        tests/mainTest.cpp
        tests/TestFileExplorer.cpp
        tests/TestFileExplorerUI.cpp
        src/build_files_db.hpp src/parse_filenames.cpp src/parse_filenames.hpp
        src/FileExplorerUI.cpp src/FileExplorerUI.hpp src/AbstractUI.hpp src/AbstractScreen.hpp src/reverse.hpp tests/FSMocks.cpp tests/FSMocks.hpp tests/TestScreen.hpp src/Player.cpp src/Player.hpp)



cmake_minimum_required(VERSION 3.23)
project(RGB_Button_Qt)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_OSX_ARCHITECTURES x86_64)

set(CMAKE_PREFIX_PATH "/Users/gasoline/Qt5.12.12/5.12.12/clang_64/lib/cmake")

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(RGB_Button_Qt main.cpp)
target_link_libraries(RGB_Button_Qt
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        )


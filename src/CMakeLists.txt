cmake_minimum_required(VERSION 2.8.3)


project(icp18)

set(CMAKE_CXX_STANDARD 14)

# list(APPEND CMAKE_PREFIX_PATH /opt/qt/5.10.1/gcc_64/lib/cmake/Qt5Widgets/ /opt/qt/5.10.1/gcc_64/lib/cmake/Qt5Quick/ /opt/qt/5.10.1/gcc_64/lib/cmake/Qt5X11Extras/)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Widgets)

# Add the include directories for the Qt 5 Widgets module to
# the compile lines.
include_directories(${Qt5Widgets_INCLUDE_DIRS})

# Use the compile definitions defined in the Qt 5 Widgets module
add_definitions(${Qt5Widgets_DEFINITIONS})

# Add compiler flags for building executables (-fPIE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")

# Tell CMake to create the helloworld executable
add_executable(
        helloworld
        app/mainwindow.cpp
        app/main.cpp
        app/core/block.cpp
        app/core/block.h
        app/core/blockmanager.cpp app/core/blockmanager.h app/core/base.h app/core/identified.cpp app/core/identified.h app/core/join.cpp app/core/join.h app/core/typeblock.cpp app/core/typeblock.h app/core/typedata.cpp app/core/typedata.h app/core/evaluator.cpp app/core/evaluator.h app/core/data.cpp app/core/data.h)

#Link the helloworld executable to the Qt 5 widgets library.
target_link_libraries(helloworld Qt5::Widgets)
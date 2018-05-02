cmake_minimum_required(VERSION 2.8.3)


project(icp18)

set(CMAKE_CXX_STANDARD 14)

list(
        APPEND CMAKE_PREFIX_PATH
        /opt/qt/5.10.1/gcc_64/lib/cmake/Qt5Widgets/
        /opt/qt/5.10.1/gcc_64/lib/cmake/Qt5Core/
        /opt/qt/5.10.1/gcc_64/lib/cmake/Qt5Gui/
        /opt/qt/5.10.1/gcc_64/lib/cmake/Qt5Svg/
        /opt/qt/5.10.1/gcc_64/lib/cmake/Qt5Quick/
        /opt/qt/5.10.1/gcc_64/lib/cmake/Qt5X11Extras/
)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Widgets)
find_package(Qt5Svg)

# Add the include directories for the Qt 5 Widgets module to
# the compile lines.
include_directories(${Qt5Widgets_INCLUDE_DIRS})

# Use the compile definitions defined in the Qt 5 Widgets module
add_definitions(${Qt5Widgets_DEFINITIONS})

# Add compiler flags for building executables (-fPIE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")

file(
        GLOB_RECURSE SRC
        LIST_DIRECTORIES false
        RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
        "app/*.h" "app/*.cpp" "app/*.qrc"
)
# Tell CMake to create the helloworld executable
add_executable(
        blockeditor
        ${SRC}
        app/ui/resources.qrc
)

#Link the helloworld executable to the Qt 5 widgets library.
target_link_libraries(blockeditor Qt5::Widgets)
target_link_libraries(blockeditor Qt5::Svg)
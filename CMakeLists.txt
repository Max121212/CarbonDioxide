cmake_minimum_required(VERSION 3.16)

# Project name and version
project(CarbonDioxide VERSION 1.0 LANGUAGES CXX)

# Set C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)

# Find Qt6 libraries
find_package(Qt6 REQUIRED COMPONENTS Widgets Quick QuickControls2)

# Add resource file
qt_add_resources(RESOURCES resources.qrc)

# Add executable
add_executable(${PROJECT_NAME} main.cpp CarbonDioxideSensor.cpp AverageCalculator.cpp ${RESOURCES})

# Link Qt6 libraries to the executable
target_link_libraries(${PROJECT_NAME} Qt6::Widgets Qt6::Quick Qt6::QuickControls2)
cmake_minimum_required(VERSION 3.5)

# Project name
project(keboard VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find the Qt5 package
find_package(Qt5 COMPONENTS Widgets REQUIRED)

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_BINARY_DIR})

# Source files
set(SOURCES
    src/main.cpp
    src/keyboard.cpp
)

# Header files
set(HEADERS
    include/keyboard.h
)

# UI files
set(UI_FILES
    ui/keyboard.ui
)

# Generate MOC files
qt5_wrap_cpp(MOC_SOURCES ${HEADERS})

# Generate UIC files
qt5_wrap_ui(UIC_SOURCES ${UI_FILES})

# Add the executable
add_executable(${PROJECT_NAME} ${SOURCES} ${MOC_SOURCES} ${UIC_SOURCES})

# Link the Qt5 Widgets library
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)


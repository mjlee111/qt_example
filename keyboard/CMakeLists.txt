cmake_minimum_required(VERSION 3.5)

# Project name
project(keyboard VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Try to find Qt6 first, if not found, try Qt5
find_package(Qt6 COMPONENTS Widgets QUIET)
if(Qt6_FOUND)
    set(QT_VERSION_MAJOR 6)
    message(STATUS "Found Qt6: ${Qt6_VERSION}")
else()
    find_package(Qt5 COMPONENTS Widgets REQUIRED)
    set(QT_VERSION_MAJOR 5)
    message(STATUS "Found Qt5: ${Qt5_VERSION}")
endif()

if(NOT Qt5_FOUND AND NOT Qt6_FOUND)
    message(FATAL_ERROR "Qt5 or Qt6 not found. Please install Qt.")
endif()

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

# Resource file
set(RESOURCE_FILES
    resources/resources.qrc
)

# Generate MOC files
if(QT_VERSION_MAJOR EQUAL 6)
    qt6_wrap_cpp(MOC_SOURCES ${HEADERS})
else()
    qt_wrap_cpp(MOC_SOURCES ${HEADERS})
endif()

# Generate UIC files
if(QT_VERSION_MAJOR EQUAL 6)
    qt6_wrap_ui(UIC_SOURCES ${UI_FILES})
else()
    qt_wrap_ui(UIC_SOURCES ${UI_FILES})
endif()

# Generate resources
if(QT_VERSION_MAJOR EQUAL 6)
    qt_add_resources(RESOURCE_SOURCES ${RESOURCE_FILES})
else()
    qt_add_resources(RESOURCE_SOURCES ${RESOURCE_FILES})
endif()

# Add the executable
add_executable(${PROJECT_NAME} ${SOURCES} ${MOC_SOURCES} ${UIC_SOURCES} ${RESOURCE_SOURCES})

# Link the appropriate Qt Widgets library
if(QT_VERSION_MAJOR EQUAL 6)
    target_link_libraries(${PROJECT_NAME} Qt6::Widgets)
else()
    target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
endif()

# Platform-specific settings
if(WIN32)
    # Windows-specific settings (if any)

elseif(UNIX)
    # Linux-specific settings
    find_package(X11 REQUIRED)

    # Find XTest using pkg-config
    find_package(PkgConfig REQUIRED)
    pkg_search_module(XTEST REQUIRED xtst)

    # Include directories and link libraries
    include_directories(${XTEST_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${X11_LIBRARIES} ${XTEST_LIBRARIES})

    # Add CMake modules path if needed
    list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
endif()

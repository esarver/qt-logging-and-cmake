cmake_minimum_required(VERSION 3.5 FATAL_ERROR) 

# Enable testing to be part of the normal cmake build
enable_testing()

project(project-name)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-fPIC")

set_property(GLOBAL PROPERTY TARGET_SUPPORTS_SHARED_LIBS TRUE)

# Maintain debug information (clearer logging)
set(CMAKE_BUILD_TYPE Debug) #TODO - Find a better way to do this. There might be a way to define this within Qt...

# Put the CMake files for Qt5 in the prefix path. 
# This needs to be where the Qt cmake files are installed on the build computer
set(CMAKE_PREFIX_PATH /opt/Qt/5.9/gcc_64/lib/cmake/)

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the required Qt5 packages
find_package(Qt5Core REQUIRED)
find_package(Qt5Sql REQUIRED)
find_package(Qt5Test REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/src ${Qt5Core_INCLUDE_DIRS})

add_subdirectory(src)
add_subdirectory(test)

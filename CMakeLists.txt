cmake_minimum_required(VERSION 3.10)

project(Minisocial)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include header files
include_directories(include)

# Add source files
add_executable(Minisocial
    src/Admin.cpp
    src/MediaMain.cpp
    src/Post.cpp
    src/User.cpp
    src/UserManager.cpp
)

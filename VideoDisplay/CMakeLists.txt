cmake_minimum_required(VERSION 3.5)

project(VideoDisplay LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add your source file
set(SOURCES
    VideoProcessing.cpp
)

# OpenCV settings
set(OpenCV_DIR C:/LIBRARY/OpenCV)
find_package(OpenCV REQUIRED PATHS ${OpenCV_DIR} NO_DEFAULT_PATH)

include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIB_DIR})


# Create executable
add_executable(VideoDisplay ${SOURCES})


# Link OpenCV libraries
target_link_libraries(VideoDisplay PRIVATE ${OpenCV_LIBS})


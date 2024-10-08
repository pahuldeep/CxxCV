cmake_minimum_required(VERSION 3.5)
project(superResolution LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define OpenCV directory path
set(OpenCV_DIR "C:/LIBRARY/OpenCV")
find_package(OpenCV REQUIRED PATHS ${OpenCV_DIR})

# Define paths for model and resource directories
set(RESOURCE_DIR "${CMAKE_SOURCE_DIR}/res")

# Include directories for OpenCV
include_directories(${OpenCV_INCLUDE_DIRS})

# Define executable and source files
add_executable(${PROJECT_NAME} main.cpp)

# Link OpenCV libraries
target_link_libraries(${PROJECT_NAME} PRIVATE ${OpenCV_LIBS})


# Copy models and resources to output directory after building
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:${PROJECT_NAME}>/res
)

cmake_minimum_required(VERSION 3.5)

project(BrightFPS LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add your source file
set(SOURCES
    bright_fps.cpp
)

# OpenCV settings
set(OpenCV_DIR C:/LIBRARY/OpenCV)
find_package(OpenCV REQUIRED PATHS ${OpenCV_DIR} NO_DEFAULT_PATH)

include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIB_DIR})


# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})


# Link OpenCV libraries
target_link_libraries(${PROJECT_NAME} PRIVATE ${OpenCV_LIBS})

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

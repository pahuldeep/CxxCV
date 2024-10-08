cmake_minimum_required(VERSION 3.5)

project(Contours LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES Contours.cpp)


#Opencv settings
set(opencv_dir C:/LIBRARY/OpenCV)
find_package(OpenCV REQUIRED PATHS ${opencv_dir} NO_DEFAULT_PATH)
include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIB_DIR})

add_executable(${PROJECT_NAME} ${SOURCES})


# Link OpenCV libraries
target_link_libraries(${PROJECT_NAME} PRIVATE ${OpenCV_LIBS})

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

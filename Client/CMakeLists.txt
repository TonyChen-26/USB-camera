cmake_minimum_required(VERSION 2.8.12)
project(Client)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/src
)

file(GLOB all_SRCS
        "${PROJECT_SOURCE_DIR}/include/*.h"
        "${PROJECT_SOURCE_DIR}/src/*.cpp"
)

add_executable(Client ${all_SRCS})


find_package ( OpenCV 3.4.6 EXACT REQUIRED )
if ( OpenCV_FOUND )
include_directories ( $ { OpenCV_INCLUDE_DIRS })
target_link_libraries ( ${PROJECT_NAME} ${OpenCV_LIBS})
else ( OpenCV_FOUND )
message ( FATAL ERROR " Open CV Library not found !")
endif ( OpenCV_FOUND )

find_package(PkgConfig REQUIRED)
pkg_check_modules(ZBAR REQUIRED zbar)

# Check if ZBar is found and set include directories and libraries
if(ZBAR_FOUND)
    include_directories(${ZBAR_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${ZBAR_LIBRARIES})
else()
    message(FATAL_ERROR "ZBar Library not found!")
endif()

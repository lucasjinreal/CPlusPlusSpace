cmake_minimum_required(VERSION 2.8)  
project(DisplayAnno)
add_compile_options(-std=c++11)

find_package(OpenCV REQUIRED)
find_package( Boost REQUIRED COMPONENTS)
include_directories( ${Boost_INCLUDE_DIRS} )


add_executable(DisplayAnno main.cpp solvecsv.cpp)
target_link_libraries(DisplayAnno
        ${OpenCV_LIBS}
        ${Boost_LIBRARIES}
        ${Boost_FILESYSTEM_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
        )

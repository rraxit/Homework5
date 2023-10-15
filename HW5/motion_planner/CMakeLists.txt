cmake_minimum_required(VERSION 3.10)
project(motion_planner)

set(CMAKE_CXX_STANDARD 17)


set(ompl_INCLUDE_DIRS /usr/include/ompl)
set(OMPL_LIBRARY /usr/lib/x86_64-linux-gnu/libompl.so)
find_package (Eigen3 3.3 REQUIRED NO_MODULE)

set(PNG_SOURCE_FILES
        src/lodepng.cpp 
        src/lodepng.h 
        )
include_directories(
        ${ompl_INCLUDE_DIRS}
        /usr/local/include
        include
        ${Eigen3_INCLUDE_DIRS}
)

add_executable(${PROJECT_NAME} src/main.cpp  ${PNG_SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} 
    Eigen3::Eigen
    ${OMPL_LIBRARY})


add_executable(${PROJECT_NAME}_img_parser  src/image_parser.cpp ${PNG_SOURCE_FILES})

target_link_libraries(${PROJECT_NAME}_img_parser 
    Eigen3::Eigen
    ${OMPL_LIBRARY})
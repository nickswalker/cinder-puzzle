cmake_minimum_required( VERSION 2.8 FATAL_ERROR )
set( CMAKE_VERBOSE_MAKEFILE ON )

set(CMAKE_CXX_STANDARD 14)

project(puzzle)
get_filename_component(CINDER_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Cinder" ABSOLUTE)
get_filename_component(CLINGO_PATH "${CMAKE_CURRENT_SOURCE_DIR}/clingo" ABSOLUTE)
get_filename_component(APP_PATH "${CMAKE_CURRENT_SOURCE_DIR}/" ABSOLUTE)

include( "${CINDER_PATH}/proj/cmake/configure.cmake" )

set(CLINGO_INCLUDES "${CLINGO_PATH}/clasp" "${CLINGO_PATH}/libclingo")
set(CLINGO_LIBS libclingo.so m stdc++)
set(CLINGO_LINK_PATH "${CLINGO_PATH}/build/bin")

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")

find_package( cinder REQUIRED PATHS
        PATHS "${CINDER_PATH}/${CINDER_LIB_DIRECTORY}"
        )

link_directories(
        ${CLINGO_LINK_PATH}
)

include_directories(
        ${CLINGO_INCLUDES}
        include
)

add_library(puzzle src/PixelsDomain.cpp src/ASPSolver.cpp src/PixelsRenderer.cpp src/Puzzle.cpp src/Constant.cpp src/ShapesRenderer.cpp src/ShapesDomain.cpp src/TSPDomain.cpp src/TSPRenderer.cpp src/TSPRenderer.cpp src/TilingDomain.cpp src/TilingRenderer.cpp)
add_library(puzzle_demos src/Colors.cpp)

add_executable(pixels_demo src/demos/pixels_demo.cpp src/demos/PuzzleDemoApp.cpp)
add_executable(shapes_demo src/demos/shapes_demo.cpp src/demos/PuzzleDemoApp.cpp)
add_executable(tsp_demo src/demos/tsp_demo.cpp src/demos/PuzzleDemoApp.cpp)
add_executable(tiling_demo src/demos/tiling_demo.cpp src/demos/PuzzleDemoApp.cpp)

target_link_libraries(puzzle
        PUBLIC
        cinder
        cairo
        ${CLINGO_LIBS}
        )

target_link_libraries(puzzle_demos
        PUBLIC
        cinder
        cairo
        puzzle
        ${CLINGO_LIBS}
        )

target_link_libraries(pixels_demo
        PUBLIC
        puzzle
        puzzle_demos
        cinder
        )

target_link_libraries(shapes_demo
        PUBLIC
        puzzle
        puzzle_demos
        cinder
        )

target_link_libraries(tsp_demo
        PUBLIC
        puzzle
        puzzle_demos
        cinder
        )

target_link_libraries(tiling_demo
        PUBLIC
        puzzle
        puzzle_demos
        cinder
        )


# Make the domains available next to the binary
# TODO: Make this actually update whenever domains are changed between builds
file(COPY domains DESTINATION ./)
file(COPY resources DESTINATION ./assets)
cmake_minimum_required( VERSION 2.8 FATAL_ERROR )
set( CMAKE_VERBOSE_MAKEFILE ON )

project(puzzle)
get_filename_component( CINDER_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../Cinder" ABSOLUTE )
get_filename_component( APP_PATH "${CMAKE_CURRENT_SOURCE_DIR}/" ABSOLUTE )

include( "${CINDER_PATH}/proj/cmake/configure.cmake" )

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")

find_package( cinder REQUIRED PATHS
        PATHS "${CINDER_PATH}/${CINDER_LIB_DIRECTORY}"
        )

SET(DCINDER_BOOST_USE_SYSTEM 1)

link_directories(
        /home/nwalker/Documents/bdp/clingo/cmake-build-debug/lib/
)

include_directories(
        /home/nwalker/Documents/bdp/clingo/libclingo/
        /home/nwalker/Documents/bdp/clingo/clasp/
        include
)

add_library(puzzle src/PixelsDomain.cpp src/ASPSolver.cpp include/puzzle/ASPSolver.h include/puzzle/Rule.h src/Puzzle.cpp include/puzzle/Puzzle.h)
add_executable(demo src/Demo.cpp)

target_link_libraries(puzzle
        PUBLIC
        cinder
        cairo
        /home/nwalker/Documents/bdp/clingo/cmake-build-debug/bin/libclingo.so
        )

target_link_libraries( demo
        PUBLIC
        puzzle
        cinder
        cairo
        /home/nwalker/Documents/bdp/clingo/cmake-build-debug/bin/libclingo.so
        )

# Make the domains available next to the binary
file(COPY domains DESTINATION ./)
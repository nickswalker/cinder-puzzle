cmake_minimum_required( VERSION 2.8 FATAL_ERROR )
set( CMAKE_VERBOSE_MAKEFILE ON )

project( creasp )
get_filename_component( CINDER_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../Cinder" ABSOLUTE )
get_filename_component( APP_PATH "${CMAKE_CURRENT_SOURCE_DIR}/" ABSOLUTE )

include( "${CINDER_PATH}/proj/cmake/configure.cmake" )

find_package( cinder REQUIRED PATHS
        PATHS "${CINDER_PATH}/${CINDER_LIB_DIRECTORY}"
        )

SET(DCINDER_BOOST_USE_SYSTEM 1)

add_executable( demo src/Demo.cpp )

link_directories(
        /home/nwalker/Documents/bdp/clingo/cmake-build-debug/lib/
)

include_directories(
        /home/nwalker/Documents/bdp/clingo/libclingo/
        /home/nwalker/Documents/bdp/clingo/clasp/
        include
)

target_link_libraries( demo
        cinder
        /home/nwalker/Documents/bdp/clingo/cmake-build-debug/bin/libclingo.so
        )
# Surge CMake file
# Exports targets for each of our builds
#
# Current Status - this builds the whole shooting match
# See issue 1206 for our working list to get this finished
#

cmake_minimum_required(VERSION 3.10)
set(CMAKE_OSX_DEPLOYMENT_TARGET 10.12 CACHE STRING "Build for 10.12")

project(disquiet0433 VERSION 1.0.0 LANGUAGES CXX ASM)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_EXTENSIONS false)
set(CMAKE_CXX_STANDARD 17)

add_executable( dq0433
  dq0433.cpp )

target_compile_options( dq0433
  PRIVATE
  -Werror
  )

# I should really do sndfile properly here.
include(FindPackageHandleStandardArgs)

find_path(LIBSNDFILE_INCLUDE_DIRS sndfile.h)
find_library(LIBSNDFILE_LIBRARIES sndfile)

target_include_directories( dq0433
  PRIVATE
  ${LIBSNDFILE_INCLUDE_DIRS}
  )
target_link_options( dq0433
  PRIVATE
  ${LIBSNDFILE_LIBRARIES} )

                

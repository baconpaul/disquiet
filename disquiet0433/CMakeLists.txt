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
target_include_directories( dq0433
  PRIVATE
  /usr/local/include
  )
target_link_options( dq0433
  PRIVATE
  -L/usr/local/lib
  -lsndfile )

add_custom_target( run_dq )
add_dependencies( run_dq dq0433 )
add_custom_command(
  TARGET run_dq
  POST_BUILD
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}

  COMMAND Release/dq0433
  )
                

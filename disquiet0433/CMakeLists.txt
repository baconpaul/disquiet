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

add_executable( feedback_drums
  feedback_drums.cpp )

add_custom_target( run_drums )
add_dependencies( run_drums feedback_drums )
add_custom_command(
  TARGET run_drums
  POST_BUILD
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}

  COMMAND Release/feedback_drums
  )
                

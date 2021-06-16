#-------------------------------------------------------------------
# This file is part of the CMake build system for CAVE_ENGINE
#
# The contents of this file are placed in the public domain. Feel
# free to make use of it in any way you like.
#-------------------------------------------------------------------

############################################################
# CaveEngine artificial inteligence library
############################################################

# # define header and source files for the library
file(GLOB HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/Public/*.h")

file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/Private/*.cpp")

file(GLOB NEURAL_NETWORK_HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/Public/NeuralNetwork/*.h")

file(GLOB NEURAL_NETWORK_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/Private/NeuralNetwork/*.cpp")

# # setup OgreMain target

# get_native_precompiled_header(OgreMain)
add_library(Ai SHARED ${HEADER_FILES} ${SOURCE_FILES} ${NEURAL_NETWORK_HEADER_FILES} ${NEURAL_NETWORK_SOURCE_FILES})

if(MSVC)
	target_compile_options(Ai PRIVATE /W4 /WX)
else()
	target_compile_options(Ai PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

target_link_libraries(Ai PUBLIC Core)
target_link_libraries(Ai PUBLIC Opennn)
# target_link_libraries(Ai PUBLIC Tensorflow)

target_include_directories(Ai PUBLIC 
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Public>" 
  "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>"
  $<INSTALL_INTERFACE:include/CAVE_ENGINE>)
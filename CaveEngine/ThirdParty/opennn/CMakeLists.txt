file(GLOB HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/opennn/*.h")
file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/opennn/*.cpp")

add_library(Opennn SHARED ${HEADER_FILES} ${SOURCE_FILES})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")

if(MSVC)
	target_compile_options(Ai PRIVATE /W4 /WX)
else()
	target_compile_options(Ai PRIVATE -Wall -Wextra -pedantic -Werror -fopenmp)
endif()

target_include_directories(Opennn PUBLIC 
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>" 
  "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>"
  $<INSTALL_INTERFACE:include/CAVE_ENGINE>)
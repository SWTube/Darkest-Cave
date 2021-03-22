# CMakeList.txt : CMake project for CMakeProject2, include source and define
# project specific logic here.

# Add source to this project's executable.
add_executable (Template "Main.cpp")

target_link_libraries(Template PUBLIC Core)

target_include_directories(Template PUBLIC "${PROJECT_SOURCE_DIR}/CaveEngine/Core/Public")
# Set minimum required CMake version
cmake_minimum_required(VERSION 3.10.2)

# Set the C++ standard we will use
set(CMAKE_CXX_STANDARD 11)

#  Set the project name
project(learn-opencl)

find_package(OpenCL 1.2 REQUIRED)

include_directories(include ${OpenCL_INCLUDE_DIRS})
link_directories(${OpenCL_LIBRARY_DIRS})
add_definitions(${OpenCL_DEFINITIONS})

# Apply link libraries to all targets
# (must come before add_executable or add_library)
link_libraries(${OpenCL_LIBRARIES})

# Find all common source files
#file(GLOB project_SRCS src/cl_utils.cpp include/cl_utils.hpp)
set(project_SRCS src/cl_utils.cpp)

# Add project executable
add_executable(intro src/intro.cpp ${project_SRCS})
add_executable(hello_world src/hello_world.cpp ${project_SRCS})

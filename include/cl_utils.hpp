#ifndef CL_UTILS_H
#define CL_UTILS_H

#include <CL/cl.hpp>

cl::Program createProgram(const std::string& file);
const char* getErrorString(cl_int error);

#endif
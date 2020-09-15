#include <iostream>
#include <fstream>
#include <CL/cl.hpp>

#include "cl_utils.hpp"

const int USE_UTILS{ 1 };

int main()
{
	cl::Device device;
	cl::Context context;
	cl::Program program; 
	int ret{ 0 };

	if (USE_UTILS) {
		// create OpenCL Program
		cl::Program program = createProgram("hello.cl");

		// get OpenCL Context from Program
		cl::Context context = program.getInfo<CL_PROGRAM_CONTEXT>();

		// get OpenCL Device from Context
		auto devices = context.getInfo<CL_CONTEXT_DEVICES>();
		cl::Device device = devices.front();
	}
	else {
		// do we have one or more OpenCL Platform's available?
		std::vector<cl::Platform> platforms;
		cl::Platform::get(&platforms);

		// get OpenCL 1.2 Platform
		cl::Platform platform = platforms.front();

		// get OpenCL 1.2 Device
		std::vector<cl::Device> devices;
		platform.getDevices(CL_DEVICE_TYPE_ALL, &devices);
		cl::Device device = devices.front();

		std::cout << "\nSelected Device: " << device.getInfo<CL_DEVICE_VENDOR>() <<
			device.getInfo<CL_DEVICE_VERSION>() << std::endl;

		// read the kernel file
		std::ifstream helloWorldFile("hello.cl");
		std::string src(std::istreambuf_iterator<char>(helloWorldFile),
			(std::istreambuf_iterator<char>()));
		cl::Program::Sources sources(1, std::make_pair(src.c_str(), src.length() + 1));

		// create OpenCL Context (contains the physical devices)
		cl::Context context(device);

		// create OpenCL Program
		cl::Program program(context, sources);
		//cl_int ret = program.build();	// will return an error code
		cl_int ret = program.build("-cl-std=CL1.2");	// will return an error code
	}

	// create a buffer to contain the "Hello, World!" string
	char buffer[16] = "00000000000000\n";
	// create the "global" memory that the kernel will write to
	cl::Buffer memBuf(context, CL_MEM_WRITE_ONLY | CL_MEM_HOST_READ_ONLY, sizeof(buffer));

	// create the OpenCL Kernel
	cl::Kernel kernel(program, "hello");
	kernel.setArg(0, memBuf);
	//kernel.setArg(0, (void*)&memBuf);
	//ret = clSetKernelArg(kernel, 0, sizeof(buffer), (void*)&memBuf);

	// create the OpenCL command queue - to send commands from host to device
	cl::CommandQueue queue(context, device);
	// set kernel to execute once
	queue.enqueueTask(kernel);
	// once kernel is executed, we want to read from the global memory on the device (memBuf)
	// to the memory on the host-side (buffer)
	queue.enqueueReadBuffer(memBuf, CL_TRUE, 0, sizeof(buffer), buffer);
	//queue.enqueueReadBuffer(memBuf, CL_TRUE, 0, sizeof(buffer), (void*)&buffer);

	std::cout << buffer;
	//std::cin.get();
}
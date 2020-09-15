#include <iostream>
#include <CL/cl.hpp>

using namespace std;

int main()
{
	cout << "Hello, World!" << endl;

	// do we have one or more OpenCL Platform's available?
	vector<cl::Platform> platforms;
	cl::Platform::get(&platforms);
	try {
		_ASSERT(platforms.size() > 0);
		cout << "We have " << platforms.size() << " OpenCL Platforms avialable."
			<< endl;

		// NOTE: copies of platforms are inexpensive
		for (cl::Platform platform : platforms) {
			// do we have one or more OpenCL Devices's available?
			std::vector<cl::Device> devices;
			platform.getDevices(CL_DEVICE_TYPE_GPU, &devices);
			cout << "\tvendor: " << platform.getInfo<CL_PLATFORM_VENDOR>() <<
				", version: " << platform.getInfo<CL_PLATFORM_VERSION>() << endl;

			try {
				_ASSERT(devices.size() > 0);
				cout << "\t\tWe have " << devices.size() <<
					" OpenCL Device(s) avialable on this platform." << endl;

				for (cl::Device device : devices) {
					// print device vendor and version info
					auto vendor = device.getInfo<CL_DEVICE_VENDOR>();
					auto version = device.getInfo<CL_DEVICE_VERSION>();
					cout << "\t\t\tvendor: " << vendor << ", verison: " << version <<
						endl;
				}				
			}
			catch (const std::exception&) {
				// do nothing
			}
		}

		// get OpenCL 1.2 Platform
		cl::Platform platform = platforms.front();

		// get OpenCL 1.2 Device
		std::vector<cl::Device> devices;
		platform.getDevices(CL_DEVICE_TYPE_ALL, &devices);
		cl::Device device = devices.front();

		cout << "\nSelected Device: " << device.getInfo<CL_DEVICE_VENDOR>() <<
			device.getInfo<CL_DEVICE_VERSION>() << endl;

	}
	catch (const std::exception&) {
		// do nothing
	}

	return 0;
}
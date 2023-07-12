
**Title**: Proposal for a Standardized GPU Programming Interface in C++ Language (std::gpu)

**Document Number**: Nxxxx

**Date**: 12-07-2023-0030 H

**Revises**: N/A

**Reply to**: ahshabazz

---

**Abstract**

This document proposes the addition of a standardized GPU programming interface to the C++ language. The goal of this proposal is to provide a platform-agnostic, efficient, and user-friendly way to program GPUs directly in C++, without the need for vendor-specific extensions or languages.

**Introduction**

With the rise of parallel computing, the use of GPUs for general-purpose computation (GPGPU) has become increasingly common-place in a wide variety of fields, including machine learning (ML), scientific computing, graphics, and more. However, C++ currently does not have native support for GPU programming. Instead, developers must rely on vendor-specific extensions and or libraries such as NVIDIA's CUDA and The Khronos Group's OpenCL, which can introduce non-standard language elements and lack seamless integration with C++ code.

By incorporating a GPU programming interface directly into the C++ standard, we can eliminate these vendor-specific points and make GPU programming more accessible to C++ developers. Additionally, a standardized interface would provide a solid foundation for future extensions and improvements to GPU programming in C++.

**Proposal**

This proposal suggests the addition of a new namespace, `std::gpu`, to the C++ standard library. This namespace would contain classes and functions for managing GPU devices, memory, and kernels, providing a high-level, platform-agnostic interface for programming the GPU.

Key features of the proposed interface include:

1. A `device` class representing a GPU device or devices, with methods for allocating and freeing memory, transferring data between the CPU and GPU, and querying specific device properties.

2. A `kernel` class template representing a function to be executed on the GPU, with a method for launching the kernel on the device.

3. Error handling using standard C++ exceptions, with a new `device_error` class for GPU-specific compile-time and runtime errors.

**Impact on the Standard**

The proposed changes would be largely additive and should not break any existing code. However, this will require modifications to the standard library and potentially the core language to support the definition and execution of GPU kernels.

**Compatibility**

The interface is intended to be platform-agnostic and should work on any system with a compatible GPU. However, it may require support from GPU vendors to implement the interface for their hardware.

**Technical Specifications**

Let's consider a hypothetical GPU interface within the C++ standard. A GPU interface may look like the following:

```
namespace std::gpu {

    // Hypothetical class to represent a GPU device. //

    class device {
    public:
        // Other Existing methods... //
        
    public:
        // List all available devices //
        static std::vector<device> get_devices() { device dev; std::vector<device> v = {dev}; return v; };

        // Copy data from CPU to GPU //
        template <typename T, typename U = std::size_t>
        void copy_to(T& cpu_ref, T& gpu_ref, U num_elements) {};

        // Copy data from GPU to CPU //
        template <typename T, typename U = std::size_t>
        void copy_from(T& gpu_ref, T& cpu_ref, U num_elements) {};

        // Allocate memory on the GPU //
        template <typename T>
        std::vector<T> allocate(const T& num_elements){ std::vector<T> v{num_elements}; return v; };

        // Free memory on the GPU //
        template <typename T>
        int deallocate(const std::vector<T>& ptr) { return 1; };
        
    public:
        // Other existing methods here... //

        // Return the name of the device. //
        std::string name() const { return "nvidia"; };

        // Return the compute capability of the device. //
        std::pair<int, int> compute_capability() const { return std::pair<int,int>(1,1); };

        // Return the number of multiprocessors. //
        int num_multiprocessors() const { return 1; };

        // Return whether the device supports CUDA. //
        bool supports_cuda() const { return true; };

        // Throw a device_error if there's an error on the device //
        void check_error() const {};
    };

    // Hypothetical class to represent a kernel, i.e., a function that runs on the GPU. //
    template <typename T>
    class kernel {
    public:
        kernel(std::function<T(T&)> f) : function_(std::move(f)) {}
    
        T operator()(T& input) {
            // Placeholder for actual GPU computation. //
            return function_(input);
        }
        // Launch the kernel on a device with the given arguments and grid configuration. //
        template <typename... Args>
        T launch(device& dev, std::tuple<int, int, int> grid, std::tuple<int, int, int> block, Args... args){ T t{}; return t; };

        // Throw a device_error if there's an error on the device //
        void check_error() const {};

    private:
        std::function<T(T&)> function_;

        // Rest of the code... //
    };

    class device_error : public std::runtime_error {
    public:
        using std::runtime_error::runtime_error;
    };
}
```

You could then use this API as follows:

```
int main() {
	// Get the first available device //
	std::gpu::device dev = std::gpu::device::get_devices()[0];

	// Allocate an array on the GPU //
	std::vector<float> dev_arr = dev.allocate<float>(1024);

	// kernel alias for std::function<float(float)> //
	using kernel_call = std::function<float&(float&)>;
    
	// Define a kernel //
	std::gpu::kernel<float> add_one([&](float& a){
		// code for kernel here //
		return 1.0f;
	});
    
	// Launch the kernel //
	add_one.launch(dev, {1024, 1, 1}, {1, 1, 1}, dev_arr, 1.0f);

	// Free the memory //
	dev.deallocate(dev_arr);

    return 0;
}
```

This example is extremely simplified and leaves out many details. For example, it doesn't cover how you would move data between the CPU and GPU, handle errors, or write the code for the kernel. These would all be important aspects of a full proposal for GPU support in C++. This code is also not runnable because it's just a hypothetical API.

In reality, a specification for GPU support in C++ would likely be much more complex and take into account a wide range of considerations related to performance, error handling, compatibility with existing GPU programming languages, and more.

An example for how to move data between the CPU and GPU might look like this:

For a standardized C++ GPU interface, data transfer between CPU and GPU memory could be accomplished through methods added to the device class in the hypothetical std::gpu namespace. In the following example, I'll add the `copy_to` and `copy_from` methods for transferring data between CPU and GPU. Here's how you could use these methods:

```
int main() {
    // Create some data on the CPU //
    std::vector<float> cpu_data(1024, 1.0f);

	// Get the first available device //
	std::gpu::device dev = std::gpu::device::get_devices()[0];

	// Allocate an array on the GPU //
	std::vector<float> dev_arr = dev.allocate<float>(1024);
    
	// Copy data from the CPU to the GPU //
	dev.copy_to(cpu_data, dev_arr, cpu_data.size());
    
	// Define a kernel //
	std::gpu::kernel<float> add_one([&](float& a){
		// code for kernel here //
		return 1.0f;
	});
    
	// Launch the kernel //
	add_one.launch(dev, {1024, 1, 1}, {1, 1, 1}, dev_arr, 1.0f);
    
	// Copy data back to the CPU //
	dev.copy_from(dev_arr, cpu_data, cpu_data.size());

	// Free the memory //
	dev.deallocate(dev_arr);

    return 0;
}
```

The allocations/deallocations could also be refactored to assume the GPU device is responsible for managing the memory and executing the memory copy operation, which aligns with how CUDA and other GPU programming interfaces work. Note that the actual kernel code is not provided in this example; it's represented by the string "code for kernel here".

There are also methods to get device details (for example a device which supports CUDA) which enables us to program the GPU, the device class might have methods to return various properties of the GPU, such as the device name, compute capability, number of multiprocessors, and so on.

You could use these methods like so:

```
int main() {
	// Get the first available device //
	std::gpu::device dev = std::gpu::device::get_devices()[0];
    
	// Print out some information about the device //
	std::cout << "Device name: " << dev.name() << '\n';
	auto [major, minor] = dev.compute_capability();
	std::cout << "Compute capability: " << major << '.' << minor << '\n';
	std::cout << "Number of multiprocessors: " << dev.num_multiprocessors() << '\n';
    
	if (dev.supports_cuda()) {
		std::cout << "This device supports CUDA!\n";
	} else {
		std::cout << "This device does not support CUDA.\n";
	}

    // Rest of the code... //

    return 0;
}
```

For an example for error-handling on a GPU with this configuration, you could then use these methods to check for errors in your code:

```
int main() {
    try {
        
        // Get the first available device //
        std::gpu::device dev = std::gpu::device::get_devices()[0];

        // Allocate an array on the GPU //
        std::vector<float> dev_arr = dev.allocate<float>(1024);

        // Check for allocation error //
        dev.check_error();
    
        // Copy data from the CPU to the GPU //
        dev.copy_to(cpu_data, dev_arr, cpu_data.size());

        // Check for copy error
        dev.check_error();
    
        // Define a kernel //
        std::gpu::kernel<float> add_one([&](float& a){
			// code for kernel here //
			return 1.0f;
		});
    
        // Launch the kernel //
        add_one.launch(dev, {1024, 1, 1}, {1, 1, 1}, dev_arr, 1.0f);

        // Check for kernel launch error //
        add_one.check_error();

        // Rest of the code...
    } catch (const std::gpu::device_error& e) {
        std::cerr << "A GPU error occurred: " << e.what() << '\n';
        return 1;
    }

    return 0;
}
```

In this code, if a GPU error occurs, an exception of type `std::gpu::device_error` is thrown. This exception is caught and handled in the catch block, where the error message is printed to the standard error stream.

**Conclusion**

By incorporating a standardized GPU programming interface into C++, we can make GPU programming more accessible, reduce dependence on vendor-specific libraries and extensions, and provide a foundation for future improvements and extensions to GPU programming in C++. We therefore urge the Committee to consider the addition of `std::gpu` to the C++ standard.

**References**

N/A

**Acknowledgements**

N/A

#include <CL/sycl.hpp>
#include <iostream>
#include <vector>

int main() {
    // Define a vector of float values
    std::vector<float> x = {1.0, 2.0, 3.0, 4.0};

    // Define a vector of float values
    std::vector<float> y = {5.0, 6.0, 7.0, 8.0};

    // Create a queue to execute OpenCL commands
    cl::sycl::queue q;

    // Create a buffer to store the x and y vectors
    cl::sycl::buffer<float, 1> x_buf(x.data(), x.size());
    cl::sycl::buffer<float, 1> y_buf(y.data(), y.size());

    // Set the value of alpha to 2.0
    float alpha = 2.0;

    // Execute the saxp function on the x and y vectors
    q.submit([&](cl::sycl::handler &h) {
        // Get access to the x and y buffers
        auto x_acc = x_buf.get_accesscl::sycl::access::mode::read_write(h);
        auto y_acc = y_buf.get_accesscl::sycl::access::mode::read_write(h);

        // Execute the saxp function using a parallel_for loop
        h.parallel_for(cl::sycl::range<1>(x.size()), [=](cl::sycl::id<1> idx) {
            x_acc[idx] = alpha * x_acc[idx] + y_acc[idx];
        });
    });

    // Copy the result from the device back to the host
    auto result = x_buf.get_accesscl::sycl::access::mode::read();

    // Print the result to the console
    for (int i = 0; i < x.size(); i++) {
        std::cout << result[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}

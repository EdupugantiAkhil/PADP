#include <CL/sycl.hpp>
#include <iostream>
#include <vector>
#include <memory>

const size_t N = 1024;

int main() {
  // Create host memory for input and output vectors
  std::vector<float> x(N);
  std::vector<float> y(N);

  // Initialize input vectors
  for (size_t i = 0; i < N; i++) {
    x[i] = 1.0f;
    y[i] = 2.0f;
  }

  // Create a SYCL queue to the default OpenGL device
  cl::sycl::queue q(cl::sycl::opengl_device{});

  // Allocate device memory for input and output vectors
  std::unique_ptr<cl::sycl::buffer<float>> d_x =
      std::make_unique<cl::sycl::buffer<float>>(x.data(), N);
  std::unique_ptr<cl::sycl::buffer<float>> d_y =
      std::make_unique<cl::sycl::buffer<float>>(y.data(), N);

  // Set the alpha coefficient for the SAXP operation
  float alpha = 2.0f;

  // Execute the SAXP kernel on the device
  q.submit([&](cl::sycl::handler &h) {
    // Get access to the device memory
    auto a_x = d_x->get_access<cl::sycl::access::mode::read>(h);
    auto a_y = d_y->get_access<cl::sycl::access::mode::read_write>(h);

    // Create a SYCL parallel_for to execute the SAXP operation
    h.parallel_for<class saxpy>(cl::sycl::range<1>(N), [=](cl::sycl::id<1> idx) {
      // Perform the SAXP operation
      a_y[idx] = alpha * a_x[idx] + a_y[idx];
    });
  });

  // Copy the result back to host memory
  q.memcpy(y.data(), *d_y, N * sizeof(float));

  // Print the result
  std::cout << "y = [";
  for (size_t i = 0; i < N; i++) {
    std::cout << y[i] << " ";
  }
  std::cout << "]" << std::endl;

  return 0;
}

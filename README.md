**Simple Multithreader**

This is a simple header-only C++ library for parallelizing for loops using pthreads. It provides two main functions: `parallel_for` for single-threaded execution and `parallel_for` for double-threaded execution. 

### How to Use

To use the library, include the `simple_multithreader.h` header file in your C++ project. Then, you can use the `parallel_for` functions to parallelize your for loops.

#### Single-threaded execution
```cpp
parallel_for(low, high, lambda_function, num_threads);
```
- `low`: Starting index of the loop.
- `high`: Ending index of the loop.
- `lambda_function`: Lambda function to be executed for each index of the loop.
- `num_threads`: Number of threads to be used for parallelization.

#### Double-threaded execution
```cpp
parallel_for(low1, high1, low2, high2, lambda_function, num_threads);
```
- `low1`, `high1`: Starting and ending indices of the outer loop.
- `low2`, `high2`: Starting and ending indices of the inner loop.
- `lambda_function`: Lambda function to be executed for each index combination of the loops.
- `num_threads`: Number of threads to be used for parallelization.

### Example

```cpp
#include "simple_multithreader.h"
#include <iostream>

int main() {
    int num_elements = 1000;

    // Single-threaded execution
    parallel_for(0, num_elements, [](int i) {
        std::cout << i << std::endl;
    }, 4);

    // Double-threaded execution
    parallel_for(0, num_elements, 0, num_elements, [](int i, int j) {
        std::cout << i << ", " << j << std::endl;
    }, 4);

    return 0;
}
```

### Notes
- Ensure that you compile your program with `-pthread` flag to link with the pthread library.
- It's recommended to carefully choose the number of threads based on the available hardware resources and the nature of the workload.

### Contributions

- Aryan Jain
- Parth Sandeep Rastogi

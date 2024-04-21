**Simple Multithreader**

This repository contains a simple C++ library for parallelizing loop execution using multithreading. It provides functions for parallelizing loops with both single and double parameter lambda functions. The library utilizes the POSIX threads (pthread) library for multithreading.

### Contents

- `simple_multithreader.h`: Header file containing the implementation of the multithreading functions.
- `README.md`: This file, providing an overview of the repository and usage instructions.

### Usage

1. **Include Header File**: Include the `simple_multithreader.h` header file in your C++ project.

   ```cpp
   #include "simple_multithreader.h"
   ```

2. **Call Parallel For Functions**: Use the provided functions `parallel_for` to parallelize loop execution.

   - For single parameter lambda functions:

     ```cpp
     parallel_for(low, high, lambda_function, num_threads);
     ```

   - For double parameter lambda functions:

     ```cpp
     parallel_for(low1, high1, low2, high2, lambda_function, num_threads);
     ```

   Replace `lambda_function` with your lambda function and `num_threads` with the desired number of threads for parallel execution.

### Example

```cpp
#include "simple_multithreader.h"
#include <iostream>

int main() {
    // Example of parallelizing loop execution with a single parameter lambda function
    parallel_for(0, 1000, [](int i) {
        std::cout << i << std::endl;
    }, 4); // 4 threads

    // Example of parallelizing loop execution with a double parameter lambda function
    parallel_for(0, 100, 0, 10, [](int i, int j) {
        std::cout << "i: " << i << ", j: " << j << std::endl;
    }, 2); // 2 threads

    return 0;
}
```

### Contributing

- Aryan Jain
- Parth Sandeep Rastogi

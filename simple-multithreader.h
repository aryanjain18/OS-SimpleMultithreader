#ifndef SIMPLE_MULTITHREADER_H
#define SIMPLE_MULTITHREADER_H

#include <functional>
#include <iostream>
#include <pthread.h>
#include <chrono>
#include <vector>

int numThread;

// Structure to hold thread arguments for single-threaded execution
struct ThreadArgs {
    int low;
    int high;
    std::function<void(int)> lambda;
};

static void *thread_function_single(void *args);

// Structure to hold thread arguments for double-threaded execution
struct ThreadArgsDouble {
    int low1;
    int high1;
    int low2;
    int high2;
    std::function<void(int, int)> lambda;
};

static void *thread_function_double(void *args);

// Function to execute parallel for loop with a single parameter lambda function
void parallel_for(int low, int high, std::function<void(int)> &&lambda, int num) {
    auto start_time = std::chrono::high_resolution_clock::now();

    // Validate the number of threads
    if (num <= 0) {
        std::cerr << "Error: Number of threads must be greater than zero." << std::endl;
        exit(EXIT_FAILURE);
    }

    numThread = num;
    pthread_t threads[numThread];
    std::vector<ThreadArgs> args(numThread);
    int chunk = (high - low) / numThread;

    // Create threads
    for (int i = 0; i < numThread; ++i) {
        int range = (high - low) / numThread;
        int thread_low = low + i * range;
        int thread_high = (i == numThread - 1) ? high : thread_low + range;

        args[i].low = thread_low;
        args[i].high = thread_high;
        args[i].lambda = lambda;

        // Create thread and check for errors
        if (pthread_create(&threads[i], nullptr, thread_function_single, static_cast<void *>(&args[i])) != 0) {
            std::cerr << "Error creating thread " << i << std::endl;

            // Cleanup: Cancel already created threads
            for (int j = 0; j < i; ++j) {
                pthread_cancel(threads[j]);
            }

            // Cleanup: Join remaining threads
            for (int j = i; j < numThread; ++j) {
                if (pthread_join(threads[j], nullptr) != 0) {
                    std::cerr << "Error joining thread " << j << std::endl;
                }
            }

            exit(EXIT_FAILURE);
        }
    }

    // Join threads
    for (int i = 0; i < numThread; ++i) {
        // Join thread and check for errors
        if (pthread_join(threads[i], nullptr) != 0) {
            std::cerr << "Error joining thread " << i << std::endl;

            // Cleanup: Cancel remaining threads
            for (int j = i; j < numThread; ++j) {
                pthread_cancel(threads[j]);
            }

            exit(EXIT_FAILURE);
        }
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << "Execution time: " << duration.count() << " microseconds\n";
}

// Thread function for single-threaded execution
void *thread_function_single(void *args) {
    ThreadArgs *threadArgs = static_cast<ThreadArgs *>(args);

    // Execute the lambda function for the assigned range
    for (int i = threadArgs->low; i < threadArgs->high; ++i) {
        threadArgs->lambda(i);
    }
    pthread_exit(nullptr);
}

// Function to execute parallel for loop with a double parameter lambda function
void parallel_for(int low1, int high1, int low2, int high2, std::function<void(int, int)> &&lambda, int num) {
    auto start_time = std::chrono::high_resolution_clock::now();

    // Validate the number of threads
    if (num <= 0) {
        std::cerr << "Error: Number of threads must be greater than zero." << std::endl;
        exit(EXIT_FAILURE);
    }

    numThread = num;
    pthread_t threads[numThread];
    std::vector<ThreadArgsDouble> args(numThread);
    int chunk = (high1 - low1) / numThread;

    // Create threads
    for (int i = 0; i < numThread; ++i) {
        int range = (high1 - low1) / numThread;
        int thread_low = low1 + i * range;
        int thread_high = (i == numThread - 1) ? high1 : thread_low + range;

        int range2 = (high2 - low2) / numThread;
        int thread_low2 = low2 + i * range2;
        int thread_high2 = (i == numThread - 1) ? high2 : thread_low2 + range2;

        args[i].low1 = thread_low;
        args[i].high1 = thread_high;
        args[i].low2 = low2;
        args[i].high2 = high2;
        args[i].lambda = lambda;

        // Create thread and check for errors
        if (pthread_create(&threads[i], nullptr, thread_function_double, static_cast<void *>(&args[i])) != 0) {
            std::cerr << "Error creating thread " << i << std::endl;

            // Cleanup: Cancel already created threads
            for (int j = 0; j < i; ++j) {
                pthread_cancel(threads[j]);
            }

            // Cleanup: Join remaining threads
            for (int j = i; j < numThread; ++j) {
                if (pthread_join(threads[j], nullptr) != 0) {
                    std::cerr << "Error joining thread " << j << std::endl;
                }
            }

            exit(EXIT_FAILURE);
        }
    }

    // Join threads
    for (int i = 0; i < numThread; ++i) {
        // Join thread and check for errors
        if (pthread_join(threads[i], nullptr) != 0) {
            std::cerr << "Error joining thread " << i << std::endl;

            // Cleanup: Cancel remaining threads
            for (int j = i; j < numThread; ++j) {
                pthread_cancel(threads[j]);
            }

            exit(EXIT_FAILURE);
        }
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << "Execution time: " << duration.count() << " microseconds\n";
}

// Thread function for double-threaded execution
void *thread_function_double(void *args) {
    ThreadArgsDouble *threadArgs = static_cast<ThreadArgsDouble *>(args);

    // Execute the lambda function for the assigned ranges
    for (int i = threadArgs->low1; i < threadArgs->high1; ++i) {
        for (int j = threadArgs->low2; j < threadArgs->high2; ++j) {
            threadArgs->lambda(i, j);
        }
    }

    pthread_exit(nullptr);
}

#endif // SIMPLE_MULTITHREADER_H


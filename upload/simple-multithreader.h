#include <iostream>
#include <list>
#include <functional>
#include <stdlib.h>
#include <cstring>
#include <pthread.h>
#include <ctime>

#ifndef SIMPLE_MULTITHREADER_H
#define SIMPLE_MULTITHREADER_H

// Structure for 1D loop arguments
struct ThreadArgs1D {
	int low, high;
	std::function<void(int)> lambda;
};

// Worker function for 1D loops
static void *thread_worker_1d(void *arg) {
	ThreadArgs1D *args = static_cast<ThreadArgs1D *>(arg);
	for (int i = args->low; i <= args->high; ++i) {
	    args->lambda(i);
	}
	return nullptr;
}

// Structure for 2D loop arguments
struct ThreadArgs2D {
	int low1, high1, low2, high2;
	std::function<void(int, int)> lambda;
};

// Worker function for 2D loops
static void *thread_worker_2d(void *arg) {
	ThreadArgs2D *args = static_cast<ThreadArgs2D *>(arg);
	for (int i = args->low1; i <= args->high1; ++i) {
	    for (int j = args->low2; j <= args->high2; ++j) {
		args->lambda(i, j);
	    }
	}
	return nullptr;
}


// Parallelize a one-dimensional loop
void parallel_for(int low, int high, std::function<void(int)> &&lambda, int numThreads) {
	// Start timing
	clock_t start_time = clock();

	// Adjust number of threads to include main thread
	numThreads = (numThreads > 1) ? numThreads - 1 : 0;

	int range = high - low + 1;
	int chunkSize = (range + numThreads) / (numThreads + 1); // Divide work including main thread

	pthread_t threads[numThreads];
	ThreadArgs1D args[numThreads];

	// Launch worker threads
	for (int i = 0; i < numThreads; ++i) {
	    args[i] = {low + i * chunkSize, std::min(low + (i + 1) * chunkSize - 1, high), lambda};
	    pthread_create(&threads[i], nullptr, thread_worker_1d, &args[i]);
	}

	// Main thread processes its chunk
	int main_low = low + numThreads * chunkSize;
	int main_high = std::min(low + (numThreads + 1) * chunkSize - 1, high);
	for (int i = main_low; i <= main_high; ++i) {
	    lambda(i);
	}

	// Join worker threads
	for (int i = 0; i < numThreads; ++i) {
	    pthread_join(threads[i], nullptr);
	}

	// End timing and print execution time
	clock_t end_time = clock();
	std::cout << "Execution time: " << 1000.0 * (end_time - start_time) / CLOCKS_PER_SEC / 1000.0 << " s\n";
}

// Parallelize a two-dimensional loop
void parallel_for(int low1, int high1, int low2, int high2, std::function<void(int, int)> &&lambda, int numThreads) {
	// Start timing
	clock_t start_time = clock();

	// Adjust number of threads to include main thread
	numThreads = (numThreads > 1) ? numThreads - 1 : 0;

	int range1 = high1 - low1 + 1;
	int chunkSize1 = (range1 + numThreads) / (numThreads + 1);

	pthread_t threads[numThreads];
	ThreadArgs2D args[numThreads];

	// Launch worker threads
	for (int i = 0; i < numThreads; ++i) {
	    args[i] = {low1 + i * chunkSize1, std::min(low1 + (i + 1) * chunkSize1 - 1, high1), low2, high2, lambda};
	    pthread_create(&threads[i], nullptr, thread_worker_2d, &args[i]);
	}

	// Main thread processes its chunk
	int main_low1 = low1 + numThreads * chunkSize1;
	int main_high1 = std::min(low1 + (numThreads + 1) * chunkSize1 - 1, high1);
	for (int i = main_low1; i <= main_high1; ++i) {
	    for (int j = low2; j <= high2; ++j) {
		lambda(i, j);
	    }
	}

	// Join worker threads
	for (int i = 0; i < numThreads; ++i) {
	    pthread_join(threads[i], nullptr);
	}

	// End timing and print execution time
	clock_t end_time = clock();
	std::cout << "Execution time: " << 1000.0 * (end_time - start_time) / CLOCKS_PER_SEC / 1000.0 << " s\n";
}



#endif

int user_main(int argc, char **argv);

/* Demonstration on how to pass lambda as parameter.
 * "&&" means r-value reference. You may read about it online.
 */
void demonstration(std::function<void()> && lambda) {
  lambda();
}

int main(int argc, char **argv) {
  /* 
   * Declaration of a sample C++ lambda function
   * that captures variable 'x' by value and 'y'
   * by reference. Global variables are by default
   * captured by reference and are not to be supplied
   * in the capture list. Only local variables must be 
   * explicity captured if they are used inside lambda.
   */
  int x=5,y=1;
  // Declaring a lambda expression that accepts void type parameter
  auto /*name*/ lambda1 = /*capture list*/[/*by value*/ x, /*by reference*/ &y](void) {
    /* Any changes to 'x' will throw compilation error as x is captured by value */
    y = 5;
    std::cout<<"====== Welcome to Assignment-"<<y<<" of the CSE231(A) ======\n";
    /* you can have any number of statements inside this lambda body */
  };
  // Executing the lambda function
  demonstration(lambda1); // the value of x is still 5, but the value of y is now 5

  int rc = user_main(argc, argv);
 
  auto /*name*/ lambda2 = [/*nothing captured*/]() {
    std::cout<<"====== Hope you enjoyed CSE231(A) ======\n";
    /* you can have any number of statements inside this lambda body */
  };
  demonstration(lambda2);
  return rc;
}

#define main user_main



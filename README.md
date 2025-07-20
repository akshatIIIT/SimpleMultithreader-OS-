# SimpleMultithreader

A header-only C++ library that simplifies multithreaded programming using **POSIX Pthreads** and **C++11 lambda expressions**. This project abstracts away boilerplate thread management by offering easy-to-use `parallel_for()` APIs for 1D and 2D loop parallelization with dynamic thread control.

---

## 🧠 Motivation

Traditional Pthread programming in C/C++ often requires verbose boilerplate code for loop-level parallelism. This project provides a clean and reusable abstraction that minimizes complexity while maintaining control over thread-level execution — especially helpful in academic OS/multithreading environments.

---

## 🚀 Features

- ✅ Header-only, lightweight C++ library (no external dependencies)
- 🧵 Supports both 1D and 2D loop parallelization
- 💡 Uses **C++11 lambda functions** for simple, inline parallel execution
- 🔧 Full control over number of threads
- 📊 Execution time logging for performance benchmarking
- 🔐 Thread-safe, with clean lifecycle management (no thread pooling)

---

## 🛠️ Technologies Used

- **C++11**, **POSIX Pthreads**
- Compiled using `g++` with `-std=c++11`
- Tested on Linux (WSL and Ubuntu)

---

## 📦 File Structure

SimpleMultithreader/
│
├── simple-multithreader.h # Main header-only library
├── example1.cpp # 1D loop example using parallel_for
├── example2.cpp # 2D loop example using parallel_for
├── Makefile # Build script
└── README.md # Project documentation



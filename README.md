# ParaSIMD

ParaSIMD was a university project I did during my second year as part of my Computer Architecture course. The goal was to create and improve a program that does math on floating-point matrices of different sizes. I made different versions of the program:

- A basic sequential version
- An optimized sequential version using techniques like loop unrolling and block-wise operations
- A version using SIMD processing with SSE3 extensions
- A parallelized version using OpenMP

This project was interesting because I learned how to apply computer architecture and parallel programming to a practical problem. I learned how to use cache memory, implement vectorization techniques, and leverage multi-core processors for improved performance.

The results showed that while manual optimizations and compiler flags could improve performance, the OpenMP version performed best, especially when using the same number of threads as CPU cores. The SIMD version using SSE3 didn't perform as well as expected due to overhead and incompatibilities.

But most importantly, I am very proud of having been able to manually achieve the same performance as the GCC compiler auto-optimized version. I did this by applying parallel instructions, multithreading, loop unrolling and refactoring, and other highly advanced techniques such as the usage of matrix decomposition into subunits, which allowed me to achieve the best results in my class. You can check the final report and the outstanding results achieved in the project repository (in Spanish).

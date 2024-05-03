# Optimization-of-Floyd-Warshall-Algorithm
Overview:

This project aims to optimize the Floyd Warshall Algorithm allowing the computation of the all pair shortest paths in comparatively less time.
Implementation of different algorithms like the sequential algorithm, rectangular algorithm and parallel implementation of the blocked Flyod Warshall Algorithm have been analyzed to observe which takes the least time.

Features:
Floyd-Warshall Algorithm: Proven algorithm to return the shortest distance between a pair of points in the graph.
Parallel Processing: Utilizes OpenMP for parallel processing to improve performance on large datasets. 
Generating Random Data: Separate function created to generate random graphs with varying graph size.
Execution Time Analysis: Records and displays the execution time for various input sizes. 

Working:
The algorithms take a square matrix as input, and return the shortest path between any pair of points in the graph.
Different algorithms give varying time complexities for different graph sizes. We have implemented sequential, rectangular, parallel as well as blocked versions of the same.

Requirements:

C++ Compiler with OpenMP support (e.g., GCC) C++ Standard Library

Compilation and Execution

Compile the program with C++ compiler with OpenMP support.

Copy code g++ -std=c++11 -fopenmp <file_name>.cpp -o <file_name> -lstdc++ to compile the program.

bash Copy code ./<file_name> to run the program.

The program will give you the time taken by the graph to give all-pair-shortest-path.

Parallelization:
The code has been parallelized using OpenMP, leading to speed-up in the execution time, especially noticeable for larger datasets. The blocked parallel implementation using 1-D array runs concurrently, hence optimizing performance.

Cache Performance:
To reduce the number of cache misses, we have employed conversion of 2-D array to 1-D array to implement a contiguous block of memory. It improves memory access patterns leading to a better performance.

Conclusion:
Parallelization has significantly improved the Floyd-Warshall algorithm's efficiency, making it more adaptable particularly for handling substantial datasets. This upgrade enhances the algorithm's scalability to fit better with the real world applications. Cache optimization also significantly reduces cache misses. Hence the blocked parallel version employing cache optimization gives us the fastest results.

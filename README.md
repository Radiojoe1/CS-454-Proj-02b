# CS-454-Proj-02b

Members: William Dappen & Nick Guevera

To Run:
Compilation Command:
    g++ main.cpp MultiplierArray.cpp -o CS_454_Proj_02b.exe

Cmake file:
    cmake_minimum_required(VERSION 4.0)
    project(CS_454_Proj_02b)
    
    set(CMAKE_CXX_STANDARD 14)
    
    include_directories(.)
    
    add_executable(CS_454_Proj_02b
    main.cpp
    MultiplierArray.cpp
    MultiplierArray.h)

Extra Credit:
    Compute the time taken for evaluating A^B using this O(n^2) algorithm for multiplication.
    Compare it to the time taken using the O(n^1.585) karatsuba algorithm for multiplication.
    Note number of digits in AB is n = log10(A^B) = B log10(A).

        The time taken for evaluating A^B using a divide and conquer exponentiation algorithm
        and a O(n^2) multiplication algorithm is equal to the product of the time complexity
        required by the multiplication algorithm, and the time complexity of the exponentiation
        algorithm. We already know the number of multiplications done by the exponentiation
        algorithm to be log2(b), and we know that the time complexity of the gradeschool 
        algorithm is theta(n^2). Therefore the time complexity of the exponentiation algorithm
        is theta(n^2 * log2(b)), where n is the number of digits in A^B. Knowing that 
        n = Blog10(A), the final complexity is theta((B log10(A))^2 * log2(b)). Using the
        same process, the karatsuba-based exponentiation algorithm would come out to a
        complexity of theta((B log10(A))^1.585 * log2(b)), making it far faster than the
        gradeschool algorithm. This is true because the exponent in the n log n-like 
        behavior of the algorithm dominates the behavior of the entire function.

    Now fix the value of A (99 or 999) and generate several values of B 
    (from 9 to 999 at an increment of 10) and plot the time taken to evaluate A^B as a function
    of n using the two different methods of multiplication.

    At what value of n is it evident that the karatsuba algorithm for multiplication
    is superior to the O(n2) method of multiplication?


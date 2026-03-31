// Goals: 1) Implement Karatsuba algorithm to multiply two integers A and B whose values are less than or equal to 10000.
//        2) Implement Exponentiation algorithm to evaluate A^B, where A and B are integers less than or equal to 10000.
//           The maximum value of A^B is 10000^10000. This number has 40001 digits. 

/* Task 1: Input: int A, int B, whose values are <= 10000.
           Output: A * B

           Store A and B as vectors. Each digit of the integer is stored separately as an element of the vector.
           Write routine karatsuba_mult to compute A * B.
            This routine must be able to:
                Account for different lengths of A and B
                Account for odd and even lengths.
                Report result without any leading zeroes.

   Task 2: Input: int A, int B, whose values are <= 10000.
           Output: A^B

           Store A and B as integers.
           Employ Karatsuba routine for squaring, do not use multiplication operator to multiply integers with more than 1 digit. 
*/

#include <iostream>
#include <string>
#include <limits>
#include <chrono>
#include <cmath>
#include <fstream>
#include <vector>
#include "MultiplierArray.h"

using Clock = std::chrono::steady_clock;

using Duration = std::chrono::duration<double, std::nano>;

template <typename Func>
Duration measureExecutionTime(Func func, const int& A, const int& B) {
    auto start = Clock::now(); // Get the starting time point

    // Call the function with its arguments
    func(A, B);

    auto end = Clock::now(); // Get the ending time point

    // Calculate the duration and cast it to the desired unit (milliseconds in this case)
    return std::chrono::duration_cast<Duration>(end - start);
}


int main(){
    int a;
    int b;

    std::cout << "Enter A: ";

    while(!(std::cin >> a) || a<=0) || a > 10000) {
        std::cout << "Invalid input. Please try again: ";

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << std::endl << "Enter B: ";
    while(!(std::cin >> b) || b<=0) || b > 10000) {
        std::cout << "Invalid input. Please try again: ";

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    int choice = 0;

    while (true) {
        std::cout << std::endl << "Select an Option:" << std::endl;
        std::cout << "1. Task 1: Multiply A * B" << std::endl;
        std::cout << "2. Task 2: Exponentiate A^B" << std::endl;
        std::cout << "3. Quit" << std::endl;
        std::cout << "4. Extra credit calculation" << std::endl;
        std::cout << "Enter Choice: ";


        while(!(std::cin >> choice)){
            std::cout << "Invalid input. Please try again: ";

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        MultiplierArray result, result2;
        switch (choice) {
            case 1:
                result = MultiplierArray(a) * MultiplierArray(b); // this is using the class overloaded * operator which implements the karatsuba algorithm
                std::cout << "A * B = " << result.toString() << std::endl;
                break;
            case 2:
                result = MultiplierArray::exponentiation(a, b); // this is using the class overloaded * operator which implements the karatsuba algorithm
                std::cout << "A ^ B = " << result.toString() << std::endl;
                break;
            case 3:
                std::cout << "Exiting program." << std::endl;
                return 0;
            case 4: {
                std::cout << "Running Extra Credit Process. A is locked to 99, and B iterates from 9 to 999 in increments of 10.\n";
                std::ofstream outFile("output.csv");

                if (outFile.is_open()) {
                    // File opened successfully
                } else {
                    std::cerr << "Error opening file!" << std::endl;
                    break;
                }
                int aInt = 99;
                outFile << "n,school,karatsuba\n";

                for(int bInt = 9; bInt <= 999; bInt += 10){
                    std::cout << bInt << std::endl;

                    auto school = measureExecutionTime(SchoolyardMultArray::exponentiation, aInt, bInt);
                    auto karatsuba = measureExecutionTime(MultiplierArray::exponentiation, aInt, bInt);
                    int n = static_cast<int>(std::floor(bInt * std::log10(aInt))) + 1;
                    // measure the time of the algorithms and create n

                    outFile << n << ','
                            << school.count() << ','
                            << karatsuba.count() << '\n';
                }
                outFile.close();
                std::cout << "write finished\n";
                break;
            }
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
        }
    }

    return 0;
}

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

    while(!(std::cin >> a) || a<=0){
        std::cout << "Invalid input. Please try again: ";

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << std::endl << "Enter B: ";
    while(!(std::cin >> b) || b<=0) {
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
                std::cout << "A ^ B = " << result.toString() << ", \n";
                break;
            case 3:
                std::cout << "Exiting program." << std::endl;
                exit(1);
                break;
            case 4: {
                std::cout << "Running Extra Credit Process. A is locked to 999, and B iterates from 9 to 999 on 10's\n";
                std::ofstream outFile("output.csv");

                if (outFile.is_open()) {
                    // File opened successfully
                } else {
                    std::cerr << "Error opening file!" << std::endl;
                    break;
                }

                std::vector<Duration> schoolTime, karatsubaTime;
                std::vector<int> ArrayOfN;
                int aInt = 999;
                for(int bInt = 9; bInt<= 999; bInt+=10){
                    std::cout << bInt << std::endl;
                    schoolTime.push_back(measureExecutionTime(SchoolyardMultArray::exponentiation, aInt, bInt));
                    karatsubaTime.push_back(measureExecutionTime(MultiplierArray::exponentiation, aInt, bInt));
                    ArrayOfN.push_back(static_cast<int>(std::floor(bInt * std::log10(aInt))) + 1);
                }

                if(schoolTime.size() == karatsubaTime.size() && ArrayOfN.size() == schoolTime.size()){
                    std::cout << "Success, writing to file\n";
                    outFile << "n, school, karatsuba\n";
                    for(size_t j = 0; j < schoolTime.size(); j++){
                        outFile << ArrayOfN.at(j) << ','
                                << schoolTime.at(j).count() << ','
                                << karatsubaTime.at(j).count() << '\n';
                    }
                    outFile.close();
                    std::cout << "write finished\n";
                } else{
                    std::cout << "Error writing\n";
                }

                break;
            }
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
        }
    }

    return 0;
}
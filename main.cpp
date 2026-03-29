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
#include "MultiplierArray.h"

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
        std::cout << "Enter Choice: ";


        while(!(std::cin >> choice)){
            std::cout << "Invalid input. Please try again: ";

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        MultiplierArray result;
        switch (choice) {
            case 1:
                result = MultiplierArray(a) * MultiplierArray(b); // this is using the class overloaded * operator which implements the karatsuba algorithm
                std::cout << "A * B = " << result.toString() << std::endl;
                break;
            case 2:
                result = MultiplierArray::exponentiation(a, b); // this is using the class overloaded * operator which implements the karatsuba algorithm
                std::cout << "A ^ B = " << result.toString() << std::endl;
            case 3:
                std::cout << "Exiting program." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }

    return 0;
}
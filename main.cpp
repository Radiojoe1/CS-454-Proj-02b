//
// Created by wdapp on 3/21/2026.
//

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

int main(){
    std::cout << "Hello World!" << std::endl;
    return 0;
}
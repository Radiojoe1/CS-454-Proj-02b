#include "MultiplierArray.h"
#include <algorithm>
#include "iostream"

MultiplierArray::MultiplierArray() : contents{0} {}

MultiplierArray::MultiplierArray(int input) : contents(intToDigits(input)) {}

MultiplierArray::MultiplierArray(const Digits& digits) : contents(trimLeadingZeroes(digits)) {}

MultiplierArray MultiplierArray::operator+(const MultiplierArray& rhs) const{
    return MultiplierArray(addDigits(contents, rhs.contents));
}

MultiplierArray MultiplierArray::operator*(const MultiplierArray& rhs) const{
    return MultiplierArray(karatsuba_mult(contents, rhs.contents));
}

std::string MultiplierArray::toString() const{
    std::string result;
    result.reserve(contents.size());

    for (int digit : contents){
        result.push_back(static_cast<char>('0' + digit));
    }

    return result;
}

MultiplierArray::Digits MultiplierArray::intToDigits(int input){
    Digits result;

    if (input == 0){
        result.push_back(0);
        return result;
    }

    while (input > 0){
        result.push_back(input % 10);
        input /= 10;
    }

    std::reverse(result.begin(), result.end());
    return result;
}

MultiplierArray::Digits MultiplierArray::trimLeadingZeroes(const Digits& in){
    int i = 0;
    int lastIndex = static_cast<int>(in.size()) - 1;

    while (i < lastIndex && in[i] == 0){
        i++;
    }

    return Digits(in.begin() + i, in.end());
}

void MultiplierArray::padLeftToEqualLength(Digits& a, Digits& b){
    if (a.size() < b.size()){
        a.insert(a.begin(), b.size() - a.size(), 0);
    } else if (b.size() < a.size()){
        b.insert(b.begin(), a.size() - b.size(), 0);
    }
}

MultiplierArray::Digits MultiplierArray::addDigits(const Digits& a, const Digits& b){
    int i = static_cast<int>(a.size()) - 1;
    int j = static_cast<int>(b.size()) - 1;
    int carry = 0;

    Digits result;

    while (i >= 0 || j >= 0 || carry != 0){
        int sum = carry;

        if (i >= 0){
            sum += a[i];
            i--;
        }

        if (j >= 0){
            sum += b[j];
            j--;
        }

        result.push_back(sum % 10);
        carry = sum / 10; 
    }

    //fix order
    std::reverse(result.begin(), result.end());
    return result;
}

// requires a >= b
MultiplierArray::Digits MultiplierArray::subtractDigits(const Digits& a, const Digits& b){
    int i = static_cast<int>(a.size()) - 1;
    int j = static_cast<int>(b.size()) - 1;
    int borrow = 0;

    Digits result;

    while (i >= 0){
        int diff = a[i] - borrow;

        if (j >= 0){
            diff -= b[j];
            j--;
        }

        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        result.push_back(diff);
        i--;
    }

    std::reverse(result.begin(), result.end());
    return trimLeadingZeroes(result);
} 

MultiplierArray::Digits MultiplierArray::shiftLeftDigits(const Digits& in, int places){
    if (in.size() == 1 && in[0] == 0){
        return in;
    }

    Digits result = in;
    result.insert(result.end(), places, 0);
    return result;
}

std::pair<MultiplierArray::Digits, MultiplierArray::Digits> MultiplierArray::splitDigits(const Digits& in){
    int mid = static_cast<int>(in.size()) /2;
    Digits left(in.begin(), in.begin() + mid);
    Digits right(in.begin() + mid, in.end());
    return {left,right};
}

//Karatsuba Multiplication
//Multiplies two non-negative integers stored as vectors of digits using Karatsuba divide-and-conquer algorithm
//Preconditions:
//  a and b are valid digit vectors with most significant digit first
//  each element of the vector is a decimal digit 0 ... 9
//Postconditions:
//  returns product a * b in the same vector representation
//  result contains no leading zeroes unless the value represented by the vector is zero
MultiplierArray::Digits MultiplierArray::karatsuba_mult(const Digits&a, const Digits& b){
    //base case if either number is 0 return 0
    if((a.size() == 1 && a[0] == 0) || (b.size() == 1 && b[0] == 0)){
        return {0};
    }

    //single digit multiplication
    if (a.size() == 1 && b.size() == 1){
        return intToDigits(a[0] * b[0]); // using standard operator * for single digit multiplications only. result is converted to a vector of digits and returned
    }

    Digits leftInput = a;
    Digits rightInput = b;

    //make lengths equal
    padLeftToEqualLength(leftInput, rightInput);

    //ensure even lengths before splitting. lengths are the same because of the previous line. 
    if (leftInput.size() % 2 != 0){
        leftInput.insert(leftInput.begin(), 0);
        rightInput.insert(rightInput.begin(), 0);
    }
    
    int halfLength = static_cast<int>(leftInput.size()) / 2;

    std::pair<Digits, Digits> leftParts = splitDigits(leftInput);
    std::pair<Digits, Digits> rightParts = splitDigits(rightInput);

    Digits aLeft = leftParts.first; // a
    Digits aRight = leftParts.second; // b
    Digits bLeft = rightParts.first; // c
    Digits bRight = rightParts.second; // d

    Digits p1 = karatsuba_mult(aLeft, bLeft); // ac (first multiplication)
    Digits p2 = karatsuba_mult(aRight, bRight); // bd (second multiplication)

    Digits sumA = addDigits(aLeft, aRight); // a+b
    Digits sumB = addDigits(bLeft, bRight); // c+d

    Digits p3 = karatsuba_mult(sumA, sumB); // (a+b)(c+d) (third multiplication)

    Digits middle = subtractDigits(subtractDigits(p3, p1), p2);
    
    Digits shiftedP1 = shiftLeftDigits(p1,2 * halfLength);
    Digits shiftedMiddle = shiftLeftDigits(middle, halfLength);

    Digits result = addDigits(addDigits(shiftedP1, shiftedMiddle), p2);
    return trimLeadingZeroes(result);
}

MultiplierArray MultiplierArray::exponentiation(int base, int exponent){
    //base cases
    if (exponent == 0) {
        return MultiplierArray(1);
    }

    if (exponent == 1) {
        return MultiplierArray(base);
    }

    MultiplierArray halfPower = exponentiation(base, exponent / 2);
    MultiplierArray squared = halfPower * halfPower; // this is using the overloaded operator for the Multiplier array class, not the built in one

    if (exponent % 2 == 0){
        return squared;
    }

    return squared * MultiplierArray(base);
}

// SCHOOLYARD Array below:

SchoolyardMultArray SchoolyardMultArray::exponentiation(int base, int exponent){
    //base cases
    if (exponent == 0) {
        return SchoolyardMultArray(1);
    }

    if (exponent == 1) {
        return SchoolyardMultArray(base);
    }

    SchoolyardMultArray halfPower = exponentiation(base, exponent / 2);
    SchoolyardMultArray squared = halfPower * halfPower; // this is using the overloaded operator for the Multiplier array class, not the built in one

    if (exponent % 2 == 0){
        return squared;
    }

    return squared * SchoolyardMultArray(base);
}

MultiplierArray::Digits SchoolyardMultArray::SchoolyardMult
(const MultiplierArray::Digits &a, const MultiplierArray::Digits &b)  {
    MultiplierArray::Digits out;
    MultiplierArray::Digits larger, smaller;
    if (a.size() > b.size()) { // choose the smaller item to iterate through first.
        larger = a;
        smaller = b;
    } else {
        larger = b;
        smaller = a;
    }
    int shiftCount = 0;
    for (int i = smaller.size()-1; i >= 0; i--) {

        out = addDigits(out,
                        shiftLeftDigits(SingleMult(smaller[i], larger),
                        shiftCount)); // add out and the individual multiplication of that value by the larger digit with a place offset.
        shiftCount++;
    }
    return out;
}

MultiplierArray::Digits SchoolyardMultArray::SingleMult
(const int value, const MultiplierArray::Digits &arr)
{
    MultiplierArray::Digits out(arr.size(), 0);
    int carry = 0;

    for (int i = arr.size() - 1; i >= 0; --i) { // iterate through the array and progressively multiply up the array by "value"
        int total = value * arr[i] + carry;
        out[i] = total % 10;
        carry = total / 10;
    }

    if (carry > 0) {
        out.insert(out.begin(), carry);
    } // if the nultiplication results in an extra digit

    return trimLeadingZeroes(out);
    }

SchoolyardMultArray SchoolyardMultArray::operator*(const SchoolyardMultArray &rhs) const {
    return SchoolyardMultArray(SchoolyardMult(contents, rhs.contents));
}

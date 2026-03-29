

#ifndef MULTIPLIER_ARRAY_H
#define MULTIPLIER_ARRAY_H

#include <vector>
#include <string>
#include <utility>


class MultiplierArray{
    public:
        //constructors
        MultiplierArray();          // default, {0}
        MultiplierArray(int input);     //construct from integer
        
        //operator overloading
        //does not publicly support subtraction but it is defined internally for use in the karatsuba algorithm
        MultiplierArray operator+(const MultiplierArray& rhs) const;
        MultiplierArray operator*(const MultiplierArray& rhs) const;

        static MultiplierArray exponentiation(int base, int exponent);

        //output
        std::string toString() const;
    
    protected:
        using Digits = std::vector<int>;

        Digits contents;
        
        explicit MultiplierArray(const Digits& digits);

        static Digits intToDigits(int input);
        static Digits trimLeadingZeroes(const Digits& in);
        static void padLeftToEqualLength(Digits& a, Digits& b);
        static Digits addDigits(const Digits& a, const Digits& b);
        static Digits subtractDigits(const Digits& a, const Digits& b); // requires a >= b
        static Digits shiftLeftDigits(const Digits& in, int places);
        static std::pair<Digits, Digits> splitDigits(const Digits& in);
        static Digits karatsuba_mult(const Digits&a, const Digits& b);
};

class SchoolyardMultArray : public MultiplierArray{
        public:
                using MultiplierArray::MultiplierArray;
                SchoolyardMultArray operator*(const SchoolyardMultArray& rhs) const;

        private:
                static Digits SchoolyardMult(const Digits&a, const Digits& b);

                static Digits SingleMult(int value, const Digits& b);
};

#endif

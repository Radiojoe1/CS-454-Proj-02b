//
// Created by wdapp on 3/21/2026.
//

#include "MultiplierArray.h"
MultiplierArray:: MultiplierArray(int input) {
    int newNode;
    std::vector<unsigned char> interVec;

    while(input != 0) {
        newNode = input % 10;
        interVec.push_back(newNode);
        input /= 10;
    }

    while (interVec.size() !=0){ //big endian to little endian
        contents.push_back(interVec.back());
        interVec.pop_back();
    }
}

MultiplierArray::MultiplierArray() {
    contents.push_back(0);
}

void MultiplierArray::push_back(int input){
    contents.push_back(input);
}

MultiplierArray MultiplierArray::operator*(MultiplierArray rhs){
    MultiplierArray out;
    if(this->size() == 1 && rhs.size() == 1){
        out.push_back(this->at(0) * rhs.at(0));
        return out;
    }
    while(this->size() != rhs.size()){
        if(this->size() < rhs.size()){
            this->front_pad();
        } else{
            rhs.front_pad();
        } // equalize sizes;
    }
    auto left = this->split();
    auto right = rhs.split();

    auto p1 = left.second * right.second;
    auto p2 = left.first * right.first;
    auto p3 = ((left.first + left.second) * (right.first + right.second)-p1)-p2;

    auto out1 = p1;
    out1.shift(this->size());
    auto out2 = p3-p2;
    out2 = out2-p1;
    out2.shift(this->size()/2);
    return out1+out2+p2;
}

void MultiplierArray::shift(int shiftAmount){
    for (int i = 0; i <= shiftAmount; ++i) {
        this->push_back(0);
    }
}


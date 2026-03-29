//
// Created by wdapp on 3/21/2026.
//
#include <vector>
#ifndef CS_454_PROJ_02B_MULTIPLIERARRAY_H
#define CS_454_PROJ_02B_MULTIPLIERARRAY_H


class MultiplierArray {
public:
    MultiplierArray(int input) {
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
    MultiplierArray() {
        return;
    }
    void push_back(int input){
        contents.push_back(input);
    }
    MultiplierArray operator*(MultiplierArray rhs){
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

    void shift(int shiftAmount){
        for (int i = 0; i <= shiftAmount; ++i) {
            this->push_back(0);
        }
    }
    std::pair<MultiplierArray,MultiplierArray> split(){
        MultiplierArray oLeft, oRight;
        int i;
        if(this->size() % 2 != 0){
            oLeft.push_back(0);
        }
        for(i = 0; i < this->size()/2; i++){
            oLeft.push_back(this->at(i));
        }
        for (i; i < this->size(); i++) {
            oRight.push_back(this->at(i));
        }
        return std::pair<MultiplierArray, MultiplierArray>(oLeft,oRight);
    }

    MultiplierArray operator+(MultiplierArray rhs){
        int left=0, right=0, sum = 0;
        MultiplierArray out;
        for(int i = std::max(rhs.size(), this->size()); i>0; i--){
            if(i<this->size()){
                left += this->at(i);
            }
            if(i<rhs.size()){
                right = rhs.at(i);
            }
            sum = left + right;
            left = 0;
            right = 0;
            if(sum/10 != 0){
                left = sum / 10;
                sum %= 10;
            }
            out.push_back(sum);
        }
        if(left > 0){
            out.push_back(left);
        }
        return out;
    }

    MultiplierArray operator-(MultiplierArray rhs){
        int left=0, right=0, product = 0;
        MultiplierArray out;
        for(int i = std::max(rhs.size(), this->size()); i>0; i--){
            if(i<this->size()){
                left += this->at(i);
            }
            if(i<rhs.size()){
                right = rhs.at(i);
            }
            product = left - right;
            left = 0;
            right = 0;
            if(product < 0){
                left = -1;
                product += 10;
            }
            out.push_back(product);
        }
        if(left > 0){
            out.push_back(left);
        }
        return out;
    }

    std::size_t size(){
        return contents.size();
    }
    unsigned char at(int input){
        return contents.at(input);
    }
    void front_pad(){
    contents.insert(contents.begin(), 0);
    }
private:

    std::vector<unsigned char>  contents;



};


#endif //CS_454_PROJ_02B_MULTIPLIERARRAY_H

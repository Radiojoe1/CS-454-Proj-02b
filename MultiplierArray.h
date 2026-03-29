//
// Created by wdapp on 3/21/2026.
//
#include <vector>
#ifndef CS_454_PROJ_02B_MULTIPLIERARRAY_H
#define CS_454_PROJ_02B_MULTIPLIERARRAY_H


class MultiplierArray {
public:
    MultiplierArray(int input);
    MultiplierArray();

    void push_back(int input);

    MultiplierArray operator*(MultiplierArray rhs);

    void shift(int shiftAmount);


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

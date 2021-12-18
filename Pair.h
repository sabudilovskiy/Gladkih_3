//
// Created by MRV on 17.12.2021.
//

#ifndef GLADKIH_3_1_PAIR_H
#define GLADKIH_3_1_PAIR_H
#include <string>
class Pair{
    int left;
    int right;
public:
    Pair(int left, int right) : left(left), right(right){}
    std::string to_string(){
        return "(" + std::to_string(left) + ", " + std::to_string(right) + ")";
    }
    int get_left() const {
        return left;
    }
    int get_right() const {
        return right;
    }
};
#endif //GLADKIH_3_1_PAIR_H

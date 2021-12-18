//
// Created by MRV on 17.12.2021.
//

#ifndef GLADKIH_3_1_SUPPORT_H
#define GLADKIH_3_1_SUPPORT_H

int find(bool* arr, int n, bool item){
    int i = 0;
    for (;i < n; i++){
        if (arr[i] == item) {
            return i;
        }
    }
    return -1;
}

#endif //GLADKIH_3_1_SUPPORT_H

#ifndef CUSTOMMATRIX_H
#define CUSTOMMATRIX_H

#include <iostream>

using namespace std;

class CustomMatrix{
public:
    static const int SIZE = 5; // Updated to 5x5 window size
    bool mat[SIZE][SIZE]={0};

    CustomMatrix(){

    }

    //alternate way to instantiate the class
    CustomMatrix(bool m[SIZE][SIZE]){
        for (int i=0; i < SIZE; i++) {
            for(int j=0; j < SIZE; j++){
                mat[i][j] = m[i][j];
            }
        }
    }

    void fillMatrix(bool m[SIZE][SIZE]){
        for (int i=0; i < SIZE; i++) {
            for(int j=0; j < SIZE; j++){
                mat[i][j] = m[i][j];
            }
        }
    }
};

#endif // CUSTOMMATRIX_H

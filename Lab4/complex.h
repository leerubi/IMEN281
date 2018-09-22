//
//  complex.h
//  IMEN281
//
//  Created by ruby on 2017. 9. 19..
//  Copyright © 2017년 ruby. All rights reserved.
//

#ifndef complex_h
#define complex_h

#include <iostream>
using namespace std;

class ComplexNum
{
private:
    double real_num;
    double imagin_num;
    
public:
    bool isDivided;
    void setReal(double _real_num);
    void setImagin(double _imagin_num);
    double getReal();
    double getImagin();
    
    //Calculation
    void plus(const ComplexNum &c2);
    void minus(const ComplexNum &c2);
    void multiply(const ComplexNum &c2);
    void divide(const ComplexNum &c2);
    
    //Compare
    bool compare(const ComplexNum &c2);
    
    //Print complex number
    void show_complex_num();
    
    //Set constructor by using default parameters
    ComplexNum(double _real_num = 0, double _imagin_num = 0) :real_num(_real_num), imagin_num(_imagin_num) {}
    
};

void bubbleSort(ComplexNum *arr, int count);
bool is1234(int input);

#endif /* complex_h */

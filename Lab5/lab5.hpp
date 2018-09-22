//
//  lab5.hpp
//  IMEN281
//
//  Created by ruby on 2017. 9. 22..
//  Copyright © 2017년 ruby. All rights reserved.
//

#ifndef lab5_hpp
#define lab5_hpp

#include <stdio.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class ComplexNum{
    double real_num;
    double imagin_num;
public:
    void setReal(double _real_num);
    void setImagin(double _imagin_num);
    double getReal();
    double getImagin();
    bool compare(const ComplexNum &c2);
    
    ComplexNum(double _real_num = 0, double _imagin_num = 0) :real_num(_real_num), imagin_num(_imagin_num) {}
};

void ReadInput(char *inputName, vector<ComplexNum> &list);
void WriteOutput1(char *outputName1, vector<ComplexNum> &list);
void WriteOutput2(char *outputName2, vector<ComplexNum> &list);
void bubbleSort(vector<ComplexNum> &arr, int count);


#endif /* lab5_hpp */


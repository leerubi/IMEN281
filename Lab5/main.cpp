//
//  main.cpp
//  IMEN281
//
//  Created by ruby on 2017. 9. 22..
//  Copyright © 2017년 ruby. All rights reserved.
//

#include <iostream>
#include "lab5.hpp"

int main(int argc, const char * argv[]) {
    vector <ComplexNum> list;
    
    ReadInput("input.csv", list);
    WriteOutput1("output1.csv", list);
    WriteOutput2("output2.csv", list);
    
    return 0;
}

//
//  main.cpp
//  IMEN281
//
//  Created by ruby on 2017. 9. 26..
//  Copyright © 2017년 ruby. All rights reserved.
//

#include <iostream>
#include "lab6.hpp"
#include <time.h>
using namespace std;

int main(int argc, char *argv[])
{
    clock_t clockA;
    double sorting_time;
       
    if (argc != 4)//
    {
        cout << "이 프로젝트는 exe파일 input파일 output1파일 output2파일을 인자로 받아야 합니다." << endl;
        return 0;
    }
    
    vector<ComplexNum> list;
    ReadInput(argv[1], list);
    WriteOutput(argv[2], list);
    clockA = clock();
    bubbleSort(list, (int)list.size());
    sorting_time = (double)(clock() - clockA) / CLOCKS_PER_SEC;
    
    WriteOutput(argv[3], list);
   
    cout << "sorting time: " << sorting_time << endl;
    system("pause");
    return 0;
}


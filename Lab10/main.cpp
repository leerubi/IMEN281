//
//  main.cpp
//  IMEN281_LAB10
//
//  Created by ruby on 2017. 10. 17..
//  Copyright © 2017년 ruby. All rights reserved.
//

#include <iostream>
#include <ctime>
#include "Point.hpp"
bool Compare(const Point & c1, const Point & c2);

int main(int argc, char * argv[]) {
    // vector<Point> pointList, pointMyList;
    
    vector< Point > point_vector;
    list< Point > point_list;

    if (argc != 2) {
        cout << "이 프로젝트는 exe파일 input파일을 인자로 받아야 합니다." << endl;
        return -1;
    }
    if (!Point::readInput(argv[1], point_vector, point_list))
        return -1;
    
    clock_t start;
    double vectorRunTime = 0;
    start = clock();
    sort(point_vector.begin(), point_vector.end(), Compare);
    vectorRunTime = (double)(clock() - start);
    
    double listRunTime = 0;
    start = clock();
    point_list.sort(Compare);
    listRunTime = (double)(clock() - start);
    
    Point::showResult(10000, vectorRunTime, listRunTime);
    
    return 0;
}

bool Compare(const Point & c1, const Point & c2){
    return c1.distance > c2.distance;
}


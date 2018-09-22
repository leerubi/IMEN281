//
//  main.cpp
//  IMEN281_LAB9
//
//  Created by ruby on 2017. 10. 12..
//  Copyright © 2017년 ruby. All rights reserved.
//

#include <iostream>
#include <ctime>
#include "point.h"

int main(int argc, char * argv[]) {
	vector<Point> pointList, pointMyList;
	if (argc != 2) {
		cout << "이 프로젝트는 exe파일 input파일을 인자로 받아야 합니다." << endl;
		return -1;
	}
	if (!Point::readInput(argv[1], pointList, pointMyList))
		return -1;

	clock_t start;
	double myRunTime = 0;
	start = clock();
	Point::mySort(pointMyList);
	myRunTime = (double)(clock() - start);

	double runTime = 0;
	start = clock();
	sort(pointList.begin(), pointList.end());
	myRunTime = (double)(clock() - start);

	Point::showResult(100000, myRunTime, runTime);

	return 0;
}


#pragma once
//
//  Point.hpp
//  IMEN281_LAB9
//
//  Created by ruby on 2017. 10. 12..
//  Copyright © 2017년 ruby. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

class Point {
public:
	// 멤버 변수
	int item_num;
	double Coo_x;
	double Coo_y;
	double distance;

	// 생성자
	Point(int _x = 0, int _y = 0) : Coo_x(_x), Coo_y(_y) {
		double _distance = sqrt((double)_x*_x + (double)_y*_y);
		distance = _distance;
	}

	// 연산자 오버로딩
	bool operator<(const Point& point) const {
		return this->distance < point.distance;
	}

	// 메소드
	static bool readInput(char *inputName, vector<Point> &pointList, vector<Point> &pointMyList);
	static void mySort(vector<Point> &pointList);
	static void showResult(int item_num, double myRunTime, double runTime);
};




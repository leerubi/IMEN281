//
//  Point.cpp
//  IMEN281_LAB9
//
//  Created by ruby on 2017. 10. 12..
//  Copyright © 2017년 ruby. All rights reserved.
//

#include <string>
#include "point.h"

bool Point::readInput(char *inputName, vector<Point> &pointList, vector<Point> &pointMyList) {  // input 파일 읽고 list에 저장
	ifstream fin(inputName);
	if (!fin.is_open()) { // 파일 오픈 실패 시 오류 메시지 출력하고 함수 종료
		cout << inputName << " 이 열리지 않음" << endl;
		return false;
	}

	string dummy;
	getline(fin, dummy);    // 첫번째 줄 처리

	string _num, _x, _y;
	int num;
	double x, y;
	while (!fin.eof()) {  // 인풋 파일 읽어서 Point 객체 생성 및 리스트에 저장
		getline(fin, _num, ',');
		if (_num == "")
			break;
		getline(fin, _x, ',');
		getline(fin, _y);
		num = stoi(_num);
		x = stoi(_x);
		y = stoi(_y);
		pointList.push_back(Point(x, y));
		pointMyList.push_back(Point(x, y));
	}
	fin.close();
	return true;
}

void Point::mySort(vector<Point> &pointList) {
	for (int j = (int)pointList.size() - 1; j > 0; j--) {
		for (int i = 0; i < j; i++) {
			if (pointList[i].distance > pointList[i + 1].distance) {
				Point temp = pointList[i];
				pointList[i] = pointList[i + 1];
				pointList[i + 1] = temp;
			}
		}
	}
}

void Point::showResult(int item_num, double myRunTime, double runTime) {
	cout << "원소 갯수 : " << item_num << endl;
	cout << "Buuble sort 소요 시간 : " << myRunTime / 1000 << " 초" << endl;
	cout << "STL sort 소요 시간 : " << runTime / 1000 << " 초" << endl;
}

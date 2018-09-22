#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

class Point {
public:
	// ��� ����
	int item_num;
	double Coo_x;
	double Coo_y;
	double distance;

	// ������
	Point(int _x = 0, int _y = 0) : Coo_x(_x), Coo_y(_y) {
		double _distance = sqrt((double)_x*_x + (double)_y*_y);
		distance = _distance;
	}

	// ������ �����ε�
	bool operator<(const Point& point) const {
		return this->distance < point.distance;
	}

	// �޼ҵ�
	static bool readInput(string inputName, vector<Point> &pointList, vector<Point> &pointMyList, vector<Point> &pointMergeList);
	static void mySort(vector<Point> &pointList);
	static void Merge(vector<Point> &pointMergeList, int p, int q, int r);
	static void Merge_Sort(vector<Point> &pointMergeList, int p, int r);
	static void showResult(int item_num, double myRunTime, double runTime, double MergeRunTime);
};

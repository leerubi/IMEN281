#include <iostream>
#include <ctime>
#include "Point.h"

int main(int argc, char * argv[]) {
	vector<Point> pointList, pointMyList, pointMergeList;
	string filename = "input_2000.csv";
	if (!Point::readInput(filename, pointList, pointMyList, pointMergeList))
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

	double MergeRunTime = 0;
	start = clock();
	Point::Merge_Sort(pointMergeList, 0, pointMergeList.size() - 1);
	MergeRunTime = (double)(clock() - start);
	Point::showResult(2000, myRunTime, runTime, MergeRunTime);
	
	return 0;
}

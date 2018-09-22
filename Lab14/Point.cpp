#include "Point.h"
#include <string>


bool Point::readInput(string inputName, vector<Point> &pointList, vector<Point> &pointMyList, vector<Point> &pointMergeList) {  // input ���� �а� list�� ����
	ifstream fin(inputName);
	if (!fin.is_open()) { // ���� ���� ���� �� ���� �޽��� ����ϰ� �Լ� ����
		cout << inputName << " �� ������ ����" << endl;
		return false;
	}

	string dummy;
	getline(fin, dummy);    // ù��° �� ó��

	string _num, _x, _y;
	int num;
	double x, y;
	while (!fin.eof()) {  // ��ǲ ���� �о Point ��ü ���� �� ����Ʈ�� ����
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
		pointMergeList.push_back(Point(x, y));
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

void Point::Merge(vector<Point> &pointMergeList, int p, int q, int r) {
	int n1 = q - p + 1;
	int n2 = r - q;
	vector<Point> L(n1), R(n2);
	copy(pointMergeList.begin() + p, pointMergeList.begin() + q + 1, L.begin());
	copy(pointMergeList.begin() + q + 1, pointMergeList.begin() + r + 1, R.begin());
	L.push_back(100000);
	R.push_back(100000);

	int i, j;
	i = j = 0;
	for (int k = p; k <= r; k++) {
		if (L[i].distance <= R[j].distance)
			pointMergeList[k] = L[i++];
		else
			pointMergeList[k] = R[j++];
	}
}

void Point::Merge_Sort(vector<Point> &pointMergeList, int p, int r) {
	if (p<r) {
		int q = (p + r) / 2;
		Merge_Sort(pointMergeList, p, q);
		Merge_Sort(pointMergeList, q + 1, r);
		Merge(pointMergeList, p, q, r);
	}
}

void Point::showResult(int item_num, double myRunTime, double runTime, double MergeSortTime) {
	cout << "���� ���� : " << item_num << endl;
	cout << "Buuble sort �ҿ� �ð� : " << myRunTime / 1000 << " ��" << endl;
	cout << "STL sort �ҿ� �ð� : " << runTime / 1000 << " ��" << endl;
	cout << "Merge sort �ҿ� �ð� : " << MergeSortTime / 1000 << " ��" << endl;
}

//
//  Point.cpp
//  IMEN281_LAB10
//
//  Created by ruby on 2017. 10. 17..
//  Copyright © 2017년 ruby. All rights reserved.
//

#include <string>
#include "Point.hpp"

bool Point::readInput(char *inputName, vector<Point> &point_vector, list<Point> &point_list){  // input 파일 읽고 vector, list에 저장
    ifstream fin(inputName);
    if ( !fin.is_open() ) { // 파일 오픈 실패 시 오류 메시지 출력하고 함수 종료
        cout << inputName << " 이 열리지 않음" << endl;
        return false;
    }
    
    string dummy;
    getline(fin, dummy);    // 첫번째 줄 처리
    
    string _num, _x, _y;
    int num;
    double x, y;
    while ( !fin.eof() ) {  // 인풋 파일 읽어서 Point 객체 생성 및 리스트에 저장
        getline(fin, _num, ',');
        if (_num == "")
            break;
        getline(fin, _x, ',');
        getline(fin, _y);
        num = stoi(_num);
        x = stoi(_x);
        y = stoi(_y);
        point_vector.push_back(Point(x, y));
        point_list.push_back(Point(x, y));
    }
    fin.close();
    return true;
}

void Point::showResult(int item_num, double vectorRunTime, double listRunTime){
    cout<< "Size of vector : " << item_num << endl;
    cout << "vector sort sorting time : " << vectorRunTime/1000 << " sec" << endl;
    cout << "list sort sorting time : " << listRunTime/1000 << " sec" << endl;
}

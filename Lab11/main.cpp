//
//  main.cpp
//  IMEN281_LAB11
//
//  Created by ruby on 2017. 10. 19..
//  Copyright © 2017년 ruby. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <map>
#include<string>

using namespace std;

typedef multimap<string,string> MyMultimap;

int main(){
    // 파일 오픈 후 저장
    MyMultimap stocks;
    //string inputFile = argv[1];

	ifstream fin;
	fin.open("input_20.csv");
    if ( !fin.is_open() ) { // 파일 오픈 실패 시 오류 메시지 출력하고 함수 종료
        cout << " 이 열리지 않음" << endl;
        return -1;
    }
    
    string dummy;
    getline(fin, dummy);    // 첫번째 줄 처리
    
    string name, num;
    while ( !fin.eof() ) {  // 인풋 파일 읽어서 저장
        getline(fin, name, ',');
        getline(fin, num);
        stocks.insert(pair<string,string>(name,num));
    }
    fin.close();
    
    // 메인 프로그램
    while (true) {
        char inputChar;
        cout << "원하는 메뉴를 입력하세요<s : search, l : list, e : exit> : "; cin >> inputChar;
        if (inputChar == 'e')
            break;
        switch (inputChar) {
            case 's': {
                // 이름을 받아 전화번호부 출력
                string inputName;
                cout << "이름 : "; cin >> inputName;
                MyMultimap::iterator pos;
                pair <multimap<string,string>::iterator, multimap<string,string>::iterator> ret;
                ret = stocks.equal_range(inputName);
                for (multimap<string,string>::iterator it=ret.first; it!=ret.second; ++it)
                        cout << it->first << " : " << it->second << endl;
                cout << endl;
                
            }
                break;
            case 'l': {
                // 전화번호부 전체 출력
                MyMultimap::iterator pos;
                for (pos = stocks.begin(); pos!=stocks.end(); ++pos) {
                    cout << "이름: " << pos->first << "\t"
                    << "전화번호: " << pos->second << endl;
                }
                cout << endl;
            }
                break;
            default: {
                cout << "유효하지 않은 메뉴입니다" << endl << endl;
            }
                break;
        }
    }
    return 0;
};


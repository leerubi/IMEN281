//
//  main.cpp
//  IMEN281_LAB8
//
//  Created by ruby on 2017. 10. 10..
//  Copyright © 2017년 ruby. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include "Employee.hpp"

using namespace std;

int main(int argc, const char * argv[]) {

    EmployeeHandler handler;
    
    //temporary list 읽어서 add
    string inputTemporary = "TemporaryList.csv";
    ifstream fin1(inputTemporary);
    if ( !fin1.is_open() ) { // 파일 오픈 실패 시 오류 메시지 출력하고 프로그램 종료
        cout << inputTemporary << " 이 열리지 않음" << endl;
        return -1;
    }
    
    string dummy;
    getline(fin1, dummy);    // 첫번째 줄 처리
    
    string name, _phon_num, address, _payPerHour, _time;
    int phon_num, payPerHour, time;
    while ( !fin1.eof() ) {
        getline(fin1, name, ',');            // name에 임시 저장
        if (name == "")
            break;
        getline(fin1, _phon_num, ',');
        phon_num = stoi(_phon_num);         // phon_num 임시 저장
        getline(fin1, address, ',');         // address 임시 저장
        getline(fin1, _payPerHour, ',');
        payPerHour = stoi(_payPerHour);     // payPerHour 임시 저장
        getline(fin1, _time);
        time = stoi(_time);                 // time 임시 저장
        
        // TemporaryWorker 생성 및 리스트에 추가
        TemporaryWorker * a = new TemporaryWorker(name, phon_num, address, payPerHour);
        a->AddWorkTime(time);
        handler.AddEmployee(a);
    }
    fin1.close();
    
    //permanent list 읽어서 add
    string inputPermenant = "PermanentList.csv";
    ifstream fin2(inputPermenant);
    if ( !fin2.is_open() ) { // 파일 오픈 실패 시 오류 메시지 출력하고 프로그램 종료
        cout << inputPermenant << " 이 열리지 않음" << endl;
        return -1;
    }
    
    getline(fin2, dummy);    // 첫번째 줄 처리
    
    string _money;
    int money;
    while ( !fin2.eof() ) {
        getline(fin2, name, ',');            // name에 임시 저장
        if (name == "")
            break;
        getline(fin2, _phon_num, ',');
        phon_num = stoi(_phon_num);     // phon_num 임시 저장
        getline(fin2, address, ',');         // address 임시 저장
        getline(fin2, _money);
        money = stoi(_money);           // money 임시 저장
        
        // PermenantWorker 생성 및 리스트에 추가
        handler.AddEmployee(new PermenantWorker(name, phon_num, address, money));
    }
    fin2.close();
    
    // 직원 급여 정보 출력
    handler.ShowAllSalaryInfo();
    handler.ShowTotalSalaryInfo();

    return 0;
}

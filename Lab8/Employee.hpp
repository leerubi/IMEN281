//
//  Employee.hpp
//  IMEN281_LAB8
//
//  Created by ruby on 2017. 10. 10..
//  Copyright © 2017년 ruby. All rights reserved.
//

#ifndef Employee_hpp
#define Employee_hpp

#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

class Employee {
private:
    string name;
    int phon_num;
    string address;
    
public:
    Employee(string _name, int _phon_num, string _address) {
        name = _name;
        address = _address;
        phon_num = _phon_num;
    }
    void ShowYourInfo() {
        cout << "name: " << name << endl;
        cout << "cell: " << phon_num << endl;
        cout << "addreess:" << address << endl;
    }
    virtual int GetPay() { return 0; }
    virtual void ShowSalaryInfo() {}
};

class PermenantWorker : public Employee {
private:
    int salary;
public:
    PermenantWorker(string name, int phon_num, string address, int money)
    : Employee(name, phon_num, address), salary(money) {}
    int GetPay() { return salary; }
    void ShowSalaryInfo() {
        ShowYourInfo();
        cout << "salary: " << GetPay() << endl << endl;
    }
};

class TemporaryWorker :public Employee {
private:
    int workTime;//이 달에 일한 시간의 합계
    int payPerHour;//시간당 급여
public:
    TemporaryWorker(string name, int phon_num, string address, int _payPerHour)
    : Employee(name, phon_num, address), workTime(0), payPerHour(_payPerHour){}
    void AddWorkTime(int time) {
        workTime += time;
    }
    int GetPay() {
        return workTime* payPerHour;
    }
    void ShowSalaryInfo() {
        ShowYourInfo();
        cout << "salary: " << GetPay() << endl << endl;
    }
};

class EmployeeHandler {
private:
    Employee* empList[50];
    int empNum;
public:
    EmployeeHandler() : empNum(0) {}
    
    void AddEmployee(Employee* emp) {
        empList[empNum++] = emp;
    }
    void ShowAllSalaryInfo() {
        for (int i = 0; i < empNum; i++) {
            empList[i]->ShowSalaryInfo();
        }
    }
    void ShowTotalSalaryInfo() {
        int sum = 0;
        for (int i = 0; i < empNum; i++)
            sum += empList[i]->GetPay();
        cout << "salary sum: " << sum << endl;
    }
    
    ~EmployeeHandler() {
        for (int i = 0; i < empNum; i++)
            delete empList[i];
    }
};

#endif /* Employee_hpp */

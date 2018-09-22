//
//  lab6.cpp
//  IMEN281
//
//  Created by ruby on 2017. 9. 26..
//  Copyright © 2017년 ruby. All rights reserved.
//

#include "lab6.hpp"

void ReadInput(char *inputName, vector<ComplexNum> &list){  // input 파일 읽고 list에 저장
    ifstream fin(inputName);
    if ( !fin.is_open() ) { // 파일 오픈 실패 시 오류 메시지 출력하고 함수 종료
        cout << inputName << " 이 열리지 않음" << endl;
        return;
    }
    
    string sline;
    getline(fin, sline, ',');   // 첫번째 줄의 "Real" 처리
    getline(fin, sline);        // 첫번째 줄의 "Imagainary" 처리 
    
    double real_temp, imagin_temp;
    while ( !fin.eof() ) {
        getline(fin, sline, ',');   // ',' 를 만나기 까지 읽은 문자열을 정수로 변환하여 real_num에 저장
        if (sline == "")
            break;
            
        real_temp = stoi(sline);
        getline(fin, sline);    // 라인의 마지막까지 읽은 문자열을 정수로 변환하여 imagin_num에 저장
        imagin_temp = stoi(sline);
        list.push_back( ComplexNum(real_temp, imagin_temp) );
    }
    fin.close();
}

void WriteOutput(char *outputName, vector<ComplexNum> &list){ // input 파일을 그대로 복사해서 출력하는 함수
    ofstream fout(outputName);
    if ( !fout.is_open() ) {    // 파일 오픈 실패 시 오류 메시지 출력하고 함수 종료
        cout << outputName << " 이 열리지 않음" << endl;
        return;
    }
    
    fout << "Real" << ',' << "Imagainary" << endl;  // 첫번째 줄의 실수부, 허수부 문자열 입력
    for ( int i = 0; i < list.size(); i++ )   // 데이터 출력
        fout << list[i].getReal() << ',' << list[i].getImagin() << endl;
    fout.close();
}


void ComplexNum::setReal(double _real_num){
    real_num = _real_num;
}

void ComplexNum::setImagin(double _imagin_num){
    imagin_num = _imagin_num;
}

double ComplexNum::getReal(){
    return real_num;
}

double ComplexNum::getImagin(){
    return imagin_num;
}

bool ComplexNum::compare(const ComplexNum &c2){
    
    if (real_num > c2.real_num )
        return true;    //앞의 것이 크면 true 반환
    else
        return false;
    
}

void bubbleSort(vector<ComplexNum> &arr, int count){
    
    for ( int j = count - 1; j > 0; j--) {
        
        for ( int i = 0; i < j; i++) {
            
            if ( arr[i].compare(arr[i+1]) ) {
                
                ComplexNum temp = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = temp;
                
            }
            else if ( arr[i].getReal() == arr[i+1].getReal() ){  //real_num이 같은 경우
                
                if ( arr[i].getImagin() > arr[i+1].getImagin() ) {
                    
                    ComplexNum temp = arr[i];
                    arr[i] = arr[i+1];
                    arr[i+1] = temp;
                    
                }
                
            }
            
        }
        
    }
    
}

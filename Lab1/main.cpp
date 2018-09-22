//
//  main.cpp
//  IMEN281
//
//  Created by ruby on 2017. 9. 7..
//  Copyright © 2017년 ruby. All rights reserved.
//

#include <iostream>

using std::cout;
using std::cin;
using std::endl;

enum {EXIT, ADD , SUBTRACT, MULTIPLY, DIVIDE};

void add(double * ptr);
void subtract(double * ptr);
void multiply(double * ptr);
void divide(double * ptr);
void showResult(double * ptr);

int main(int argc, const char * argv[]) {
    
    
    cout<<"복소수 연산 프로그램입니다.";
    
    while (1) {
        
        int input;
        double arr[6];
        
        cout<<"원하는 4칙 연산을 선택하시오(1 = 더하기, 2 = 빼기, 3 = 곱셈, 4 = 나누기, 0 = 프로그램 마치기): ";
        cin>>input;
        
        
        if (input == EXIT) {
            
            cout<<"프로그램을 종료합니다"<<endl;
            break;
            
        }
        
        cout<<"첫번째 복소수를 실수부 허수부 순서로 입력하세요: ";
        cin>>arr[0]>>arr[1];
        cout<<"두번째 복소수를 실수부 허수부 순서로 입력하세요: ";
        cin>>arr[2]>>arr[3];
        
        switch (input) {
            case ADD:
                add(arr);
                break;
            case SUBTRACT:
                subtract(arr);
                break;
            case MULTIPLY:
                multiply(arr);
                break;
            case DIVIDE:
                divide(arr);
                break;
            default:
                cout<<"다시 입력하세요"<<endl;
                break;
        }
        
    }
    
    return 0;
}

void add(double * ptr){

    ptr[4] = ptr[0] + ptr[2];
    ptr[5] = ptr[1] + ptr[3];
    
    showResult(ptr);

}
void subtract(double * ptr){
    
    ptr[4] = ptr[0] - ptr[2];
    ptr[5] = ptr[1] - ptr[3];
    
    showResult(ptr);
    
}

void multiply(double * ptr){
    
    ptr[4] = (ptr[0]*ptr[2]) - (ptr[1]*ptr[3]);
    ptr[5] = (ptr[1]*ptr[2]) + (ptr[0]*ptr[3]);
    
    showResult(ptr);
    
}

void divide(double * ptr){
   
    ptr[4] = ((ptr[0]*ptr[2]) + (ptr[1]*ptr[3]))
            / ((ptr[2]*ptr[2]) + (ptr[3]*ptr[3]));
    ptr[5] = ((ptr[1]*ptr[2]) - (ptr[0]*ptr[3]))
            / ((ptr[2]*ptr[2]) + (ptr[3]*ptr[3]));
    
    showResult(ptr);
    
}

void showResult(double * ptr){
    
    cout<<"결과: "<<ptr[4]<<" ";

    if ( ptr[5] >= 0 ) {
        cout<<"+ ";
    }
    
    cout<<ptr[5]<<" i"<<endl<<endl;
    
}










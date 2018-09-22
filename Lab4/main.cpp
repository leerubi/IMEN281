//
//  main.cpp
//  IMEN281
//
//  Created by ruby on 2017. 9. 7..
//  Copyright © 2017년 ruby. All rights reserved.
//

#include <iostream>
#include "complex.h"

using std::cout;
using std::cin;
using std::endl;


int main(int argc, const char * argv[]) {
    
    int input;
    double real_num1, real_num2;
    double imagin_num1, imagin_num2;
    
    while (true) {
        
        cout << endl << "원하는 4칙 연산을 선택하시오(1 = 더하기, 2 = 빼기, 3 = 곱셈, 4 = 나누기, 5 = 배열 정렬, 0 = 나가기)" << endl;
        cin >> input;
        
        
        if (is1234(input)) {
            
            cout << "첫번째 복소수를 실수부 허수부 순으로 입력하세요: ";
            cin >> real_num1 >> imagin_num1;
            ComplexNum c1(real_num1, imagin_num1);
            cout << "두번째 복소수를 실수부 허수부 순으로 입력하세요: ";
            cin >> real_num2 >> imagin_num2;
            ComplexNum c2(real_num2, imagin_num2);
            
            // object 생성
            
            // 입력한 복소수 2개 출력
            cout << "첫번째 복소수: ";
            c1.show_complex_num();
            cout << "두번째 복소수: ";
            c2.show_complex_num();
            
            switch (input) {
                    
                case 1:
                    c1.plus(c2);
                    break;
                case 2:
                    c1.minus(c2);
                    break;
                case 3:
                    c1.multiply(c2);
                    break;
                case 4:
                    c1.divide(c2);
                    break;
                    
            }
            if (input == 4 && !c1.isDivided) {
                cout << "0으로 나눌 수 없습니다." << endl;
            }
            else{
                cout << "결과 = ";
                c1.show_complex_num(); // 사칙연산 수행 후 결과 출력
            }
            
        }
        else if (input == 5) {
            
            int array_size;
            cout << "배열의 크기를 입력하세요"<< endl;
            cin >> array_size;
            ComplexNum* complex_array = new ComplexNum[array_size];
            
            cout << "배열의 원소를 입력하세요" << endl;
            for ( int i = 0; i < array_size; i++ ){
                cout<< i+1 << "번째 복소수를 실수부 허수부 순으로 입력하세요: ";
                double input_real, input_imagin;
                cin >> input_real >> input_imagin;
                complex_array[i].setReal(input_real);
                complex_array[i].setImagin(input_imagin);
            }
            // 배열 원소 입력
            
            bubbleSort(complex_array, array_size); // Lab2 참고
            
            cout << endl << "정렬 후:  " << endl;
            for ( int i = 0; i < array_size; i++ ){
                cout<< i << "번째 복소수: ";
                complex_array[i].show_complex_num();
            }
            // 정렬 후 배열 출력
            
            delete []complex_array;

        }
        else if(input == 0)
            break;
        else
            cout << "잘못 입력하셨습니다." << endl;
        
    }

    return 0;
}

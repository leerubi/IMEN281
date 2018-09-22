//
//  complex.cpp
//  IMEN281
//
//  Created by ruby on 2017. 9. 19..
//  Copyright © 2017년 ruby. All rights reserved.
//

#include <stdio.h>
#include "complex.h"

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

void ComplexNum::plus(const ComplexNum &c2){
    
    real_num += c2.real_num;
    imagin_num += c2.imagin_num;
    
}
void ComplexNum::minus(const ComplexNum &c2){
    
    real_num -= c2.real_num;
    imagin_num -= c2.imagin_num;
    
}

void ComplexNum::multiply(const ComplexNum &c2){
    
    double real_temp = real_num;
    double imagin_temp = imagin_num;
    
    real_num = (real_temp)*(c2.real_num) - (imagin_temp)*(c2.imagin_num);
    imagin_num = (imagin_temp)*(c2.real_num) + (real_temp)*(c2.imagin_num);
    
}

void ComplexNum::divide(const ComplexNum &c2){
   
    if (c2.real_num == 0 || c2.imagin_num == 0) {
        isDivided = false;
        return;
    }
    
    double real_temp = real_num;
    double imagin_temp = imagin_num;
    
    real_num = ((real_temp)*(c2.real_num) + (imagin_temp)*(c2.imagin_num))
                /  ((c2.real_num)*(c2.real_num) + (c2.imagin_num)*(c2.imagin_num));
    imagin_num = ((imagin_temp)*(c2.real_num) - (real_temp)*(c2.imagin_num))
                /  ((c2.real_num)*(c2.real_num) + (c2.imagin_num)*(c2.imagin_num));
    isDivided = true;
    
}

bool ComplexNum::compare(const ComplexNum &c2){
    
    if (real_num > c2.real_num )
        return true;    //앞의 것이 크면 true 반환
    else
        return false;
    
}


void ComplexNum::show_complex_num(){
    
    cout<<real_num<<" ";
    
    if ( imagin_num >= 0 ) {
        cout<<"+ ";
    }
    
    cout<<imagin_num<<" i"<<endl;
    
}


void bubbleSort(ComplexNum *arr, int count){
    
    
    
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

bool is1234(int input){
    
    if ( (input == 1)||(input == 2)||(input == 3)||(input == 4) )
        return true;
    else
        return false;
    
}



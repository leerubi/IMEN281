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

void print_numbers(int * ptr, int num){
    
    for ( int i = 0; i < num; i++ ) {
        
        cout<<ptr[i]<<" ";
        
    }
    
    cout<<endl;
}

void BubbleSort(int * ptr, int num){

    
    for ( int j = num - 1; j > 0; j--) {
        
        for ( int i = 0; i < j; i++) {
            
            if ( ptr[i] > ptr[i+1] ) {
                
                int temp = ptr[i];
                ptr[i] = ptr[i+1];
                ptr[i+1] = temp;
                //Swap
    
            }
            
        }

    }
    
}

int main(int argc, const char * argv[]) {
    
    int count;
    while (true) {
        cout<<endl<<"Enter the number of elements (-1 for quit program): ";
        cin>>count;
        if (count == -1) {
            break;
        }
        int * numbers = new int[count];
        //array 생성
        
        cout<<"Enter "<<count<<" number with space"<<endl;
        for ( int i = 0; i < count; i++) {
            cin>>numbers[i];
        }
        //숫자 입력
        
        cout<<"Entered numbers are"<<endl;
        print_numbers(numbers, count);
        
        BubbleSort(numbers, count);
        cout<<"Sorted numbers are"<<endl;
        print_numbers(numbers, count);
        
        delete []numbers;
    }
    
    return 0;
}

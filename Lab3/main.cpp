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

void printResult(int * ptr, int num){
    
    cout<<"정렬된 배열"<<endl;
    for ( int i = 0; i < num; i++ ) {
        
        cout<<ptr[i]<<" ";
        
    }
    
    cout<<endl;
}

void bubble_sort(int * ptr, int num){

    
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

int binarySearch(int a[], int left, int right, int target){
    
    int index = -1;
    int mid = (left + right)/2;

    if (target == a[mid]) {
        
        index = mid;
        return index;
        
    }
    else if (target < a[mid]){
       
        if (mid == 0)
            return index;
        index = binarySearch(a, 0, mid - 1, target);

    }
    else if (target > a[mid]){
        
        if (mid == right)
            return index;
        index = binarySearch(a, mid + 1, right, target);
    }

    return index;
}

void searchIndex(int a[], int array_size, int found_index, int start_index, int end_index){
  
    int i = 1;
    while (true) {
        
        if (a[found_index] == a[found_index - i])
            start_index = found_index - i;
        else
            break;
        
        i++;
    }
    
    i = 1;
    while (true) {
        
        if (a[found_index] == a[found_index + i])
            end_index = found_index + i;
        else
            break;
        
        i++;
    }
    
    if ((found_index == 0) || start_index == found_index)
        cout<<"해당 원소는 배열의 "<<found_index+1<<"번째 원소입니다"<<endl;
    else
        cout<<"해당 원소는 배열의 "<<start_index+1<<"번째부터 "<<end_index+1<<"번째 원소입니다"<<endl;

    
}

int main(int argc, const char * argv[]) {
    
    int array_size;
    while (true) {

        cout<<"배열의 크기를 입력하세요(-1 = 종료)"<<endl;
        cin>>array_size;
        if (array_size == -1) {
            break;
        }
        int * arr = new int[array_size];
        //Array 생성
        
        cout<<"배열의 원소를 입력하세요"<<endl;
        for ( int i = 0; i < array_size; i++) {
            cin>>arr[i];
        }
        //원소 입력
        
        bubble_sort(arr, array_size);
        printResult(arr, array_size);
        //Array를 정렬하고 출력
        
        int target = 1;
        while (true) {
                
            cout<<endl<<"찾으려는 원소를 입력하세요(0 = 배열 재입력)"<<endl;
            cin>>target;
            
            if (target == 0) {  //0 = 배열 재입력
                break;
            }
            
            int found_index, start_index, end_index;
            found_index = binarySearch(arr, 0, array_size-1, target);
            start_index = found_index;
            end_index = found_index;
            
            if (found_index == -1)
                cout<<"해당 원소는 존재하지 않습니다"<<endl;
            else
                searchIndex(arr, array_size, found_index, start_index, end_index);
                // start_index와 end_index를 구함
        
        }
        
        delete []arr;
        
    }
    
    return 0;
}

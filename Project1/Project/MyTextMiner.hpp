//
//  MyTextMiner.hpp : 파일을 읽어서 단어로 구분하여 빈도수를 세고 내림차순으로 정렬하여 출력한다.
//  IMEN281_HW1
//
//  Created by ruby on 2017. 9. 28..
//  Copyright © 2017년 ruby. All rights reserved.
//

#ifndef MyTextMiner_hpp
#define MyTextMiner_hpp

//#include "stdafx.h"
#include <stdio.h>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <time.h>
#include <algorithm>
using namespace std;

class CWord {
    string word;
    int count;
public:
    string getWord() { return word; }
    int getCount() { return count; }
    void setWord(string _word) { word = _word;  }
    void setCount(int _count) { count = _count; }
    
    CWord(string _word, int _count = 1) {
        word = _word;
        count = _count;
    }
};

class CTextMine {
    vector <char> m_delimiter_list;                                  // 단어 구분자 리스트 (예: '.', ',')
    vector <CWord> m_my_word_list;                                   // 단어와 빈도수 저장
    long m_total_word_count;                                         // 전체 word 수를 갖는다 (반복되는 word를 중복 count)
public:
    long getTotalWordCount() { return m_total_word_count; }          // 전체 word 수를 return
    long getWordCount() { return (long)m_my_word_list.size(); }      // word의 종류 수를 return
    
    void read_delimiter_file(const char *filename);                  // 구분자 파일을 읽어서 m_delimiter_list에 넣는다
    void read_text_file_and_parse(const char *filename);             // 주어진 text 파일을 읽어서 m_my_word_list에 넣는다
    void sort_word_list();                                           // m_my_word_list 를 빈도수가 큰 순서로 sort한다
    void write_result(const char *filename);                         // 구해진 word summary를 출력한다
    void bubbleSort(vector<int> &indexList);                         // 구분자의 인덱스를 정렬하기 위한 버블 소트
};

#endif /* MyTextMiner_hpp */

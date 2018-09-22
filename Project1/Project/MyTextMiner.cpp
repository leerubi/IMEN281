//
//  MyTextMiner.cpp
//  IMEN281_HW1
//
//  Created by ruby on 2017. 9. 28..
//  Copyright © 2017년 ruby. All rights reserved.
//

#include "MyTextMiner.hpp"

void CTextMine::read_delimiter_file(const char *filename){
    ifstream fin(filename);
    if ( !fin.is_open() )
        throw -1;             // 파일 오픈 실패 시 프로그램 종료
    
    string _delimiter;
    while ( !fin.eof() ) {      // 파일의 끝에 도달할 때 까지
        getline(fin, _delimiter);                    // 파일의 문자를 하나씩 입력받는다
        m_delimiter_list.push_back(_delimiter[0]);   // 구분자를 m_delimiter_list에 저장한다
    }
    m_delimiter_list.push_back('\n');
}

void CTextMine::read_text_file_and_parse(const char *filename){
    ifstream fin(filename);
    if ( !fin.is_open() )
        throw -2;            // 파일 오픈 실패 시 프로그램 종료
    
    string tempLine;
    string _word;
    while ( !fin.eof() ) {      // 파일의 끝에 도달할 때 까지 파일의 텍스트를 '\r'로 구분하여 저장한다
        getline(fin, tempLine, '\r');
        if ( !(tempLine == "" || tempLine == "\r" || tempLine == "\n") ) {        // 개행 문자 처리를 위한 조건문
            vector<int> delimiterIndexList;                                                    // 구분자의 인덱스 컨테이너
            delimiterIndexList.push_back(-1);
            for (int i = 0; i < (int)m_delimiter_list.size(); i++) {              // 모든 구분자를 찾기 위한 반복문
                int tempIndex = -1;
                while (true) {
                    tempIndex = (int)tempLine.find(m_delimiter_list[i], tempIndex + 1);       // 저장된 문자열에서 찾은 구분자의 인덱스 반환
                    if ( tempIndex == -1)                                                     // 구분자를 못찾으면 다른 구분자를 찾기위해 탈출
                        break;
                    delimiterIndexList.push_back(tempIndex);                                  // 찾은 구분자의 인덱스를 저장
                }
            }
            bubbleSort(delimiterIndexList);                                                   // 인덱스를 오름차순으로 정렬
            for (int i = 0; i < (int)delimiterIndexList.size(); i++) {
                _word = tempLine.substr(delimiterIndexList[i]+1, delimiterIndexList[i+1]-delimiterIndexList[i]-1);    // 구분된 문자열을 추출
                if ( !(_word == "" || _word == "\r" || _word == "\n") ) {                                             // 개행 문자 처리를 위한 조건문
                    m_total_word_count++;                                         // 전체 단어 수 증가
                    bool isRepeated = false;
                    for (int i = 0; i < (int)m_my_word_list.size(); i++) {
                        if ( _word.compare(m_my_word_list[i].getWord()) == 0 ) {              // 반복되는 단어인지 확인하는 조건문
                            int count = m_my_word_list[i].getCount();
                            m_my_word_list[i].setCount(count + 1);                            // 반복되는 단어라면 해당 단어의 빈도수 증가
                            isRepeated = true;
                            break;
                        }
                    }
                    if ( !isRepeated )
                        m_my_word_list.push_back(CWord(_word));                              // 새로운 단어라면 CWord 객체를 생성함과 동시에 단어를 저장
                }
            }
        }
    }
    fin.close();
}

void CTextMine::sort_word_list(){
    for (int j = (int)m_my_word_list.size() - 1; j > 0; j--) {
        for (int i = 0; i < j; i++) {
            if (m_my_word_list[i].getCount() < m_my_word_list[i+1].getCount()) {                // 1. 단어의 빈도 수로 정렬
                CWord temp = m_my_word_list[i];
                m_my_word_list[i] = m_my_word_list[i+1];
                m_my_word_list[i+1] = temp;
            }
            else if (m_my_word_list[i].getCount() == m_my_word_list[i+1].getCount()){
                if (m_my_word_list[i].getWord().compare(m_my_word_list[i+1].getWord()) > 0) {   // 2. 단어 알파벳 순(가나다 순)으로 정렬
                    CWord temp = m_my_word_list[i];
                    m_my_word_list[i] = m_my_word_list[i+1];
                    m_my_word_list[i+1] = temp;
                }
            }
        }
    }
}

void CTextMine::write_result(const char *filename){
    ofstream fout(filename);
    if ( !fout.is_open() )
        throw -3;              // 파일 오픈 실패 시 프로그램 종료
    fout << "전체 word 수 (중복) = " << getTotalWordCount() << endl;
    fout << "전체 word 수 = " << getWordCount() << endl << endl;
    fout << "Word, count" << endl;
    for (int i = 0; i < getWordCount(); i++)
        fout << m_my_word_list[i].getWord() << ", " << m_my_word_list[i].getCount() << endl;
    fout.close();
}

void CTextMine::bubbleSort(vector<int> &indexList){
    int count = (int)indexList.size();
    for ( int j = count - 1; j > 0; j--) {
        for ( int i = 0; i < j; i++) {
            if ( indexList[i] > indexList[i+1] ) {
                int temp = indexList[i];
                indexList[i] = indexList[i+1];
                indexList[i+1] = temp;
            }
        }
    }
}

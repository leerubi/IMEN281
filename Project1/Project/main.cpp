//
//  main.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//  IMEN281_HW1
//
//  Created by ruby on 2017. 9. 28..
//  Copyright © 2017년 ruby. All rights reserved.
//

//#include "stdafx.hpp"     // Window에서 실행 시 주석을 해제하세요.
#include "MyTextMiner.hpp"

int main(int argc, const char *argv[])
{
    try {
        clock_t    clockA;
        double elaspsedTime;
        clockA = clock();           // 구동 시작 시각 저장

        if (argc != 4) {
            cout << "프로그램 구동 방법이 잘못되었습니다. *.exe input_text.txt delimiter.txt output.txt" << endl;
            throw - 1;
        }

        CTextMine my_text_miner;
        my_text_miner.read_delimiter_file(argv[2]);                   // 구분자 파일을 읽어서 m_delimiter_list에 넣는다
        my_text_miner.read_text_file_and_parse(argv[1]);              // 주어진 text 파일을 읽어서 m_my_word_list에 넣는다
        my_text_miner.sort_word_list();                               // m_my_word_list 를 빈도수가 큰 순서로 sort한다
        my_text_miner.write_result(argv[3]);                          // 구해진 word summary를 출력한다
        
        cout << "전체 word 수 (중복) = " << my_text_miner.getTotalWordCount() << endl;          // 중복 count된 word 수
        cout << "전체 word 수 = " << my_text_miner.getWordCount() << endl;                     // 중복 count되지 않은 word 수
        elaspsedTime = (double)(double)(clock() - clockA) / CLOCKS_PER_SEC / 1000.0;
        cout << "구동시간 = " <<fixed<< elaspsedTime << " milli seconds" << endl;
    }
    catch (int exception) {
        if (exception == -1)
            cout << "input 오류입니다" << endl;
        else if (exception == -2)
            cout << "delimiter.txt 파일을 열 수 없습니다" << endl;
        else if (exception == -3)
            cout << "input_text.txt 파일을 열 수 없습니다" << endl;
        else if (exception == -4)
            cout << "output.txt 파일을 열 수 없습니다" << endl;
    }
    catch (...) {
        cout << "구분되지 않은 예외입니다" << endl;
    }
    return 0;
}


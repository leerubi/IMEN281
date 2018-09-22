//
//  ex.hpp
//  lab18
//
//  Created by ruby on 2017. 11. 28..
//  Copyright © 2017년 ruby. All rights reserved.
//

#ifndef ex_hpp
#define ex_hpp

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stack>
#include <queue>

using namespace std;

class CPosition
{
public:
    int row, col;
    bool operator==(const CPosition &p1)
    {
        if (row == p1.row && col == p1.col)
            return true;
        else
            return false;
    }
    
};


class CMaze
{
public:
    int num_row, num_col;
    vector<vector<int>> maze;
    stack <CPosition> path_stack;
    
    CPosition start_position, end_position;
    
    int get_row_num()
    {
        return num_row;
    }
    int get_num_col()
    {
        return num_col;
    }
    
    bool read_MazeInput(string filename);
    void show_Maze();
    bool find_path();
    void extract_path();
    bool find_shortest_path();
    void show_shortest_path();
    
};


#endif /* ex_hpp */

//
//  main.cpp
//  lab18
//
//  Created by ruby on 2017. 11. 28..
//  Copyright © 2017년 ruby. All rights reserved.
//

#include <iostream>
#include "ex.hpp"

int main(int argc, const char * argv[]) {
    
    CMaze my_maze;
    
    try {
        string menu;
        bool maze_initialize = false;
        while (true) {
            cout << "Select menu r(read maze file), s(search), e(exit): ";
            cin >> menu;
            if (menu == "e")
                break;
            if (menu == "r") {
                cout << "file name(sample_maze.csv): ";
                string filename;
                cin >> filename;
                if (my_maze.read_MazeInput(filename) == true) {
                    my_maze.show_Maze();
                    maze_initialize = true;
                }
            }
            else if (menu == "s") {
                if (maze_initialize == true) {
                    cout << "Select sub menu s(stack), q(queue): ";
                    string option;
                    cin >> option;
                    cout << "Enter start_position_row: "; cin >> my_maze.start_position.row;
                    cout << "Enter start_position_col: "; cin >> my_maze.start_position.col;
                    cout << "Enter end_position_row: ";  cin >> my_maze.end_position.row;
                    cout << "Enter end_position_row: ";   cin >> my_maze.end_position.col;
                    if (option == "s") {
                        if (my_maze.find_path() == true) {
                            cout << "Succeed!" << endl;
                            my_maze.extract_path();
                        }
                        else
                            cout << "There is no feasible path!" << endl;
                        maze_initialize = false;
                    }
                    else if (option == "q") {
                        if (my_maze.find_shortest_path() == true) {
                            cout << "Succeed!" << endl;
                            my_maze.show_shortest_path();
                        }
                        else
                            cout << "There is no feasible path!" << endl;
                        maze_initialize = false;
                    }
                }
                else {
                    cout << "maze read first" << endl;
                }
            }
        }
    } catch (int ex) {
        if (ex == -1)
            return -1;
    } catch (...) {
        return -1;
    }
    return 0;
}

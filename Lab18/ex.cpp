//
//  ex.cpp
//  lab18
//
//  Created by ruby on 2017. 11. 28..
//  Copyright © 2017년 ruby. All rights reserved.
//

#include "ex.hpp"

int pathLength;
vector<CPosition> path;

bool CMaze::read_MazeInput(string filename)
{
    ifstream in(filename);
    string str, temp;
    maze.clear();
    
    if (in.is_open()) {
        getline(in, str, ',');
        getline(in, temp);
        num_row = stoi(temp);
        
        getline(in, str, ',');
        getline(in, temp);
        num_col = stoi(temp);
        
        for (int i = 0; i < num_row; i++) {
            vector<int> col_vector(num_col);
            for (int j = 0; j < num_col - 1; j++) {
                getline(in, temp, ',');
                col_vector[j] = stoi(temp);
            }
            getline(in, temp);
            col_vector[num_col - 1] = stoi(temp);
            maze.push_back(col_vector);
        }
        in.close();
    }
    else {
        cout << "cannot open " << filename << endl;
        return false;
    }
    return true;
}

void CMaze::show_Maze()
{
    for (int i = 0; i < num_row; i++) {
        for (int j = 0; j < num_col - 1; j++) {
            cout << maze[i][j] << " ";
        }
        cout << maze[i][num_col - 1] << endl;
    }
}

// for queue
bool CMaze::find_shortest_path()
{// Find a shortest path from start_position to end_position.
    // Return true if successful, false if impossible.
    
    if ((start_position.row == end_position.row) && (start_position.col == end_position.col))
    {// start_position == end_position
        pathLength = 0;
        return true;
    }
    
    // initialize offsets
    CPosition offset[4];
    offset[0].row = 0; offset[0].col = 1;   // right
    offset[1].row = 1; offset[1].col = 0;   // down
    offset[2].row = 0; offset[2].col = -1;  // left
    offset[3].row = -1; offset[3].col = 0;  // up
    
    CPosition here = start_position;
    maze[start_position.row][start_position.col] = 2; // block
    int numOfNbrs = 4; // neighbors of a grid position
    
    // label reachable grid positions
    queue <CPosition> q;
    CPosition nbr;
    
    
    do
    {// label neighbors of here
        for (int i = 0; i < numOfNbrs; i++)
        {// check out neighbors of here
            nbr.row = here.row + offset[i].row;
            nbr.col = here.col + offset[i].col;
            if (maze[nbr.row][nbr.col] == 0)
            {// unlabeled nbr, label it
                maze[nbr.row][nbr.col]
                = maze[here.row][here.col] + 1;
                if ((nbr.row == end_position.row) &&
                    (nbr.col == end_position.col)) break; // done
                // put on queue for later expansion
                q.push(nbr);
            }
        }
        
        // have we reached end_position?
        if ((nbr.row == end_position.row) &&
            (nbr.col == end_position.col)) break;     // done
        
        // end_position not reached, can we move to a nbr?
        if (q.empty())
            return false;          // no path
        here = q.front();         // get next position
        q.pop();
    } while (true);
    
    
    // construct path
    pathLength = maze[end_position.row][end_position.col] - 2;
    path.resize(pathLength);
    
    // trace backwards from end_position
    here = end_position;
    for (int j = pathLength - 1; j >= 0; j--)
    {
        path[j] = here;
        // find predecessor position
        for (int i = 0; i < numOfNbrs; i++)
        {
            nbr.row = here.row + offset[i].row;
            nbr.col = here.col + offset[i].col;
            if (maze[nbr.row][nbr.col] == j + 2) break;
        }
        here = nbr;  // move to predecessor
    }
    
    return true;
}

// queue
void CMaze::show_shortest_path()
{
    cout << "(" << start_position.row << "," << start_position.col << ") --> ";
    int count = 1;
    for (int i = 0; i<(int)path.size(); i++)
    {
        if (i < (int)path.size() - 1)
            cout << "(" << path[i].row << "," << path[i].col << ") --> ";
        else
            cout << "(" << path[i].row << "," << path[i].col << ") ";
        count++;
        if (count % 7 == 0)
            cout << endl;
    }
    cout << endl;
}

// stack
bool CMaze::find_path()
{// Find a shortest path from start_position to end_position.
    // Return true if successful, false if impossible.
    
    if ((start_position.row == end_position.row) && (start_position.col == end_position.col))
    {// start_position == end_position
        pathLength = 0;
        return true;
    }
    
    // initialize offsets
    CPosition offset[4];
    offset[0].row = 0; offset[0].col = 1;   // right
    offset[1].row = 1; offset[1].col = 0;   // down
    offset[2].row = 0; offset[2].col = -1;  // left
    offset[3].row = -1; offset[3].col = 0;  // up
    
    CPosition here = start_position;
    maze[start_position.row][start_position.col] = 2; // block
    int numOfNbrs = 4; // neighbors of a grid position
    
    // label reachable grid positions
    stack <CPosition> s;
//    queue <CPosition> q;
    CPosition nbr;
    
    
    do
    {// label neighbors of here
        for (int i = 0; i < numOfNbrs; i++)
        {// check out neighbors of here
            nbr.row = here.row + offset[i].row;
            nbr.col = here.col + offset[i].col;
            if (maze[nbr.row][nbr.col] == 0)
            {// unlabeled nbr, label it
                maze[nbr.row][nbr.col]
                = maze[here.row][here.col] + 1;
                if ((nbr.row == end_position.row) &&
                    (nbr.col == end_position.col)) break; // done
                // put on queue for later expansion
                s.push(nbr);
            }
        }
        
        // have we reached end_position?
        if ((nbr.row == end_position.row) &&
            (nbr.col == end_position.col)) break;     // done
        
        // end_position not reached, can we move to a nbr?
        if (s.empty())
            return false;          // no path
        here = s.top();
//        here = s.front();         // get next position
        s.pop();
    } while (true);
    
    
    // construct path
    pathLength = maze[end_position.row][end_position.col] - 2;
    path.resize(pathLength);
    
    // trace backwards from end_position
    here = end_position;
    for (int j = pathLength - 1; j >= 0; j--)
    {
        path[j] = here;
        // find predecessor position
        for (int i = 0; i < numOfNbrs; i++)
        {
            nbr.row = here.row + offset[i].row;
            nbr.col = here.col + offset[i].col;
            if (maze[nbr.row][nbr.col] == j + 2) break;
        }
        here = nbr;  // move to predecessor
    }
    
    return true;
}
// stack
void CMaze::extract_path()
{
    cout << "(" << start_position.row << "," << start_position.col << ") --> ";
    int count = 1;
    for (int i = 0; i<(int)path.size(); i++)
    {
        if (i < (int)path.size() - 1)
            cout << "(" << path[i].row << "," << path[i].col << ") --> ";
        else
            cout << "(" << path[i].row << "," << path[i].col << ") ";
        count++;
        if (count % 7 == 0)
            cout << endl;
    }
    cout << endl;
}


//
//  main.cpp
//  Lab16
//
//  Created by ruby on 2017. 11. 14..
//  Copyright © 2017년 ruby. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Item {
public:
    int id;
    int w;
    int p;
    Item(int _id, int _w, int _p) : id(_id), w(_w), p(_p) {}
};

class Myknabsack {
public:
    // members
    vector<Item> items;
    int capacity;
    int maxProfit;
    vector<int> solution;   // for iterative, recursive
    vector<int> weight;     // for iterative
    vector<int> trial;      // for recursive
    
    //methods
    void solve_iterative() {
        solution.resize(items.size());
        for (int i = 0; i < items.size() - 1; i++)
            weight.push_back(items[i].w);
        
        vector< vector<int> > matrix(items.size(), vector<int>(capacity+1,0));
        // initialize
        int n = (int)items.size() - 1;
        int yMax = min(weight[n] - 1, capacity);
        for (int y = 0; y <= yMax; y++)
            matrix[n][y] = 0;
        for (int y = items[n].w; y <= capacity; y++)
            matrix[n][y] = items[n].p;
        // compute maxProfit, 0 <= i < n
        for (int i = n-1; i > 0; i--){
            yMax = min(weight[i] - 1, capacity);
            for (int y = 0; y <= yMax; y++)
                matrix[i][y] = matrix[i + 1][y];
            
            for (int y = items[i].w; y <= capacity; y++)
                matrix[i][y] = max(matrix[i + 1][y], matrix[i + 1][y - items[i].w] + items[i].p);
        }
        // compute f[0][c]
        matrix[0][capacity] = matrix[1][capacity];
        if (capacity >= items[0].w)
            matrix[0][capacity] = max(matrix[0][capacity], matrix[1][capacity-items[0].w] + items[0].p);
        // traceback
        int cap = capacity;
        for (int i = 0; i < n; i++) {
            if (matrix[i][cap] == matrix[i+1][cap])
                solution[i] = 0;
            else {
                solution[i] = 1;
                cap = cap - weight[i];
            }
        }
        solution[n] = (matrix[n][cap] > 0) ? 1 : 0;
        maxProfit = matrix[0][capacity];
    }
    
    void solve_recursive(int j = -1, int w = 0, int p = 0) {
        solution.resize(items.size());
        trial.resize(items.size());
        if(puttable(capacity, w)) {
            if (j == items.size()-1) {
                if (p > maxProfit) {
                    maxProfit = p;
                    for (int i = 0; i < items.size(); i++)
                        solution[i] = trial[i];
                }
            }
            else {
                trial[j+1] = 1;
                solve_recursive(j+1, w+items[j+1].w, p+items[j+1].p);
                trial[j+1] = 0;
                solve_recursive(j+1, w, p);
            }
        }
    }
    bool puttable(int capacity, int weight) {
        if (weight <= capacity)
            return true;
        else
            return false;
    }
    void readInputfile(string filename, int c) {
        ifstream fin(filename);
        if (!fin.is_open())
            throw -1;
        string dummy;
        getline(fin, dummy);
        // set w, p
        string _id, _w, _p;
        int id, w, p;
        while (!fin.eof()) {
            getline(fin, _id, ',');
            if (_id == "\n")
                break;
            getline(fin, _w, ',');
            getline(fin, _p, '\r');
            id = stoi(_id);
            w = stoi(_w);
            p = stoi(_p);
            items.push_back(Item(id, w, p));
        }
        fin.close();
        // set capacity
        capacity = c;
    }
    void printResult() {
        vector<int> result;
        for (int i = 0; i < solution.size(); i++) {
            if (solution[i] == 1)
                result.push_back(items[i].id);
        }
        
        cout << "Optimal Solution = {";
        for (int i = 0; i < result.size()-1; i++) {
            cout << result[i] << ", ";
        }
        cout << result[result.size()-1] << "}" << endl;
        cout << "Optimal Objective Value = " << maxProfit << endl;
    }
};
int main(int argc, const char * argv[]) {
    int capacity = stoi(argv[2]);
    Myknabsack myknapsack;
    try {
        myknapsack.readInputfile(argv[1], capacity);
        myknapsack.solve_iterative();
//        myknapsack.solve_recursive();
        myknapsack.printResult();
    } catch (int exception) {
        cout << "can not open the file" << endl;
        return -1;
    }
    
    
    return 0;
}

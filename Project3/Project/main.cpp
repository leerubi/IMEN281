//
//  main.cpp
//  HW3
//
//  Created by ruby on 2017. 12. 4..
//  Copyright © 2017년 ruby. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <ctime>
using namespace std;

class Item {
public:
    int id; // id of the item
    int w;  // weight of the item
    int p;  // profit of the item
    Item(int _id, int _w) : id(_id), w(_w) {}                   // constructor
    Item(int _id, int _w, int _p) : id(_id), w(_w), p(_p) {}    // constructor for knapsack algorithm
    bool operator >(const Item &a) const {                      // operator overloading
        return this->w > a.w;
    }
};

class Truck {
public:
    vector<Item> innerItems;    // inner items of the truck
    int c;                      // capacity of the truck
    Truck(int _c) : c(_c) {}    // constructor
    bool operator <(const Truck &a) const {     // operator overloading
        return this->c < a.c;
    }
};

class BinPacking {
public:
    // members
    vector<Item> items;
    vector<Truck> trucks;
    int capacity;
    string inputfileName;
    string outputfileName;
    string algorithmName;
    
    // method reaing input file
    void readInputfile(string inputfile, string outputfile, int c) {
        ifstream fin(inputfile);
        if (!fin.is_open())
            throw -1;
        inputfileName = inputfile;
        outputfileName = outputfile;
        string dummy;
        getline(fin, dummy);
        // set id, weight
        string _id, _w;
        int id, w;
        while (!fin.eof()) {
            getline(fin, _id, '\t');
            if (_id == "")  // for mac?
                break;
            getline(fin, _w, '\n');
            id = stoi(_id);
            w = stoi(_w);
            items.push_back(Item(id, w));
        }
        fin.close();
        // set capacity
        capacity = c;
    }
    
    // method writing solution file
    void writeSolutionfile(string filename, double runTime) {
        ofstream fout(filename);
        if (!fout.is_open())
            throw -1;
        fout << "Input file 명 = " << inputfileName << ", ";
        fout << "Bin 용량 = " << capacity << ", ";
        fout << "Algorithm Type = " << algorithmName << ", ";
        fout << "Bin 수 = " << trucks.size() << ", ";
        fout << "계산시간 = " << runTime << "ms" << endl;

        for (int i = 0; i < trucks.size(); i++) {
            fout << "Bin #" << i+1 << ": " << trucks[i].innerItems.size() << ", " << capacity - trucks[i].c << endl;
            for (int j = 0; j < trucks[i].innerItems.size(); j++) {
                fout << trucks[i].innerItems[j].id << ", " << trucks[i].innerItems[j].w << endl;
            }
        }
    }
    
    // algorithms
    void firstFit() {
        algorithmName = "First Fit";
        clock_t start = clock();    // start time
        vector<Item>::iterator i = items.begin();
        while (true) {  // pop the items whose weight is greater than the capacity of a truck
            if (i->w > capacity)
                items.erase(i);
            else
                i++;
            if (i == items.end())
                break;
        }
        if (items.size() == 0) throw 'e';   // if there are no item that is not greater than capacity, throw 'e'.
        trucks.push_back(Truck(capacity));
        for (int i = 0; i < items.size(); i++) {
            for (int j = 0; j < trucks.size(); j++) {
                if (trucks[j].c >= items[i].w) {    // if the weight of current item is not greater than rest capacity, put into the truck and adjust the rest capacity.
                    trucks[j].innerItems.push_back(items[i]);
                    trucks[j].c -= items[i].w;
                    break;
                }
                if (j == trucks.size()-1 && capacity >= items[i].w) {   // if new truck is required and the weight of current item is not greater than the capacity of new truck, put into the truck and adjust the rest capacity.
                    trucks.push_back(Truck(capacity));
                    trucks[j+1].innerItems.push_back(items[i]);
                    trucks[j+1].c -= items[i].w;
                    break;
                }
            }
        }
        double runTime = (double)(clock() - start);
        // write the result
        writeSolutionfile(outputfileName, runTime);
    }
    
    void firstFitDecreasing() {
        algorithmName = "First Fit Decreasing";
        clock_t start = clock();    // start time
        vector<Item>::iterator i = items.begin();
        while (true) {  // pop the items whose weight is greater than the capacity of a truck
            if (i->w > capacity)
                items.erase(i);
            else
                i++;
            if (i == items.end())
                break;
        }
        if (items.size() == 0) throw 'e';   // if there are no item that is not greater than capacity, throw 'e'.
        sort(items.begin(), items.end(), greater<Item>());  // sort the items by weight in decreasing order
        trucks.push_back(Truck(capacity));
        for (int i = 0; i < items.size(); i++) {
            for (int j = 0; j < trucks.size(); j++) {
                if (trucks[j].c >= items[i].w) {    // if the weight of current item is not greater than rest capacity, put into the truck and adjust the rest capacity.
                    trucks[j].innerItems.push_back(items[i]);
                    trucks[j].c -= items[i].w;
                    break;
                }
                if (j == trucks.size()-1 && capacity >= items[i].w) {   // if new truck is required and the weight of current item is not greater than the capacity of new truck, put into the truck and adjust the rest capacity.
                    trucks.push_back(Truck(capacity));
                    trucks[j+1].innerItems.push_back(items[i]);
                    trucks[j+1].c -= items[i].w;
                    break;
                }
            }
        }
        double runTime = (double)(clock() - start);
        // write the result
        writeSolutionfile(outputfileName, runTime);
    }
    
    void bestFit() {
        algorithmName = "Best Fit";
        clock_t start = clock();    // start time
        vector<Item>::iterator i = items.begin();
        while (true) {  // pop the items whose weight is greater than the capacity of a truck
            if (i->w > capacity)
                items.erase(i);
            else
                i++;
            if (i == items.end())
                break;
        }
        if (items.size() == 0) throw 'e';   // if there are no item that is not greater than capacity, throw 'e'.
        trucks.push_back(Truck(capacity));
        for (int i = 0; i < items.size(); i++) {
            sort(trucks.begin(), trucks.end());     // sort the trucks by rest capacity in increasing order
            for (int j = 0; j < trucks.size(); j++) {
                if (trucks[j].c >= items[i].w) {    // if the weight of current item is not greater than rest capacity, put into the truck and adjust the rest capacity.
                    trucks[j].innerItems.push_back(items[i]);
                    trucks[j].c -= items[i].w;
                    break;
                }
                if (j == trucks.size()-1 && capacity >= items[i].w) {   // if new truck is required and the weight of current item is not greater than the capacity of new truck, put into the truck and adjust the rest capacity.
                    trucks.push_back(Truck(capacity));
                    trucks[j+1].innerItems.push_back(items[i]);
                    trucks[j+1].c -= items[i].w;
                    break;
                }
            }
        }
        double runTime = (double)(clock() - start);
        // write the result
        writeSolutionfile(outputfileName, runTime);
    }
    
    void bestFitDecreasing() {
        algorithmName = "Best Fit Decreasing";
        clock_t start = clock();    // start time
        vector<Item>::iterator i = items.begin();
        while (true) {  // pop the items whose weight is greater than the capacity of a truck
            if (i->w > capacity)
                items.erase(i);
            else
                i++;
            if (i == items.end())
                break;
        }
        if (items.size() == 0) throw 'e';   // if there are no item that is not greater than capacity, throw 'e'.
        sort(items.begin(), items.end(), greater<Item>());  // sort the items by weight in decreasing order
        trucks.push_back(Truck(capacity));
        for (int i = 0; i < items.size(); i++) {
            sort(trucks.begin(), trucks.end());     // sort the trucks by rest capacity in increasing order
            for (int j = 0; j < trucks.size(); j++) {
                if (trucks[j].c >= items[i].w) {    // if the weight of current item is not greater than rest capacity, put into the truck and adjust the rest capacity.
                    trucks[j].innerItems.push_back(items[i]);
                    trucks[j].c -= items[i].w;
                    break;
                }
                if (j == trucks.size()-1 && capacity >= items[i].w) {   // if new truck is required and the weight of current item is not greater than the capacity of new truck, put into the truck and adjust the rest capacity.
                    trucks.push_back(Truck(capacity));
                    trucks[j+1].innerItems.push_back(items[i]);
                    trucks[j+1].c -= items[i].w;
                    break;
                }
            }
        }
        double runTime = (double)(clock() - start);
        // write the result
        writeSolutionfile(outputfileName, runTime);
    }

    void firstFitDecreasing_lastTwoFit() {
        algorithmName = "First Fit Decreasing, Last Two Fit";
        clock_t start = clock();    // start time
        vector<Item>::iterator i = items.begin();
        while (true) {  // pop the items whose weight is greater than the capacity of a truck
            if (i->w > capacity)
                items.erase(i);
            else
                i++;
            if (i == items.end())
                break;
        }
        if (items.size() == 0) throw 'e';   // if there are no item that is not greater than capacity, throw 'e'.
        sort(items.begin(), items.end(), greater<Item>());  // sort the items by weight in decreasing order
        trucks.push_back(Truck(capacity));
        //i--;    // for check i-th item agin after check this pair
        vector<Item>::iterator iter = items.begin();
        while (true) {
            if (items.size() > 2 && iter->w < (items[items.size()-1].w + items[items.size()-2].w)) { // if a pair of last two items select a pair can be packed and they occupy more than i-th item, put the pair into a truck
                for (int j = 0; j < trucks.size(); j++) {
                    if (trucks[j].c >= (items[items.size()-1].w + items[items.size()-2].w)) {
                        trucks[j].innerItems.push_back(items[items.size()-1]);
                        trucks[j].c -= items[items.size()-1].w;
                        trucks[j].innerItems.push_back(items[items.size()-2]);
                        trucks[j].c -= items[items.size()-2].w;
                        items.pop_back();
                        items.pop_back();
                        break;
                    }
                    if (j == trucks.size()-1 && capacity >= (items[items.size()-1].w + items[items.size()-2].w)) {   // if new truck is required and the weight of current item is not greater than the capacity of new truck, put into the truck and adjust the rest capacity.
                        trucks.push_back(Truck(capacity));
                        trucks[j+1].innerItems.push_back(items[items.size()-1]);
                        trucks[j+1].c -= items[items.size()-1].w;
                        trucks[j+1].innerItems.push_back(items[items.size()-2]);
                        trucks[j+1].c -= items[items.size()-2].w;
                        items.pop_back();
                        items.pop_back();
                        break;
                    }
                }
            }
            else {
                for (int j = 0; j < trucks.size(); j++) {
                    if (trucks[j].c >= iter->w) {    // if the weight of current item is not greater than rest capacity, put into the truck and adjust the rest capacity.
                        trucks[j].innerItems.push_back(*iter);
                        trucks[j].c -= iter->w;
                        items.erase(iter);
                        break;
                    }
                    if (j == trucks.size()-1 && capacity >= iter->w) {   // if new truck is required and the weight of current item is not greater than the capacity of new truck, put into the truck and adjust the rest capacity.
                        trucks.push_back(Truck(capacity));
                        trucks[j+1].innerItems.push_back(*iter);
                        trucks[j+1].c -= iter->w;
                        items.erase(iter);
                        break;
                    }
                }
            }
            if (iter == items.end())
                break;
        }
        double runTime = (double)(clock() - start);
        // write the result
        writeSolutionfile(outputfileName, runTime);
    }

};

class Myknabsack {
public:
    // members
    vector<Item> items;
    int capacity;
    vector<Truck> trucks;
    vector<int> weight;
    string inputfileName;
    string outputfileName;
    string algorithmName;
    
    //methods
    void solve_iterative() {
        algorithmName = "Iterative Knapsack Algorithm";
        clock_t start = clock();    // start time
        vector<Item>::iterator i = items.begin();
        while (true) {  // pop the items whose weight is greater than the capacity of a truck
            if (i->w > capacity)
                items.erase(i);
            else
                i++;
            if (i == items.end())
                break;
        }
        if (items.size() == 0) throw 'e';   // if there are no item that is not greater than capacity, throw 'e'.
        while (true) {  // if items are remain, put items into a new truck
            vector<Item>::iterator iter = items.begin();
            trucks.push_back(Truck(capacity));
            for (int i = 0; i < items.size()-1; i++)
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
                    iter++;
                else {
                    trucks.back().innerItems.push_back(*iter);    // put the item into the truck
                    trucks.back().c -= iter->w;     // adjust capacity of the truck
                    cap = cap - weight[i];
                    items.erase(iter);  // erase the item in a truck from items
                }
            }
            if (matrix[n][cap] > 0) {
                trucks.back().innerItems.push_back(Item(iter->id, iter->w));    // put the item into the truck
                trucks.back().c -= iter->w;     // adjust capacity of the truck
                cap = cap - iter->w;
                items.erase(iter);  // erase the item in a truck from items
            }
            for (int i = 0; weight.size(); i++) {
                weight.pop_back();
            }
            if (iter == items.end())
                break;
        }
        double runTime = (double)(clock() - start);
        // write the result
        writeSolutionfile(outputfileName, runTime);
    }

    // method reaing input file
    void readInputfile(string inputfile, string outputfile, int c) {
        ifstream fin(inputfile);
        if (!fin.is_open())
            throw -1;
        inputfileName = inputfile;
        outputfileName = outputfile;
        string dummy;
        getline(fin, dummy);
        // set id, weight, profit
        string _id, _w;
        int id, w;
        while (!fin.eof()) {
            getline(fin, _id, '\t');
            if (_id == "")  // for mac?
                break;
            getline(fin, _w, '\n');
            id = stoi(_id);
            w = stoi(_w);
            items.push_back(Item(id, w, w));
        }
        fin.close();
        // set capacity
        capacity = c;
    }
    
    // method writing solution file
    void writeSolutionfile(string filename, double runTime) {
        ofstream fout(filename);
        if (!fout.is_open())
            throw -1;
        fout << "Input file 명 = " << inputfileName << ", ";
        fout << "Bin 용량 = " << capacity << ", ";
        fout << "Algorithm Type = " << algorithmName << ", ";
        fout << "Bin 수 = " << trucks.size() << ", ";
        fout << "계산시간 = " << runTime << "ms" << endl;
        
        for (int i = 0; i < trucks.size(); i++) {
            fout << "Bin #" << i+1 << ": " << trucks[i].innerItems.size() << ", " << capacity - trucks[i].c << endl;
            for (int j = 0; j < trucks[i].innerItems.size(); j++) {
                fout << trucks[i].innerItems[j].id << ", " << trucks[i].innerItems[j].w << endl;
            }
        }
    }
};

int main(int argc, const char * argv[]) {
    if (argc != 5) {
        cout << "Please input in the following format." << endl;
        cout << "<item file name> <Bin size> <algorithm_type: 1 = FF, 2 = BF, 3 = FFD, 4 = BFD, 5 = Knapsack, 6 = FFD-L2F> <solution file name>" << endl;
        return -1;
    }
    try {
        int capacity = stoi(argv[2]);
        int type = stoi(argv[3]);
        switch (type) {
            case 1: {
                BinPacking b1;
                b1.readInputfile(argv[1], argv[4], capacity);
                b1.firstFit();
                break;
            }
            case 2: {
                BinPacking b2;
                b2.readInputfile(argv[1], argv[4], capacity);
                b2.bestFit();
                break;
            }
            case 3: {
                BinPacking b3;
                b3.readInputfile(argv[1], argv[4], capacity);
                b3.firstFitDecreasing();
                break;
            }
            case 4: {
                BinPacking b4;
                b4.readInputfile(argv[1], argv[4], capacity);
                b4.bestFitDecreasing();
                break;
            }
            case 5: {
                Myknabsack myknapsack;
                myknapsack.readInputfile(argv[1], argv[4], capacity);
                myknapsack.solve_iterative();
                break;
            }
            case 6: {
                BinPacking b6;
                b6.readInputfile(argv[1], argv[4], capacity);
                b6.firstFitDecreasing_lastTwoFit();
                break;
            }
            default: {
                cout << "Please enter 1 ~ 6 as argv[5]." << endl;
                break;
            }
        }
    } catch (int exception) {
        cout << "can not open reading file." << endl;
        return -1;
    } catch (char exception) {
        cout << "all items' weight is greater than the capacity." << endl;
        return -1;
    }
    return 0;
}

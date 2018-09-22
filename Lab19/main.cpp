//
//  main.cpp
//  lab19
//
//  Created by ruby on 2017. 12. 1..
//  Copyright © 2017년 ruby. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <ctime>

using namespace std;
typedef unordered_map<string, string>Mymap;

class Person
{
public:
    string name;
    string number;
    
    Person(string _name = "0", string _number = "0") :name(_name), number(_number) {}
};

int main(int argc, const char * argv[]) {
    ifstream myfile;
    string name;
    string number;
    string line;
    string filename;
    vector <Person> list;
    Mymap map;
    clock_t clockA, clockB;
    bool check = false;
    bool check1 = false;
    char menu = 'a';
    Mymap::iterator pos;
    while (!(menu == 'E'))
    {
        cout << "메뉴입력(R : read file, S : search, E : exit)" << endl;
        cin >> menu;
        if (menu == 'R')
        {
            if (check1 == true)
            {
                cout << "이미 파일을 읽었습니다." << endl;
                continue;
            }
            check = true;
            cout << "파일 이름을 입력: ";
            cin >> filename;
            
            myfile.open(filename);
            getline(myfile, line);
            while (!(myfile.eof()))
            {
                getline(myfile, line, ',');
                name = line;
                getline(myfile, line);
                number = line;
                list.push_back(Person(name, number));
                map.insert(Mymap::value_type(name, number));
            }
        }
        else if (menu == 'S')
        {
            if (check == false)
            {
                cout << "파일 먼저 읽어주세요." << endl;
            }
            else
            {
                cout << "이름을 입력하세요" << endl;
                cin >> name;
                clockA = clock();
                int i;
                for (i = 0; i < list.size(); i++)
                {
                    if (list[i].name == name)
                    {
                        cout << "Linear list 검색결과 : " << endl;
                        cout << list[i].name << " " << list[i].number << endl;
                        cout << clock() - clockA << endl;
                        break;
                    }
                }
                if (i == list.size())
                    cout << name << " is not in the list" << endl;
                else
                {
                    cout << "Unordered_map list 검색결과 : " << endl;
                    clockB = clock();
                    for (pos = map.begin(); pos != map.end(); pos++)
                    {
                        pos = map.find(name);
                        cout << pos->first << " " << pos->second << endl;
                        cout << clock() - clockB << endl;
                        break;
                    }
                }
            }
        }
        else if (menu == 'E')
        {
            break;
        }
        else continue;
    }
    return 0;
}

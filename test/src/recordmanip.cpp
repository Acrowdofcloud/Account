#include "recordmanip.h"
#include "getdate.h"
#include "class.h"
#include "database.h"
#include "global.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>


using namespace std;

void separation(int len){
    for (int i = 0; i < len; i++){
        cout << "*";
    }
    cout << endl;
}

void show10(){
    int num_of_line = getNumofRecords(getmonth() + ".txt");
    ifstream fin(getmonth() + ".txt");
    string line;
    int current_line_num{1};
    if (num_of_line > 10) {
        current_line_num = num_of_line - 10 + 1 ;
        int i{1};
        while (i < current_line_num) {
            getline(fin,line);
            i++;
        }
    }
    separation(105);
    for (;current_line_num <= num_of_line; current_line_num++) {
        if (getline(fin,line)) {
            cout << current_line_num << ". " << line << endl;
        }
    }
    separation(105);
    fin.close();
}


#include "recordmanip.h"
#include "getdate.h"
#include "test.h"
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


void editrecord(record& records){
    int editcom = 9;
    while (editcom != 0){
        cout << "What to change?\n";
        cout << "0. return\n";
        cout << "1. date   2. Account   3. type   4. usage   5. amount   6. Notes\n";
        cin >> editcom;
        if (editcom == 1){
            cout << "Newdate? Leave blank to set as today\n";
            cin.ignore();
            records.input("date");
        }
        if (editcom == 2){
            int account;
            if (records.getType() == "R"){
                cout << "1. Cash   2. Bank\n";
                cin >> account;
                if (account == 1){
                    records.setAccount("Cash");
                }
                else{
                    records.setAccount("Bank");
                }
            }
            else{
                cout << "1. Cash   2. Bank   3. Credit_Card\n";
                cin >> account;
                if (account == 1){
                    records.setAccount("Cash");
                }
                else if (account == 2){
                    records.setAccount("Bank");
                }
                else{
                    records.setAccount("Credit_Card");
                }
            }

        }
        if (editcom == 3){
            if (records.getType() == "E"){
                records.setType("R");
            }
            else{
                records.setType("E");
            }
            cout << "Type changed\n";
        }
        if (editcom == 4){
            int type;
            if (records.getType() == "E"){
                cout << "1. Entertainment   2. Transport   3. Food   4. Bill   5. Others\n";
                cin >> type;
                if (type == 1){
                    records.setUsage("Entertainment");
                }
                if (type == 2){
                    records.setUsage("Transport");
                }
                if (type == 3){
                    records.setUsage("Food");
                }
                if (type == 4){
                    records.setUsage("Bill");
                }
                if (type == 5){
                    records.setUsage("Others");
                }
            }
            else{
                int type;
                cout << "1. Salary   2. others\n";
                cin >> type;
                if (type == 1){
                    records.setUsage("Salary");
                }
                if (type == 2){
                    records.setUsage("Others");
                }
            }
        }
        if (editcom == 5){
            cout << "New amount?   ";
            cin.ignore();
            records.input("amount");
        }
        if (editcom == 6){
            cout << "New Notes:   ";
            cin.ignore();
            string tempnote;
            getline(cin, tempnote);
            records.setNote(tempnote);
        }
    }
}

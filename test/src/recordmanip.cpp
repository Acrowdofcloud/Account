#include <iostream>
#include "recordmanip.h"
#include <string>
#include "test.h"
#include <fstream>
#include "getdate.h"

using namespace std;

void separation(int len){
    for (int i = 0; i < len; i++){
        cout << "*";
    }
    cout << endl;
}

void show10(){
    string arr[10] = {};
    int index{0};
    ifstream fin;
    string line;
    fin.open(getmonth() + ".txt");
    while (getline(fin, line)){
        if(line != ""){
            if (index != 10){
                arr[index] = line;
                index++;
            }
            else{
                for (int i = 0; i < 9; i++){
                    arr[i] = arr[i+1];
                }
                arr[9] = line;
            }
        }
    }
    fin.close();
    separation(105);
    printf("Recent records:\n");
    index = 1;
    for (int i = 9; i >= 0; i--){
        if (arr[i] != ""){
            if (to_string(index).length() == 1){
                printf("%d.  ",index);
            }
            else{
                printf("%d. ", index);
            }
            cout << arr[i] << endl;
            index++;
        }
    }
    separation(105);
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
            if (records.getType() == 'R'){
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
            if (records.getType() == 'E'){
                records.setType('R');
            }
            else{
                records.setType('E');
            }
            cout << "Type changed\n";
        }
        if (editcom == 4){
            int type;
            if (records.getType() == 'E'){
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
            if (tempnote == ""){
                tempnote = "N";
            }
            records.setNote(tempnote);
        }
    }
}

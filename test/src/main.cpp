#include <iostream>
#include <iomanip>
#include <string>
#include "test.h"
#include "getdate.h"

using namespace std;

void editrecord(record&);

int main() {
    record entry;
    entry.type = 'E';
    entry.setAccount("Visa card 1234");
    cout << "Input a new record:\n\n";
    cout << "Date: (YYYYMMDD,Leave blank to set as today)\n";
    entry.input("date");

    cout << "Amount: \n";
    entry.input("amount");

    cout << "Usage: \n";
    entry.input("usage");

    cout << "Note: \n";
    entry.input("note");

    cout << entry.getDate() << endl;
    cout << fixed << setprecision(2) << entry.getAmount() << endl;
    cout << entry.getAccount() << endl;
    cout << entry.getUsage() << endl;
    cout << entry.getNote() << endl;
    cout << endl;

    editrecord(entry);
    cout << "Edited record:\n" << entry.toString();
    return 0;
}

void editrecord(record& records){
    int editcom = 9;
    records.type = 'E';
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
            if (records.type == 'R'){
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
            if (records.type == 'E'){
                records.type = 'R';
            }
            else{
                records.type = 'E';
            }
            cout << "Type changed\n";
        }
        if (editcom == 4){
            int type;
            if (records.type == 'E'){
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

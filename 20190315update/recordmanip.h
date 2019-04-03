#include <iostream>
using namespace std;
string tempnote;

void deleterecord(struct record &records){
    records.exist = false;
    cout << "***************************************************************************\n";
    cout << "Record deleted\n";
    cout << "***************************************************************************\n";

}


void printallrecords(struct record records[]){
    int index = 1;
    cout << "***************************************************************************\n";
    for (int i = 0; i <20000; i++){
        if (records[i].exist == true){
            cout << index << ".\t";
            cout << setw(8) << records[i].date << " ";
            cout << setw(12) << records[i].account << " ";
            cout << setw(2) << records[i].type;
            cout << setw(20) << records[i].usage;
            cout << setw(8) << setprecision(6) << records[i].amount;
            cout << "\t\t" << records[i].notes << endl;
            index++;
        }
    }
    cout << "\n";
}
void printsinglerecord(struct record records){
    cout << "***************************************************************************\n";
    cout << setw(8) << records.date << " ";
    cout << setw(12) << records.account << " ";
    cout << setw(2) << records.type;
    cout << setw(20) << records.usage;
    cout << setw(8) << setprecision(6) << records.amount;
    cout << "\t\t" << records.notes << endl;
    cout << "*******************************************************\n";
}

void editrecord(struct record &records){
    int editcom = 9;
    while (editcom != 0){
        printsinglerecord(records);
        cout << "What to change?\n";
        cout << "0. return\n";
        cout << "1. date   2. Account   3. type   4. usage   5. amount   6. Notes\n";
        cin >> editcom;
        if (editcom == 1){
            cout << "Newdate?   ";
            cin >> records.date;
        }
        if (editcom == 2){
            int account;
            if (records.type == 'R'){
                cout << "1. Cash   2. Bank\n";
                cin >> account;
                if (account == 1){
                    records.account = "Cash";
                }
                else{
                    records.account = "Bank";
                }
            }
            else{
                cout << "1. Cash   2. Bank   3. Credit_Card\n";
                cin >> account;
                if (account == 1){
                    records.account = "Cash";
                }
                else if (account == 2){
                    records.account = "Bank";
                }
                else{
                    records.account = "Credit_Card";
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
                    records.usage = "Entertainment";
                }
                if (type == 2){
                    records.usage = "Transport";
                }
                if (type == 3){
                    records.usage = "Food";
                }
                if (type == 4){
                    records.usage = "Bill";
                }
                if (type == 5){
                    records.usage = "Others";
                }
            }
            else{
                int type;
                cout << "1. Salary   2. others\n";
                cin >> type;
                if (type == 1){
                    records.usage = "Salary";
                }
                if (type == 2){
                    records.usage = "Others";
                }
            }
        }
        if (editcom == 5){
            cout << "New amount?   ";
            cin >> records.amount;
        }
        if (editcom == 6){
            cout << "New Notes:   ";
            cin.ignore();
            getline(cin, tempnote);
            if (tempnote == ""){
                tempnote = "N";
            }
            records.notes = tempnote;
        }
    }
}

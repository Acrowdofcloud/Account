#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "structs.h"
#include "getdate.h"
#include "recordmanip.h"
#include "alarm.h"
#include "addrecords.h"
#include "filemanip.h"
#include "report.h"
using namespace std;

int main(){
    string todaydate = gettime(); //getdate.h
    double budget = 0;
    int command;
    int x;
    ifstream fin;
    struct record records[20000] = {};

    fin.open("budget.txt");
    fin >> budget;
    fin.close();
    if (budget == 0){
        cout << "Whats your monthly budget?";
        cin >> budget;
    }

    int index = 0;
    fin.open("sortedrecord.txt");
    while (fin >> records[index].date >> records[index].account >> records[index].type >> records[index].usage >> records[index].amount >> records[index].notes){
        records[index].exist = true;
        index++;
    }
    fin.close();
    printallrecords(records);
    alarm(budget, records);

    while (true){
        for (int i = 0; i < 20000; i++){
            records[i].exist = false;
        }
        fin.open("budget.txt");
        fin >> budget;
        fin.close();
        if (budget == 0){
            cout << "Whats your monthly budget?";
            cin >> budget;
        }
        index = 0;
        fin.open("sortedrecord.txt");
        while (fin >> records[index].date >> records[index].account >> records[index].type >> records[index].usage >> records[index].amount >> records[index].notes){
            records[index].exist = true;
            index++;
        }
        fin.close();

        for (int i = 0; i<20000; i++){
            if (records[i].exist == false){
                x = i;
                break;
            }
        }

        cout << "What do you want to do?\n";
        cout << "1. Display records 2. New Expense      3. New Income       4. Edit Record\n";
        cout << "5. Delete Record   6. Statistic report 7. Change budget    0. Exit" << endl;
        cout << "***************************************************************************\n";
        cin >> command;

        if (command == 1){
            printallrecords(records); //recordmanip.h
            alarm(budget, records); //alarm.h
        }
        if (command == 2){
            addexpense(todaydate, records[x]); //addrecords.h
            printallrecords(records); //recordmanip.h
            cout << "\n";
            alarm(budget, records); //alarm.h
        }
        if (command == 3){
            addincome(todaydate, records[x]); //addrecords.h
            printallrecords(records); //recordmanip.h
            cout << "\n";
            alarm(budget, records); //alarm.h
        }
        if (command == 4){
            int edit;
            cout << "Which record?\n";
            printallrecords(records); //recordmanip.h
            cin >> edit;
            editrecord(records[edit-1]); //recordmanip.h
        }
        if (command == 5){
            int del;
            cout << "Which record?\n";
            cout << "0. Return\n";
            printallrecords(records); //recordmanip.h
            cin >> del;
            if (del != 0){
                deleterecord(records[del - 1]); //recordmanip.h
            }
        }
        if (command == 6){
            report(budget, records); //report.h
        }
        if (command == 7){
          cout << "New budget? ";
          cin >> budget;
        }
        if (command == 0){
            break;
        }

        system("rm budget.txt");
        ofstream budout;
        budout.open("budget.txt");
        budout << budget;
        budout.close();

        writetorecord(records); //filemanip.h

        system("rm sortedrecord.txt");
        system("sort -k1 -k2 record.txt >> sortedrecord.txt");
    }
    return 0;
}

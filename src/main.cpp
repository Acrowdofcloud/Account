#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include "class.h"
#include "getdate.h"
#include "recordmanip.h"
#include "database.h"
#include "addrecord.h"
#include "alarm.h"
#include "global.h"
#include "report.h"
#include "config.h"

using namespace std;

int main() {
    double budget, creditlim = 0;
    ifstream fin;
    fin.open(getmonth() + "budget.txt");
    if (fin.fail()){ofstream fout(getmonth() + "budget.txt");}
    else{fin >> budget >> creditlim;}
    fin.close();

    if (budget == 0){cout << "What's your monthly budget? ";
                     cin >> budget;
                     ofstream fout(getmonth()+"budget.txt");
                     fout << budget << " " << creditlim;}

    if (creditlim == 0){cout << "What's your monthly credit limit? ";
                        cin >> creditlim;
                        ofstream fout(getmonth()+"budget.txt");
                        fout << budget << " " << creditlim;}
    int command = -1;

    cout << "Latest records:\n";
    show10();
	while (command != 0){
        budgetalarm(budget);
        creditalarm(creditlim);
        printf("What do you want to do?\n");
        printf("0. Return\n");
        printf("1. Display records  2. Add expense  3. Add income  4. Delete record   5. Edit record\n");
        printf("6. Statistical report   7. Configuration\n");
        separation(105);
        cin >> command;
        record entry;

        if (command == 1){
            int choice;
            cout << "1. Show latest 10 records  2. Search records\n";
            cin >> choice;
            if ( choice == 1 ) { show10(); }
            else if ( choice == 2 ) { searchAndSelectRecord("display"); }
            else {continue;}
            cout << "Press Enter to Continue\n";
            cin.ignore();
            cin.ignore();
        }

        if (command == 2){
            entry.setType("E");
            addexpense(entry);
            insertRecord(entry);
        }

        else if (command == 3){
            entry.setType("R");
            addincome(entry);
            insertRecord(entry);

        }

        else if(command == 4){
            vector<record> target_list;
            target_list = searchAndSelectRecord("select");       //searchAndSelectRecord() let user choose parameter for searchRecord()
            if ( target_list.size() == 0) { continue; }
            for (int i{0};i < target_list.size();i++) {     //do the search,let user select the record(s),return a vector of records
                deleteRecord(target_list[i]);
            }

        }
        else if(command == 5) {
            vector<record> target_list;
            target_list = searchAndSelectRecord("select");
            if ( target_list.size() == 0) { continue; }
            for (int i{0};i < target_list.size();i++) {
                record temp = target_list[i];
                editRecord(temp);
                deleteRecord(target_list[i]);
                insertRecord(temp);
            }
        }

        else if(command == 6){
            string reportmonth;
            string line;
            cout << "Which month? (YYYYMM) Leave blank as current month\n";
            cin.ignore();
            getline(cin, reportmonth);
            if (reportmonth == ""){
                reportmonth = getmonth();
            }
            if (fileExist(reportmonth + ".txt")){
                report(reportmonth);
                fin.open(reportmonth + "report.txt");
                while (getline(fin,line)){
                    cout << line << endl;
                }
                fin.close();
                separation(105);
            }
            else{cout << "No record for " << reportmonth << endl;}
        }
        else if(command == 7){
            configmenu();
            fin.open(getmonth() + "budget.txt");
            fin >> budget >> creditlim;
            fin.close();
        }
	}

    return 0;
}


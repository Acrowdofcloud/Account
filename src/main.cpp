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
    show10();
    budgetalarm(budget);
    separation(105);
    creditalarm(creditlim);
    separation(105);

	while (command != 0){
        printf("What do you want to do?\n");
        printf("0. Return\n");
        printf("1. Add expense  2. Add income  3. Delete record   4. Edit record\n");
        printf("5. Statistical report\n");
        separation(105);
        cin >> command;
        record entry;

        if (command == 1){
            entry.setType("E");
            addexpense(entry);
            insertRecord(entry);
            show10();
            budgetalarm(budget);
            separation(105);
            creditalarm(creditlim);
            separation(105);
        }

        else if (command == 2){
            entry.setType("R");
            addincome(entry);
            insertRecord(entry);
            show10();
            budgetalarm(budget);
            separation(105);
            creditalarm(creditlim);
            separation(105);
        }

        else if(command == 3){
            vector<record> target_list;
            target_list = searchAndSelectRecord();       //searchAndSelectRecord() let user choose parameter for searchRecord(),
            for (int i{0};i < target_list.size();i++) {     //do the search,let user select the record(s),return a vector of records
                deleteRecord(target_list[i]);
            }
            show10();
            budgetalarm(budget);
            separation(105);
            creditalarm(creditlim);
            separation(105);
        }
        /*
        else if(command == 4) {
            vector<record> target_list;
            target_list = searchAndSelectRecord();
            for (int i{0};i < target_list.size();i++) {
                record temp = target_list[i];
                editRecord(temp);
                deleteRecord(target_list[i]);
                insertRecord(temp);
            }
        }
        */

        else if(command == 5){
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
	}

    return 0;
}


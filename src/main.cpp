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
    //get the monthly budget and credit limit
    fin.open(getmonth() + "budget.txt");
    if (fin.fail()){ofstream fout(getmonth() + "budget.txt");}
    else{fin >> budget >> creditlim;}
    fin.close();
    //asks user for budget and credit limit if no previous record
    if (budget == 0){cout << "What's your monthly budget? ";
                     cin >> budget;
                     ofstream fout(getmonth()+"budget.txt");
                     fout << budget << " " << creditlim;}

    if (creditlim == 0){cout << "What's your monthly credit limit? ";
                        cin >> creditlim;
                        ofstream fout(getmonth()+"budget.txt");
                        fout << budget << " " << creditlim;}
    int command = -1;
    //show latest 10 records
    cout << "Latest records:\n";
    show10();
	while (command != 0){
        budgetalarm(budget); //check if total expense exceeds 70% of the budget or not
        creditalarm(creditlim); //check if total credited expense exceeds 70% of the credit limit or not
        printf("What do you want to do?\n");
        printf("0. Return\n");
        printf("1. Display records  2. Add expense  3. Add income  4. Delete record   5. Edit record\n");
        printf("6. Statistical report   7. Configuration\n");
        separation(105);
        cin >> command; //get user command
        record entry;

        if (command == 1){ //display records
            int choice;
            //user chooses what to display
            cout << "1. Show latest 10 records  2. Search records\n";
            cin >> choice;
            if ( choice == 1 ) { show10(); }
            else if ( choice == 2 ) { searchAndSelectRecord("display"); }
            else {continue;}
            cout << "Press Enter to Continue\n";
            cin.ignore();
            cin.ignore();
        }

        if (command == 2){ //add expense
            entry.setType("E");
            addexpense(entry);
            insertRecord(entry);
        }

        else if (command == 3){ //add income
            entry.setType("R");
            addincome(entry);
            insertRecord(entry);

        }

        else if(command == 4){//delete record
            vector<record> target_list;
            target_list = searchAndSelectRecord("select");       //searchAndSelectRecord() let user choose parameter for searchRecord()
            if ( target_list.size() == 0) { continue; }
            for (int i{0};i < target_list.size();i++) {     //do the search,let user select the record(s),return a vector of records
                deleteRecord(target_list[i]);
            }

        }
        else if(command == 5) {//edit record
            vector<record> target_list;
            target_list = searchAndSelectRecord("select");  //searchAndSelectRecord() let user choose parameter for searchRecord()
            if ( target_list.size() == 0) { continue; }
            for (int i{0};i < target_list.size();i++) { //do the search,let user select the record(s),return a vector of records
                record temp = target_list[i];
                editRecord(temp);
                deleteRecord(target_list[i]);
                insertRecord(temp);
            }
        }

        else if(command == 6){ //make statistical report
            string reportmonth;
            string line;
            cout << "Which month? (YYYYMM) Leave blank as current month\n";
            cin.ignore();
            //user input the month which records are to be reported
            getline(cin, reportmonth);
            if (reportmonth == ""){
                reportmonth = getmonth();//report on current month if no user input
            }
            if (fileExist(reportmonth + ".txt")){//report if records for that month exist in directory
                report(reportmonth);
                fin.open(reportmonth + "report.txt");
                while (getline(fin,line)){
                    cout << line << endl;
                }
                fin.close();
                separation(105);
            }
            else{cout << "No record for " << reportmonth << endl;}//tell user no records for that month in directory
        }
        else if(command == 7){//configuration for the month
            configmenu();
            fin.open(getmonth() + "budget.txt");//get updated budget or credit limit
            fin >> budget >> creditlim;
            fin.close();
        }
	}

    return 0;
}


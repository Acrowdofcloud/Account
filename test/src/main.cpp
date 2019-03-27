#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include "class.h"
#include "getdate.h"
#include "recordmanip.h"
#include "database.h"
#include "addrecord.h"
#include "alarm.h"

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

	//double creditlim = 0;
    int command = -1;
    //int x, index = 0;

	while (command != 0){
        show10();
        budgetalarm(budget);
        separation(105);
        printf("What do you want to do?\n");
        printf("0. Return\n");
        printf("1. Add expense  2. Add income  3. Delete record(WIP)   4. Edit record\n");
        separation(105);
        cin >> command;
        record entry;

        if (command == 1){
            entry.setType("E");
            addexpense(entry);
            insertRecord(entry);
        }

        else if (command == 2){
            entry.setType("R");
            addincome(entry);
            insertRecord(entry);
        }

        else if(command == 3){
            //searchrecord()
            cout << "Delete: WIP,enter whole line for now\n";
            string line;
            cin.ignore();
            getline(cin,line);
            record target;
            target = stringtoRecord(line);
            deleteRecord(target);
        }
        /*
        else if(command == 4) {
            cout << "Which record?\n";
            searchrecord()
            editrecord()
            deleteRecord(original)
            insertRecord(edited)
        }
        */
	}

    return 0;
}

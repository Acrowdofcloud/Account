#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include "test.h"
#include "getdate.h"
#include "recordmanip.h"
#include "database.h"
#include "addrecord.h"

using namespace std;

int main() {
    //double budget = 0;
	//double creditlim = 0;
    int command = -1;
    //int x, index = 0;

	while (command != 0){
        show10();
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
            cout << "Delete by line number in file:\n";
            int num;
            record target;
            cin.ignore();
            cin >> num;
            target.setLineNum(num);
            target.setDate("20190322");
            deleteRecord(target);
        }
	}

    return 0;
}

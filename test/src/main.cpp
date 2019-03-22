#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "test.h"
#include "getdate.h"
#include "recordmanip.h"
#include "filemanip.h"
#include "addrecord.h"

using namespace std;

void editrecord(record&);

int main() {
    double budget = 0;
	double creditlim = 0;
    int command = -1;
    int x, index = 0;

	while (command != 0){
        show10();
        printf("What do you want to do?\n");
        printf("0. Return\n");
        printf("1. Add expense  2. Add income  3. Delete record   4. Edit record\n");
        separation(105);
        cin >> command;
        record entry;

        if (command == 1){
            entry.setType('E');
            addexpense(entry);
            toRecord(entry);
        }

        else if (command == 2){
            entry.setType('R');
            addincome(entry);
            toRecord(entry);
        }

        else if(command == 3){

        }
	}



    return 0;
}

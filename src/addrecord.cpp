#include "class.h"
#include "recordmanip.h"
#include "addrecord.h"
#include <iostream>

using namespace std;


void addexpense(record& records){       //create new record
    cout << "Newdate? Leave blank to set as today\n";
    cin.ignore();
    records.input("date", "NULL");

    cout << "Account? (Default account: Cash)\n";
    records.input("account", "NULL");

    cout << "Amount?\n";
    records.input("amount", "NULL");

    cout << "Usage?\n";
    string usage = expensetypes("add");
    records.setUsage(usage);

    cin.ignore();
    cout << "Notes?\n";
    records.input("note", "NULL");

    separation(105);
    cout << "Record added:\n";
    cout << "  ";
    cout << records.toString() << "\n";
}

void addincome(record& records){        //create new record
    cout << "New date? Leave blank to set as today\n";
    cin.ignore();
    records.input("date", "NULL");

    cout << "Account? (Default account: Bank)\n";
    records.input("account", "NULL");

    cout << "Amount?\n";
    records.input("amount", "NULL");

    cout << "Source?\n";
    string source = incometypes("add");
    records.setUsage(source);

    cin.ignore();
    cout << "Notes?\n";
    records.input("note", "NULL");

    separation(105);

    cout << "Record added:\n";
    cout << "  ";
    cout << records.toString() << endl;

}

void editRecord(record &records) {      //change input record
    cout << "New date? Leave blank to skip\n" << "Current: " << records.getDate() << endl;
    cin.ignore();
    records.input("date", "edit");

    cout << "Account? Leave blank to skip\n" << "Current: " << records.getAccount() << endl;
    records.input("account", "edit");

    cout << "Amount? Leave blank to skip\n" << "Current: " << records.getAmount() << endl;
    records.input("amount", "edit");

    cout << "Source?\n";
    string source;
    if (records.getType() == "E") { source = expensetypes("edit"); }
    else { source = incometypes("edit"); }

    if (source.length() != 0) {
        records.setUsage(source);
    }

    cout << "Notes? Leave blank to skip\n" << "Current: " << records.getNote() << endl;
    cin.ignore();
    records.input("note", "edit");

    separation(105);

    cout << "Record edited:\n";
    cout << "  ";
    cout << records.toString() << endl;

}

string expensetypes(string mode){
    printf("1. Transports   2. Food   3. Entertainments   4. Bill   5. Others\n");
    if ( mode == "edit" ) { cout << "6. Skip\n"; }
    int t;
    cin >> t;
    switch (t){
        case 1:{
            return "Transports";
        }break;

        case 2:{
            return "Food";
        }break;

        case 3:{
            return "Entertainments";
        }break;

        case 4:{
            return "Bills";
        }break;

        case 5:{
            return "Others";
        }break;

        case 6:{
            return "";
        }break;
    }
}

string incometypes(string mode){
    printf("1. Salary   2. Others\n");
    if ( mode == "edit" ) { cout << "3. Skip\n"; }
    int t;
    cin >> t;
    switch (t){
        case 1:{
            return "Salary";
        }break;
        case 2:{
            return "Others";
        }break;
        case 3:{
            return "";
        }break;

    }
}

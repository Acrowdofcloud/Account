#include "class.h"
#include "recordmanip.h"
#include "addrecord.h"
#include <iostream>

using namespace std;


void addexpense(record& records){
    cout << "Newdate? Leave blank to set as today\n";
    cin.ignore();
    records.input("date", "NULL");

    cout << "Account? (Default account: Cash)\n";
    records.input("account", "NULL");

    cout << "Amount?\n";
    records.input("amount", "NULL");

    cout << "Usage?\n";
    string usage = expensetypes();
    records.input("usage", usage);

    cout << "Notes?\n";
    records.input("note", "NULL");

    separation(105);
    cout << "Record added:\n";
    cout << "  ";
    cout << records.toString() << "\n";
}

void addincome(record& records){
    cout << "Newdate? Leave blank to set as today\n";
    cin.ignore();
    records.input("date", "NULL");

    cout << "Account? (Default account: Bank)\n";
    records.input("account", "NULL");

    cout << "Amount?\n";
    records.input("amount", "NULL");

    cout << "Source?\n";
    string source = incometypes();
    records.input("usage", source);

    cout << "Notes?\n";
    records.input("note", "NULL");

    separation(105);

    cout << "Record added:\n";
    cout << "  ";
    cout << records.toString() << endl;

}

string expensetypes(){
    printf("1. Transports   2. Food   3. Entertainments   4. Bill   5. Others\n");
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
    }
}

string incometypes(){
    printf("1. Salary   2. Others\n");
    int t;
    cin >> t;
    switch (t){
        case 1:{
            return "Salary";
        }break;
        case 2:{
            return "Others";
        }break;

    }
}

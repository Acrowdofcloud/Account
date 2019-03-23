#include "test.h"
#include "recordmanip.h"
#include "addrecord.h"
#include <iostream>

using namespace std;


void addexpense(record& records){
    cout << "Newdate? Leave blank to set as today\n";
    cin.ignore();
    records.input("date");

    cout << "Account? (Default account: Cash)\n";
    records.input("account");

    cout << "Amount?\n";
    records.input("amount");

    cout << "Usage?\n";
    records.input("usage");

    cout << "Notes?\n";
    records.input("note");

    separation(105);
    cout << "Record added:\n";
    cout << "  ";
    cout << records.toString();
}

void addincome(record& records){
    cout << "Newdate? Leave blank to set as today\n";
    cin.ignore();
    records.input("date");

    cout << "Account? (Default account: Bank)\n";
    records.input("account");

    cout << "Amount?\n";
    records.input("amount");

    cout << "Source?\n";
    records.input("usage");

    cout << "Notes?\n";
    records.input("note");

    separation(105);

    cout << "Record added:\n";
    cout << "  ";
    cout << records.toString() << endl;

}

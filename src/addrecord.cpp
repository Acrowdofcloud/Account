#include "class.h"
#include "recordmanip.h"
#include "addrecord.h"
#include <iostream>

using namespace std;


void addexpense(record& records){ //add new expense
    cout << "Newdate? Leave blank to set as today\n"; //get the date for the record
    cin.ignore();
    records.input("date", "NULL");//assign date to the temporary record to be added

    cout << "Account? (Default account: Cash)\n";//get account for the record
    records.input("account", "NULL");//assign account to the temporary record to be added

    cout << "Amount?\n";//get amount for the record
    records.input("amount", "NULL");//assign amount to the temporary record to be added

    cout << "Usage?\n";
    string usage = expensetypes("add");//get usage for the record
    records.setUsage(usage);//assign usage to the temporary record to be added

    cin.ignore();
    cout << "Notes?\n";//allow user to add note for the record
    records.input("note", "NULL");//assign note to the temporary record to be added

    separation(105);
    cout << "Record added:\n";
    cout << "  ";
    cout << records.toString() << "\n";
}

void addincome(record& records){//all comments are the same as the function addexpense()
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

void editRecord(record &records) {//edit record
    //ask if the user wants to change the date for the record
    //not allowed to move the record to another month
    cout << "New date? Leave blank to skip\n" << "Current: " << records.getDate() << endl;
    cin.ignore();
    records.input("date", "edit");//change the date for the record

    //ask if the user wants to change the account for the record
    cout << "Account? Leave blank to skip\n" << "Current: " << records.getAccount() << endl;
    records.input("account", "edit");//change the account of the record

    //ask if the user wants to change the amount for the record
    cout << "Amount? Leave blank to skip\n" << "Current: " << records.getAmount() << endl;
    records.input("amount", "edit");//change amount for record

    //ask if the user wants to change the usage for the record
    cout << "Source?\n";
    string source;
    if (records.getType() == "E") { source = expensetypes("edit"); }
    else { source = incometypes("edit"); } //change usage

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

string expensetypes(string mode){//get preset types for user
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

string incometypes(string mode){//get preset types for user
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

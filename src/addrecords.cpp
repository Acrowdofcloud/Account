#include "addrecords.h"
#include <iostream>
#include <string>
#include "structs.h"

using namespace std;

string tempdate, tempaccount, tempusage;
double tempamount;
char temptype;

string typeofexpense(){
    int type;
    cout << "1. Entertainment   2. Transport   3. Food   4. Bill   5. Others\n";
    cin >> type;
    if (type == 1){
        return "Entertainment";
    }
    if (type == 2){
        return "Transport";
    }
    if (type == 3){
        return "Food";
    }
    if (type == 4){
        return "Bill";
    }
    if (type == 5){
        return "Others";
    }
    return "";
}

string typeofincome(){
    int type;
    cout << "1. Salary   2. others\n";
    cin >> type;
    if (type == 1){
        return "Salary";
    }
    else if (type == 2){
        return "Others";
    }
    return "";
}

void addexpense(string todaydate, struct record &records){
    string tempnote;
    temptype = 'E';
    tempusage = typeofexpense();
    int account = 0;
    cout << "Amount?\t";
    cin >> tempamount;
    cout << "1. Cash   2. Bank   3. Credit_Card\n";
    cin >> account;
    if (account == 1){
        tempaccount = "Cash";
    }
    else if (account == 2){
        tempaccount = "Bank";
    }
    else{
        tempaccount = "Credit_Card";
    }


    cin.ignore();
    cout << "Notes: ";
    getline(cin, tempnote);
    if (tempnote == ""){
        tempnote = "N";
    }
    if(tempamount != 0){
        records.date = todaydate;
        records.amount = tempamount;
        records.exist = true;
        records.usage = tempusage;
        records.type = temptype;
        records.notes = tempnote;
        records.account = tempaccount;
    }
}

void addincome(string todaydate, struct record &records){
    string tempnote;
    int account;
    temptype = 'R';
    tempusage = typeofincome();
    cout << "Amount?\t";
    cin >> tempamount;
    cout << "1. Cash   2. Bank\n";
    cin >> account;
    if (account == 1){
        tempaccount = "Cash";
    }
    if (account == 2){
        tempaccount = "Bank";
    }


    cin.ignore();
    cout << "Notes: ";
    getline(cin, tempnote);
    if (tempnote == ""){
        tempnote = "N";
    }
    if(tempamount != 0){
        records.date = todaydate;
        records.amount = tempamount;
        records.exist = true;
        records.usage = tempusage;
        records.type = temptype;
        records.notes = tempnote;
        records.account = tempaccount;
    }
}

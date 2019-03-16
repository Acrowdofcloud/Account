#include "addrecords.h"
#include <iostream>
#include <string>
#include "structs.h"
#include "getdate.h"

using namespace std;

string tempdate, tempaccount, tempusage;
double tempamount;
char temptype;

string typeofexpense(){
    int type;
    cout << "0. Return   1. Entertainment   2. Transport   3. Food   4. Bill   5. Others\n";
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
    if (type == 0){
        return "";
    }
}

string typeofincome(){
    int type;
    cout << "0. Return   1. Salary   2. others\n";
    cin >> type;
    if (type == 1){
        return "Salary";
    }
    else if (type == 2){
        return "Others";
    }
    else{
        return "";
    }
}

void addexpense(string todaymonth, string todaydate, struct record &records){
    string tempnote;
    temptype = 'E';
    tempdate = todaydate;
    tempusage = typeofexpense();

    if (tempusage != ""){

        if (todaymonth != getmonth()){
        cout << "Date?\n";
        cin >> tempdate;
        }

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
            records.date = tempdate;
            records.amount = tempamount;
            records.exist = true;
            records.usage = tempusage;
            records.type = temptype;
            records.notes = tempnote;
            records.account = tempaccount;
        }
    }
}

void addincome(string todaymonth, string todaydate, struct record &records){
    string tempnote;
    tempdate = todaydate;
    int account;
    temptype = 'R';
    tempusage = typeofincome();
    if (tempusage != ""){
        if (todaymonth != getmonth()){
        cout << "Date?\n";
        cin >> tempdate;
        }

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
            records.date = tempdate;
            records.amount = tempamount;
            records.exist = true;
            records.usage = tempusage;
            records.type = temptype;
            records.notes = tempnote;
            records.account = tempaccount;
        }
    }
}

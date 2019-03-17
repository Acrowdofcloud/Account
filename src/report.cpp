#include "report.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include "structs.h"
#include "filemanip.h"
#include "alarm.h"

using namespace std;

void profitstat(string todaymonth, double budget, double statexpense, struct record records[]){
    double Entertainment = 0;
    double Food = 0;
    double Bill = 0;
    double Others = 0;
    double Transport = 0;
    string types;
    double statincome = calin(todaymonth, records);
    for (int i = 0; i < 2000; i++){
        if (records[i].exist == true){
            if (records[i].usage == "Entertainment"){
                Entertainment += records[i].amount;
            }
            if (records[i].usage == "Others"){
                Others += records[i].amount;
            }
            if (records[i].usage == "Bill"){
                Bill += records[i].amount;
            }
            if (records[i].usage == "Transport"){
                Transport += records[i].amount;
            }
            if (records[i].usage == "Food"){
                Food += records[i].amount;
            }
        }
    }

    writereport(todaymonth, statincome, statexpense, Entertainment, Transport, Food, Bill, Others, budget);
    cout << "***************************************************************************\n";
}

void accountstat(string todaymonth, double budget, struct record records[]){
    double Bankin = 0, Bankout = 0, Cashin = 0, Cashout  = 0, Credit = 0, Otherin = 0, Otherout = 0;
    for (int i = 0; i < 2000; i++){
        if (records[i].exist){
            if(records[i].account == "Bank"){
                if (records[i].type == 'E'){
                    Bankout += records[i].amount;
                }
                else{
                    Bankin += records[i].amount;
                }
            }
            else if (records[i].account == "Cash"){
                if (records[i].type == 'E'){
                    Cashout += records[i].amount;
                }
                else{
                    Cashin += records[i].amount;
                }
            }
            else if (records[i].account == "Others"){
                Otherin += records[i].amount;
            }
            else {
                Credit += records[i].amount;
            }
        }
    }
    writeaccount(todaymonth, Bankin, Bankout, Cashin, Cashout, Credit, Otherin, Otherout);
}

void report(string todaymonth, double budget, struct record records[]){
    string filename = todaymonth + "stat.txt";
    double statexpense = calout(todaymonth, records);
    profitstat(todaymonth, budget, statexpense, records);
    accountstat(todaymonth, budget, records);
    system(("cat " + filename).c_str());
}

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

void report(string todaymonth, double budget, struct record records[]){
    double statexpense = calout(todaymonth, records);
    profitstat(todaymonth, budget, statexpense, records);

}

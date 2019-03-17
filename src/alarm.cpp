#include "alarm.h"
#include <iostream>
#include <iomanip>
#include "structs.h"
#include "getdate.h"

using namespace std;

double calin(string todaymonth, struct record records[]){
    int tempincome = 0;
    for (int i = 0; i<2000; i++){
        if (records[i].exist == true){
            if (records[i].date.substr(0, 6) == todaymonth){
                if (records[i].type == 'R'){
                    tempincome += records[i].amount;
                }
            }
        }
    }
    return tempincome;
}

double calout(string todaymonth, struct record records[]){
    int tempexpense = 0;
    for (int i = 0; i<2000; i++){
        if (records[i].exist == true){
            if (records[i].date.substr(0, 6) == todaymonth){
                if (records[i].type == 'E'){
                    tempexpense += records[i].amount;
                }
            }
        }
    }
    return tempexpense;
}

double calcre(string todaymonth, struct record records[]){
    double temp = 0;
    for (int i = 0; i < 2000; i++){
        if (records[i].exist){
            if (records[i].date.substr(0, 6) == todaymonth){
                if (records[i].account == "Credit_Card"){
                    temp += records[i].amount;
                }
            }
        }
    }
    return temp;
}

void creditalarm(string todaymonth, double creditlim, struct record records[]){
    double totalcredit = calcre(todaymonth, records);
    if (totalcredit/creditlim >= 0.7){
        cout << "***************************************************************************\n";
        cout << "Alert! Your credit expense is " << setprecision(3) << totalcredit/creditlim * 100 << "% of your credit limit!" << endl;
    }
}
void alarm(string todaymonth, double creditlim, double budget, struct record records[]){
    double totalincome = calin(todaymonth, records);
    double totalexpense = calout(todaymonth, records);
    cout << "Total income : $";
    printf("%.2f\n", totalincome);
    cout << "Total expense: $";
    printf("%.2f\n", totalexpense);

    if (totalexpense >= budget*0.7){
        cout << "***************************************************************************\n";
        cout << "Alert! Your expense this month is " << setprecision(3) <<  totalexpense/budget * 100 << "% of your budget!" << endl;
    }
    creditalarm(todaymonth, creditlim, records);
    cout << "***************************************************************************\n";

}

#include "alarm.h"
#include <iostream>
#include <iomanip>
#include "structs.h"
#include "getdate.h"

using namespace std;

double calin(struct record records[]){
    int tempincome = 0;
    string month = getmonth();
    for (int i = 0; i<2000; i++){
        if (records[i].exist == true){
            if (records[i].date.substr(0, 6) == month){
                if (records[i].type == 'R'){
                    tempincome += records[i].amount;
                }
            }
        }
    }
    return tempincome;
}

double calout(struct record records[]){
    int tempexpense = 0;
    string month = getmonth();
    for (int i = 0; i<2000; i++){
        if (records[i].exist == true){
            if (records[i].date.substr(0, 6) == month){
                if (records[i].type == 'E'){
                    tempexpense += records[i].amount;
                }
            }
        }
    }
    return tempexpense;
}

void alarm(double budget, struct record records[]){
    double totalincome = calin(records);
    double totalexpense = calout(records);
    cout << "Total income : $";
    printf("%.2f\n", totalincome);
    cout << "Total expense: $";
    printf("%.2f\n", totalexpense);

    if (totalexpense >= budget*0.7){
        cout << "***************************************************************************\n";
        cout << "Alert! Your expense this month is " << setprecision(3) <<  totalexpense/budget * 100 << "% of your budget!" << endl;
    }
    cout << "***************************************************************************\n";
}

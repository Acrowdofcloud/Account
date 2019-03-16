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

void alarm(string todaymonth, double budget, struct record records[]){
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
    cout << "***************************************************************************\n";
}

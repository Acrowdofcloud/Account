#include <string>
#include <fstream>
#include "class.h"
#include "alarm.h"
#include "getdate.h"
#include "database.h"

using namespace std;

void budgetalarm(double budget){
    string filename = getmonth() + ".txt";
    ifstream fin(filename);
    string line;
    double totalexpense, totalincome = 0;
    while(getline(fin, line)){
        if (stringtoRecord(line).getType() == "E"){
            totalexpense += stringtoRecord(line).getAmount();
        }
        else{
            totalincome += stringtoRecord(line).getAmount();
        }
    }
    printf("Total Expense: %f\n", totalexpense);
    printf("Total Income:  %f\n", totalincome);
    if (totalexpense >= 0.7 * budget){
        printf("Alert!! Your expenses this month is %.0f%% of your budget!\n", ((totalexpense/budget) * 100));
    }
}

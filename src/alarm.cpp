#include <string>
#include <vector>
#include "class.h"
#include "alarm.h"
#include "getdate.h"
#include "database.h"
#include "global.h"

using namespace std;

void budgetalarm(double budget){//budget monitoring
    vector<record> search_result;
    string filename = getmonth() + ".txt";
    double totalexpense = 0, totalincome = 0;
    search_result = searchRecord(filename,"type","E"); //get records of expenses for current month

    for (int i{0};i < search_result.size();i++) { //add all expenses
        totalexpense += search_result[i].getAmount();
    }

    search_result = searchRecord(filename,"type","R");//get records of incomes for the current month
    for (int i{0};i < search_result.size();i++) {
        totalincome += search_result[i].getAmount();//add all incomes
    }
    printf("Total Expense: %f\n", totalexpense);
    printf("Total Income:  %f\n", totalincome);
    if (totalexpense >= 0.7 * budget){//notice user when expense exceed 70% of the monthly budget
        printf("Alert!! Your expenses this month is %.0f%% of your budget!\n", ((totalexpense/budget) * 100));
    }
    separation(105);

}

void creditalarm(double creditlim){//credit spending monitoring
    vector<record> search_results;
    string filename = getmonth() + ".txt";
    double totalcredit = 0;
    search_results = searchRecord(filename, "account", "Card");//get records of credited expense for current month
    for (int i = 0; i < search_results.size(); ++i){
        totalcredit += search_results[i].getAmount();//add all credited expenses
    }
    printf("Total credited expenses: %f\n", totalcredit);
    if (totalcredit >= creditlim * 0.7){//notice user when credited expense exceed 70% of the monthly credit limit
        printf("Alert!! Your credited expenses this month is %.0f%% of your credit limit!\n", ((totalcredit/creditlim) * 100));

    }
    separation(105);
}

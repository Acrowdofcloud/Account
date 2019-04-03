#include <string>
#include <vector>
#include "class.h"
#include "alarm.h"
#include "getdate.h"
#include "database.h"

using namespace std;

void budgetalarm(double budget){
    vector<record> search_result;
    string filename = getmonth() + ".txt";
    double totalexpense = 0, totalincome = 0;
    search_result = searchRecord(filename,"type","E");

    for (int i{0};i < search_result.size();i++) {
        totalexpense += search_result[i].getAmount();
    }

    search_result = searchRecord(filename,"type","R");
    for (int i{0};i < search_result.size();i++) {
        totalincome += search_result[i].getAmount();
    }
    printf("Total Expense: %f\n", totalexpense);
    printf("Total Income:  %f\n", totalincome);
    if (totalexpense >= 0.7 * budget){
        printf("Alert!! Your expenses this month is %.0f%% of your budget!\n", ((totalexpense/budget) * 100));
    }
}

void creditalarm(double creditlim){
    vector<record> search_results;
    string filename = getmonth() + ".txt";
    double totalcredit = 0;
    search_results = searchRecord(filename, "account", "Card");
    for (int i = 0; i < search_results.size(); ++i){
        totalcredit += search_results[i].getAmount();
    }
    printf("Total credited expenses: %f\n", totalcredit);
    if (totalcredit >= creditlim * 0.7){
        printf("Alert!! Your credited expenses this month is %.0f%% of your credit limit!\n", ((totalcredit/creditlim) * 100));
    }
}

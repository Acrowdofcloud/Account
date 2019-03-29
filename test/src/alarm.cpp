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

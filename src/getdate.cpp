#include "getdate.h"
#include <ctime>
#include <string>

using namespace std;

string temptime, tempmonth, year, month, day;
time_t now = time(0);


string getmonth(){//get current month of the os
    tm *ltm = localtime(&now);

    year = to_string(1900 + ltm->tm_year);
    month = to_string(1 + ltm->tm_mon);

    if (month.length() == 1){
      month = "0" + month;
    }
    tempmonth = year+month;
    return tempmonth;
}

string gettime(){//get current date of the os
    tm *ltm = localtime(&now);

    year = to_string(1900 + ltm->tm_year);
    month = to_string(1 + ltm->tm_mon);
    day = to_string(ltm->tm_mday);


    if (day.length() == 1){
        day = "0" + day;
    }
    if (month.length() == 1){
        month = "0" + month;
    }
    temptime = year+month+day;
    return temptime;
}

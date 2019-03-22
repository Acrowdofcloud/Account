#include <iostream>
#include <iomanip>
#include <string>
#include "test.h"
#include "getdate.h"

using namespace std;

int main() {
    record entry[3];
    for (int i{0};i < 3;i++) {
        string line,result;
        entry[i].setAccount("Visa card 1234");

        cout << "Date: (YYYYMMDD,Leave blank to set as today)\n";
        while ( result != "ok" ) {
            if ( result != "" ) {cout << result << endl;}
            getline(cin,line);
            if ( line.length() == 0 ) { result = entry[i].setDate(gettime()); }    //set to current date if blank
            else { result = entry[i].setDate(line); }
        }
        result = "";

        cout << "Amount: \n";
        entry[i].inputAmount();

        result = "";
        cout << "Usage: \n";
        while (result != "ok") {
            if (result != "") {cout << result << endl;}
            getline(cin,line);
            result = entry[i].setUsage(line);
        }

        result = "";
        cout << "Note: \n";
        while (result != "ok") {
            if (result != "") {cout << result << endl;}
            getline(cin,line);
            result = entry[i].setNote(line);
        }
        cout << entry[i].getDate() << endl;
        cout << fixed << setprecision(2) << entry[i].getAmount() << endl;
        cout << entry[i].getAccount() << endl;
        cout << entry[i].getUsage() << endl;
        cout << entry[i].getNote() << endl;
        cout << entry[i].getType() << endl;
        cout << endl;
    }

    for (record& c : entry) { cout << c.toString(); }
    return 0;
}

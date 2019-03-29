#include "recordmanip.h"
#include "getdate.h"
#include "class.h"
#include "database.h"
#include "global.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>

using namespace std;

void separation(int len){
    for (int i = 0; i < len; i++){
        cout << "*";
    }
    cout << endl;
}

void show10(){
    int num_of_line = getNumofRecords(getmonth() + ".txt");
    ifstream fin(getmonth() + ".txt");
    if (fin.fail() || fin.eof()) {return;}
    string line;
    int current_line_num{1};
    if (num_of_line > 10) {
        current_line_num = num_of_line - 10 + 1 ;
        int i{1};
        while (i < current_line_num) {
            getline(fin,line);
            i++;
        }
    }
    separation(105);
    for (;current_line_num <= num_of_line; current_line_num++) {
        if (getline(fin,line)) {
            cout << current_line_num << ". " << line << endl;
        }
    }
    separation(105);
    fin.close();
}

vector<record> search_and_select_record() {
    vector<record> output;
    cout << "Input the year and month of the record(YYYYMM):\n";
    string month;
    cin >> month;
    if ( ! file_exist(month + ".txt") ) {       //check file exist
        cout << "Cannot find record file for " << month << "\n";
        output.push_back(::empty);
        return output;
    }

    vector<record> result;
    cout << "Search the record by:\n1.Date    not done(2.Type   3.Account    4.Usage)\n";
    int choice;
    cin >> choice;
    switch(choice) {        //To enter search field and keyword
        case 1: cout << "Input the day(DD) of the record:\n";
                string day;
                cin >> day;
                result = searchRecord(month + ".txt","date",month + day);

    }
    if ( result.size() == 0 ) {     //check search did found sth
        cout << "Search returned 0 result\n";
        output.push_back(::empty);
        return output;
    }

    bool show_all{true};        //ask user whether to show every result
    if ( result.size() > 20 ) {
        cout << "The search result contain " << result.size() << " results,show all of them? (Y/N)\n";
        char input;
        cin >> input;
        if (input == 'N' || input == 'n') { show_all = false; }
    }

    string record_choice;
    if (show_all) {         //choosing record
        for (int i{0};i < result.size();i++) {
            cout << setw(4) << i+1 << ":";
            cout << result[i].toString() << "\n";
        }
        cout << "\nChoose the record number or type all to choose all\n";
        cin >> record_choice;
        if ( record_choice == "all") { return result; }
        output.push_back(result[stoi(record_choice) - 1]);
        return output;
    }
    else {
        int line_number{1};
        int startpos;
        startpos = result.size() - 20;
        for (int i{startpos};i < result.size();i++) {
            cout << setw(4) << line_number << " : ";
            cout << result[i].toString() << "\n";
            line_number++;
        }
        cout << "\nChoose the record number or type all to choose all:\n";
        cin >> record_choice;
        if ( record_choice == "all") { return result; }
        int chosen_record_num;
        chosen_record_num = stoi(record_choice) + (result.size() - 20 - 1);
        output.push_back(result[chosen_record_num]);
        return output;
    }
}

bool file_exist(string file) {      //return true if file exist
    ifstream fin(file);
    if (fin.fail()) { return false; }
    fin.close();
    return true;
}


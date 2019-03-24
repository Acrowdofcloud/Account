#include "test.h"
#include "getdate.h"
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <regex>

using namespace std;

record::record() {
    date = "00000000";
    account = "";
    type = " ";
    amount = 0;
    usage = "";
    note = "";
}

string record::getDate() const { return date; }
string record::getAccount() const { return account; }
string record::getUsage() const { return usage; }
string record::getNote() const { return note; }
double record::getAmount() const { return amount; }
string record::getType() const { return type; }
int record::getLineNum() const { return line_num; }

void record::input(string field) {
    string result,line;
    while (result != "ok") {
        getline(cin, line);
        if (field == "date") {
            if ( line.length() == 0) {line = gettime();}
            result = setDate(line);
        }
        if (field == "account") result = setAccount(line);
        if (field == "amount") result = setAmount(line);
        if (field == "usage") result = setUsage(line);
        if (field == "note") result = setNote(line);
    }
}

string record::toString() const {
    ostringstream output;
    output << date << " " << type << " " << setw(amount_width) << fixed << setprecision(2) << amount << " " << setw(usage_width) << usage;
    output << " " << setw(account_width) << account << " " << setw(note_width) << note;
    return output.str();
}


string record::setDate(string input) {
    if ( input.length() != 8 ) {
        cout << "Wrong date format\n";
        return "error";
    }      //simply check for length
    date = input;
    return "ok";
}

string record::setAccount(string input) {
    if ( input.length() > account_width ) {
        cout << "Account name is too long,limit is " + to_string(account_width) + " characters\n" ;
        return "error";
    }      //check for length

    else if(input == ""){
        if (type == "R"){
            input = "Bank";
        }
        else{
            input = "Cash";
        }
    }
    account = input;
    return "ok";
}

string record::setUsage(string input) {
    if ( input.length() > usage_width ) {
        cout << "Usage info is too long,limit is " + to_string(usage_width) + " characters\n";
        return "error";
    }      //check for length
    usage = input;
    return "ok";
}

string record::setNote(string input) {
    if ( input.length() > note_width ) {
        cout << "Note is too long,limit is " + to_string(note_width) + " characters\n";
        return "error";
    }
    note = input;
    return "ok";
}

string record::setType(string input) {
    type = input;
    return "ok";
}

int record::setLineNum(int input) {
    line_num = input;
}

string record::setAmount(string input) {
    regex test("^\\d+[.]?\\d*");
    if ( ! regex_match(input,test)) {
        cout << "Input is not a correct number\n";
        return "error";
    }
    if (input.find(".") == string::npos) {      //true if no "."
        //run if is input is int
        if ((amount_width-3) < input.length()) {
            cout << "Amount to long,max is " + to_string(amount_width-3) + " digits before the decimal point\n";
            return "error";
        }
    }
    else {
        input = input.substr(0,input.find(".")+3);   //cut anything after 2 decimal places
        if ((amount_width) < input.length()) {
            cout << "Amount to long,max is " + to_string(amount_width-3) + " digits before the decimal point\n";
            return "error";
        }
    }
    double number;
    number = stod(input);
    if (number == 0) {
        cout << "Input should not be zero\n";
        return "error";
    }
    amount = number;
    return "ok";
}


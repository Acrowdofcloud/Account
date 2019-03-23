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
//add consturctor to set type?
string record::getDate() const { return date; }
string record::getAccount() const { return account; }
string record::getUsage() const { return usage; }
string record::getNote() const { return note; }
double record::getAmount() const { return amount; }
char record::getType() const { return type; }

void record::input(string field) {
    string result,line;
    while (result != "ok") {
        if (result != "") cout << result << endl;
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
    output << " " << setw(account_width) << account << " " << setw(note_width) << note << "|" << endl;
    return output.str();
}


string record::setDate(string input) {
    if ( input.length() != 8 ) { return "Wrong date format"; }      //simply check for length
    date = input;
    return "ok";
}

string record::setAccount(string input) {
    if ( input.length() > account_width ) { return "Account name is too long,limit is " + to_string(account_width) + " characters" ; }      //check for length

    else if(input == ""){
        if (type == 'R'){
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
    if ( input.length() > usage_width ) { return "Usage info is too long,limit is " + to_string(usage_width) + " characters" ; }      //check for length
    usage = input;
    return "ok";
}

string record::setNote(string input) {
    if ( input.length() > note_width ) { return "Note is too long,limit is " + to_string(note_width) + " characters" ; }      //check for length
    note = input;
    return "ok";
}

string record::setType(char input) {
    type = input;
    return "ok";
}

string record::setAmount(string input) {
    regex test("^\\d+[.]?\\d*");
    if ( ! regex_match(input,test)) { return "Input is not a correct number"; }
    double number;
    number = stod(input);
    if (number == 0) { return "Input should not be zero"; }        //check input not start with letter/is 0
    if (pow(10,(amount_width-3)) <= number) { return "Amount to large,max is " + to_string(amount_width-3) + " digits"; }        //check if input is too long
    else {
        amount = floor(100 * number)/100;       //round down to 2 decimal places
        return "ok";
    }
}


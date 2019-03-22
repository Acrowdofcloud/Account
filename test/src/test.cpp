#include "test.h"       //used to avoid redeclaration within header and its cpp,eg int hi below
#include <string>
#include <iostream>
#include <sstream>
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

void record::inputAmount() {
    string result,line;
    while (result != "ok") {
        if (result != "") {cout << result << endl;}
        getline(cin,line);
        result = setAmount(line);
    }

}

string record::toString() const {
    ostringstream output;
    output << date << " " << setw(amount_width) << fixed << setprecision(2) << amount << " " << setw(usage_width) << usage;
    output << " " << setw(account_width) << account << " " << setw(note_width) << note << "|" << endl;
    return output.str();
}

void record::toRecord(string input) {

}

string record::setDate(string input) {
    if ( input.length() != 8 ) { return "Wrong date format"; }      //simply check for length
    date = input;
    return "ok";
}

string record::setAccount(string input) {
    if ( input.length() > account_width ) { return "Account name is too long,limit is " + to_string(account_width) + " characters" ; }      //check for length
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
    type = 'E';
    return "ok";
}

string record::setAmount(string input) {
    regex test("^\\d+[.]?\\d*");
    if ( ! regex_match(input,test)) { return "Input is not a correct number"; }
    double number;
    number = atof(input.c_str());
    if (number == 0) { return "Input should not be zero"; }        //check input not start with letter/is 0
    if (pow(10,(amount_width-3)) <= number) { return "Amount to large,max is " + to_string(amount_width-3) + " digits"; }        //check if input is too long
    else {
        amount = floor(100 * number)/100;       //round down to 2 decimal places
        return "ok";
    }
}


#include "database.h"
#include "test.h"
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

record empty;
int line_length = empty.toString().length();

void insertRecord(record input) {
    ofstream fout;
    fout.open(input.getDate().substr(0,6) + ".txt", ios::app);
    fout << input.toString() << endl;
    fout.close();
}

record stringtoRecord(string& line) {
    record extract;
    extract.setDate(line.substr(0,8));
    extract.setType(line.substr(9,1));
    extract.setAmount(remove_all_space(line.substr(11,amount_width)));
    extract.setUsage(line.substr(11+amount_width+1,usage_width));
    extract.setAccount(line.substr(11+amount_width+1+account_width+1,account_width));
    extract.setNote(line.substr(line_length-note_width,note_width));
    return extract;
}

string remove_all_space(string input) {
    while (input.find(" ") != string::npos) {
        input.erase(input.find(" "),1);
    }
    return input;
}

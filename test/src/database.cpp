#include "database.h"
#include "global.h"
#include "test.h"
#include "global.h"
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

int getNumofRecords(string file) {
    ifstream fin;
    fin.open(file);
    fin.seekg(0,ios::end);
    streampos length = fin.tellg();
    return length/(::line_length + 1);
}

void insertRecord(record input) {
    ofstream fout;
    fout.open(input.getDate().substr(0,6) + ".txt", ios::app);
    fout << input.toString() << endl;
    fout.close();
}

record stringtoRecord(string& line) {
    if (line.length() != line_length) {
        cout << "The input is not a valid record\n";
        return ::empty; }
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

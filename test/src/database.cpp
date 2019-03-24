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
    return length/(::line_length + 2);
}

void insertRecord(record input) {
    ifstream fin;
    fin.open("");

    ofstream fout;
    fout.open(input.getDate().substr(0,6) + ".txt", ios::app);
    fout << input.toString() << endl;
    fout.close();
}

int deleteRecord(record input) {
    string record_file;
    record_file = input.getDate().substr(0,6) + ".txt";
    if ( input.getLineNum() == 0 || input.getLineNum() > getNumofRecords(record_file) ) {
        cout << "record line number is out of range\n";
        return -1;
    }
    ifstream fin(record_file, ios::binary);
    remove("temp.txt");
    ofstream fout("temp.txt", ios::app | ios::binary);
    streampos current_pos{0};
    string line;
    streampos target_pos = (input.getLineNum() - 1)*(::line_length + 2);
    while (current_pos < target_pos) {      //copy every line b4 the target record to temp.txt
        getline(fin,line);
        current_pos = fin.tellg();
        fout << line << endl;
    }
    current_pos += (::line_length + 2);
    fin.seekg(current_pos);
    fout << fin.rdbuf();        //skip the target record and copy the rest to temp.txt
    fin.close();
    fout.close();
    remove(record_file.c_str());
    char oldname[] ="temp.txt";
    int result = rename(oldname, record_file.c_str());
    return result;
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

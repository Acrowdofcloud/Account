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

int insertRecord(record input) {
    string record_file = input.getDate().substr(0,6) + ".txt";
    int input_date = stoi(input.getDate());
    ifstream fin;
    fin.open(record_file);
    streampos last_record_start;
    last_record_start = (getNumofRecords(record_file) - 1) * (::line_length + 2);
    fin.seekg(last_record_start);
    int last_record_date;
    fin >> last_record_date;
    ofstream fout;
    if ( last_record_date <= input_date ) {
        fout.open(record_file, ios::app);       //input is newer / the same as the last record
        fout << input.toString() << endl;
        fout.close();
        return 0;
    }
    else {
        fin.seekg(0,ios::beg);      //input is older
        int current_pos{0};
        int record_date{0};
        while (record_date < input_date) {
            fin >> record_date;
            current_pos += (::line_length + 2);
            fin.seekg(current_pos);
        }
    streampos target_pos = current_pos - (::line_length + 2);
    string line;
    fin.seekg(0,ios::beg);
    current_pos = fin.tellg();
    remove ("temp.txt");
    fout.open("temp.txt", ios::app);
    while (current_pos < target_pos) {
        getline(fin,line);
        current_pos = fin.tellg();
        fout << line << endl;
    }
    fout << input.toString() << endl;       //add the target record and copy the rest to temp.txt
    fout << fin.rdbuf();
    fin.close();
    fout.close();
    remove(record_file.c_str());
    char oldname[] ="temp.txt";
    int result = rename(oldname, record_file.c_str());
    return result;
    }
}


int deleteRecord(record input) {
    string record_file;
    record_file = input.getDate().substr(0,6) + ".txt";
    if ( input.getLineNum() == 0 || input.getLineNum() > getNumofRecords(record_file) ) {
        cout << "record line number is out of range\n";     //check input
        return -1;
    }

    ifstream fin(record_file,ios::binary);
    fin.rdbuf()->pubsetbuf(nullptr, 0);
    remove("temp.txt");
    ofstream fout("temp.txt", ios::app | ios::binary);
    streampos current_pos{0};
    string line;
    streampos target_pos = (input.getLineNum() - 1)*(::line_length + 2);
    while (current_pos < target_pos) {      //copy every line b4 the target record to temp.txt
        getline(fin,line);
        current_pos = fin.tellg();
        cout << "tellg(): " << current_pos << endl;
        fout << line << endl;
    }
    current_pos += (::line_length + 2);
    fin.seekg(current_pos);
    cout << "to seekg(): " << fin.tellg();
    cout << "after skip line: " << current_pos << endl;
    while (!fin.eof()) {
        getline(fin,line);
        fout << line << endl;
    }       //skip the target record and copy the rest to temp.txt
    fin.close();
    fout.close();
    //remove(record_file.c_str());
    //char oldname[] ="temp.txt";
    //int result = rename(oldname, record_file.c_str());
    //return result;
    return 0;
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

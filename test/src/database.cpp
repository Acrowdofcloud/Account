#include "database.h"
#include "global.h"
#include "class.h"
#include "global.h"
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include "getdate.h"
using namespace std;

int getNumofRecords(string file) {
    ifstream fin;
    string line;
    fin.open(file);
    int num_of_line{0};
    while(getline(fin,line)) { num_of_line++; }
    return num_of_line;
}

int insertRecord(record input) {
    string record_file = input.getDate().substr(0,6) + ".txt";
    int input_date = stoi(input.getDate());
    int num_of_line = getNumofRecords(record_file);
    ofstream fout;
    ifstream fin;
    fin.open(record_file);
    if (fin.fail()) {
        fout.open(record_file, ios::app);       //input needs to go to new file
        fout << input.toString() << "\n";
        fout.close();
        return 0;
    }
    int last_line = num_of_line;
    int current_line_num{1};
    string line;
    while (current_line_num < last_line) {
        getline(fin,line);
        current_line_num++;
        cout << current_line_num << "\n";
    }
    int last_record_date;
    fin >> last_record_date;

    cout << last_record_date << "\n";

    if ( last_record_date <= input_date ) {
        fout.open(record_file, ios::app);       //input is newer / the same as the last record
        fout << input.toString() << "\n";
        fout.close();
        return 0;
    }
    else {
        fin.seekg(0,ios::beg);      //input is older
        vector<string> records(num_of_line+1);
        bool inserted = false;
        for (int i{0};i<num_of_line+1;i++) {
            getline(fin,line);
            if (stoi(line.substr(0,8)) >= input_date && !inserted) {
                records[i] = input.toString();      //insert input when fin line date is larger than input
                inserted = true;
                i++;
                records[i] = line;
            }
            else {records[i] = line;
            }
        }
        remove ("temp.txt");
        fout.open("temp.txt", ios::app);
        for (string s : records) {      //write vector to file
            fout << s << "\n";
        }
    }
    fin.close();
    fout.close();
    remove(record_file.c_str());
    char oldname[] ="temp.txt";
    rename(oldname, record_file.c_str());
    return 0;
}


int deleteRecord(record input) {
    string record_file = input.getDate().substr(0,6) + ".txt";;
    ifstream fin(record_file);
    string target = input.toString();
    remove("temp.txt");
    ofstream fout("temp.txt",ios::app);
    string line;
    fin.clear();
    fin.seekg(0,ios::beg);
    bool deleted{false};
    while (getline(fin,line)) {
        if (line != target || deleted ) {
            fout << line << endl;
        }
        else {deleted = true;}
    }
    fin.close();
    fout.close();
    remove(record_file.c_str());
    char oldfile[] = "temp.txt";
    rename(oldfile,record_file.c_str());
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

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
    if ( input.getDate() == "00000000") { return -1; }      //check input is not an empty record
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
    }
    int last_record_date;
    fin >> last_record_date;

    if ( last_record_date <= input_date ) {
        fout.open(record_file, ios::app);       //input is newer / the same as the last record
        fout << input.toString() << "\n";
        fout.close();
        return 0;
    }
    else {
        fin.seekg(0,ios::beg);      //input is older
        string* records = new string[num_of_line+1];
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
        for (int i{0};i < (num_of_line+1);i++) {      //write array to file
            fout << records[i] << "\n";
        }
        delete [] records;
        records = nullptr;
    }
    fin.close();
    fout.close();
    remove(record_file.c_str());
    char oldname[] ="temp.txt";
    rename(oldname, record_file.c_str());
    return 0;
}

vector<record> searchRecord(string file,string field,string searchword) {       //if nth found,return vector with an empty record
    vector<record> result;
    if ( field != "type" && field != "date" && field != "usage" && field != "account" ) {
        cout << "The inputed search field is not supported\n";
        result.push_back(::empty);
        return result;
    }
    ifstream fin(file);
    string line;
    record temp;                //compare searchword to substring,add matched records to vector result
    if ( field == "type" ) {
        while ( getline(fin,line) ) {
            if (line.substr(9,1) == searchword) {
                temp = stringtoRecord(line);
                result.push_back(temp);
            }
        }
    }

    if ( field == "date" ) {
        while ( getline(fin,line) ) {
            if (line.substr(0,8) == searchword) {
                temp = stringtoRecord(line);
                result.push_back(temp);
            }
        }
    }

    if ( field == "usage" ) {
        int usage_startpos = 11+amount_width+1;
        while ( getline(fin,line) ) {
            if (removePrecedingSpace( line.substr(usage_startpos,usage_width) ) == searchword) {
                temp = stringtoRecord(line);
                result.push_back(temp);
            }
        }
    }

    if ( field == "account" ) {
        int account_startpos = 11+amount_width+1+account_width+1;
        while ( getline(fin,line) ) {
            if (removePrecedingSpace( line.substr(account_startpos,account_width) ) == searchword) {
                temp = stringtoRecord(line);
                result.push_back(temp);
            }
        }
    }

    return result;
}

int deleteRecord(record input) {
    if ( input.getDate() == "00000000") { return -1; }      //check input is not an empty record
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
    extract.setAmount(removeAllSpace(line.substr(11,amount_width)));
    extract.setUsage( removePrecedingSpace( line.substr(11+amount_width+1,usage_width) ) );
    extract.setAccount( removePrecedingSpace( line.substr(11+amount_width+1+account_width+1,account_width) ) );
    extract.setNote(removePrecedingSpace(line.substr(line_length-note_width,note_width)));
    return extract;
}

string removeAllSpace(string input) {
    while (input.find(" ") != string::npos) {
        input.erase(input.find(" "),1);
    }
    return input;
}

string removePrecedingSpace(string input) {
    int pos_of_first_nonspace{0};
    for (int i{0};i < input.length();i++) {
        if ( input.substr(i,1) != " ") {
            pos_of_first_nonspace = i;
            break;
        }
    }
    return input.substr(pos_of_first_nonspace);
}

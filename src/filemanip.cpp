#include "filemanip.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include "structs.h"
#include "getdate.h"
#include "alarm.h"

using namespace std;

void writetorecord(string todaymonth, string filename, struct record records[]){
    ofstream fout;
    remove(filename.c_str());
    fout.open(filename);
    for (int i = 0; i <2000; i++){
        if (records[i].exist == true){
            fout << setw(8) << records[i].date << " ";
            fout << setw(12) << records[i].account << " ";
            fout << setw(2) << records[i].type;
            fout << setw(20) << records[i].usage;
            fout << setw(8) << records[i].amount;
            fout << " " << records[i].notes << endl;
        }
    }
    fout.close();
}

void writereport(string todaymonth, double statincome, double statexpense, double Entertainment, double Transport, double Food, double Bill, double Others, double creditlim, double budget){
    string filename, cat;
    filename = todaymonth + "stat.txt";
    remove((todaymonth + "stat.txt").c_str());
    ofstream fout;
    fout.open(filename);
    fout << "Expenses for " << todaymonth << ": \n";
    fout << "Entertainment\t" << setw(15) << setprecision(6) << Entertainment << setw(20) << setprecision(3) << (Entertainment/statexpense) * 100 << "%\n";
    fout << "    Transport\t" << setw(15) << setprecision(6) << Transport << setw(20) << setprecision(3) << (Transport/statexpense) * 100 << "%\n";
    fout << "         Food\t" << setw(15) << setprecision(6) << Food << setw(20) << setprecision(3) << (Food/statexpense) * 100 << "%\n";
    fout << "         Bill\t" << setw(15) << setprecision(6) << Bill << setw(20) << setprecision(3) << (Bill/statexpense) * 100 << "%\n";
    fout << "       Others\t" << setw(15) << setprecision(6) << Others << setw(20) <<  setprecision(3) << (Others/statexpense) * 100 << "%\n";
    fout << "***************************************************************************\n";
    fout << "Budget: " << setprecision(6) << budget << setw(25) << "Credit Limit: " << setprecision(6) << creditlim << endl;
    fout << "\nTotal expense: " << setw(9) << setprecision(6) << statexpense << "       Total income:" << setw(8) << setprecision(6) << statincome << endl;
    fout << "Your expense in " << todaymonth << " is " << setprecision(3) << (statexpense/budget) * 100 << "% of your budget.\n";
    if (statincome < statexpense){
        fout << "You have a net loss of $" << setprecision(8) << statexpense - statincome  << " in " << todaymonth << ".\n";
    }
    else if(statincome > statexpense){
        fout << "You have a net profit of $" << setprecision(8) << statincome - statexpense << " in " << todaymonth << ".\n";
    }
    else{
        fout << "You are even this month.\n";
    }
    fout.close();
}

void writecredit(string todaymonth, double creditlim, struct record records[]){
    ofstream fout;
    double totalcred = calcre(todaymonth, records);
    string filename = todaymonth + "stat.txt";
    fout.open(filename, ios::app);
    fout << "Your credit spending is " << totalcred/creditlim * 100 << "% of your credit limit in " << todaymonth << "." << endl;
    fout << "***************************************************************************\n";
    fout.close();
}

void writeaccount(string todaymonth, double Bankin, double Bankout, double Cashin, double Cashout, double Credit, double Otherin, double Otherout){
    ofstream fout;
    string filename = todaymonth + "stat.txt";
    fout.open(filename, ios::app);
    fout << "***************************************************************************\n";
    fout << setw(19) << "Bank" << setw(16) << "Cash" << setw(22) << "Credit Card" << setw(19) << "Others\n";
    fout << "Income:     " << setw(7) << Bankin;
    fout << setw(16) << Cashin << setw(40) << Otherin << endl;
    fout << "Expenses:   " << setw(7) << Bankout;
    fout << setw(16) << Cashout << setw(22) << Credit << setw(18) << Otherout << endl;
    fout << "\n";
    fout.close();
}



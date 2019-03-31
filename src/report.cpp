#include <iostream>
#include <fstream>
#include "class.h"
#include "database.h"
#include <iomanip>
using namespace std;

double calexpense(string reportmonth){
    ifstream fin(reportmonth + ".txt");
    string line;
    record record;
    double totalexpense = 0;
    while (getline(fin, line)){
        record = stringtoRecord(line);
        if (record.getType() == "E"){totalexpense += record.getAmount();}
    }
    fin.close();
    return totalexpense;
}

double calincome(string reportmonth){
    ifstream fin(reportmonth + ".txt");
    string line;
    record record;
    double totalincome = 0;
    while (getline(fin, line)){
        record = stringtoRecord(line);
        if (record.getType() == "R"){totalincome += record.getAmount();}
    }
    fin.close();
    return totalincome;
}

void writereport(string reportmonth, double entertainments, double food, double bill, double transports, double otherin, double otherex, double credit, double cash, double bank){
    double budget, creditlim;
    ifstream getbud(reportmonth + "budget.txt");
    getbud >> budget >> creditlim;
    getbud.close();

    ofstream fout(reportmonth + "report.txt");
    double totalexpense = calexpense(reportmonth);
    double totalincome = calincome(reportmonth);
    fout << "Statistical report for " << reportmonth << setw(39) << "||";
    fout << "Budget :" << budget << "   Credit limit: " << creditlim << "||" << endl;

    fout << setprecision(2) << fixed;
    fout << "Entertainments: " << setw(20) << entertainments << setw(20) << (entertainments/totalexpense)*100 << "%" << endl;
    fout << "          Food: " << setw(20) << food << setw(20) << (food/totalexpense)*100 << "%" << endl;
    fout << "    Transports: " << setw(20) << transports << setw(20) << (transports/totalexpense) *100 << "%" << endl;
    fout << "          Bill: " << setw(20) << bill << setw(20) << (bill/totalexpense) *100 << "%" << endl;
    fout << "        Others: " << setw(20) << otherex << setw(20) << (otherex/totalexpense) *100 << "%" << endl;
    fout << "*********************************************************************************************************\n";
    fout << "Credited expense: " << setw(18) << credit << setw(10) << "||" <<  (credit/totalexpense) *100 << "% of total expense||" << credit/creditlim *100 << "% of credit limit||" << endl;
    fout << "Total expenses: " << setw(20) << totalexpense << setw(10) << "||" << totalexpense/budget *100 << "% of budget||" << endl;
    fout << "Total income:   " << setw(20) << totalincome << "        ||";

    if (totalexpense > totalincome){fout << "Loss of " << totalexpense-totalincome << " for " << reportmonth << "||" << endl;}
    else if(totalincome > totalexpense){ fout << "Profit of " << totalincome - totalexpense << " for " << reportmonth << "||" << endl;}
    else{fout << "Even for " << reportmonth << "||" << endl;}
    fout << "*********************************************************************************************************\n";

    fout.close();
}

void report(string reportmonth){
    ifstream fin(reportmonth + ".txt");
    string line;
    record record;
    double entertainments(0), food(0), bill(0), transports(0), otherin(0), otherex(0), credit(0), cash(0), bank(0);
    while (getline(fin, line)){
        record = stringtoRecord(line);
        if (record.getUsage() == "Entertainments"){entertainments += record.getAmount();}
        else if(record.getUsage() == "Food"){food += record.getAmount();}
        else if(record.getUsage() == "Transports"){transports += record.getAmount();}
        else if(record.getUsage() == "Bill"){bill += record.getAmount();}
        else if((record.getUsage() == "Others")){
            if (record.getType()== "R"){
                otherin += record.getAmount();
            }
            else{
                otherex += record.getAmount();
            }
        }

        if (record.getAccount() == "Cash"){cash += record.getAmount();}
        else if(record.getAccount() == "Bank"){bank += record.getAmount();}
        else if(record.getAccount() == "Card"){credit += record.getAmount();}
    }
    fin.close();
    writereport(reportmonth, entertainments, food, bill, transports, otherin, otherex, credit, cash, bank);
}



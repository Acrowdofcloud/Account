#include <iostream>
#include <fstream>
#include "class.h"
#include "database.h"
#include <iomanip>
using namespace std;

double calexpense(string reportmonth){//calculate and return the total of all the expenses for the month
    ifstream fin(reportmonth + ".txt");
    string line;
    record record;
    double totalexpense = 0;
    while (getline(fin, line)){
        record = stringtoRecord(line);//get records from file
        if (record.getType() == "E"){totalexpense += record.getAmount();}//add to totalexpense if the record is an expense
    }
    fin.close();
    return totalexpense;
}

double calincome(string reportmonth){//calculate and return the total of all the incomes for the month
    ifstream fin(reportmonth + ".txt");
    string line;
    record record;
    double totalincome = 0;
    while (getline(fin, line)){//get records from file
        record = stringtoRecord(line);
        if (record.getType() == "R"){totalincome += record.getAmount();}//add to totalincome if the record is an income
    }
    fin.close();
    return totalincome;
}

//write the report to a file
void writereport(string reportmonth, double entertainments, double food, double bill, double transports, double otherin, double otherex, double salary, double credit){
    double budget, creditlim;
    ifstream getbud(reportmonth + "budget.txt");//get the monthly budget and credit limit
    getbud >> budget >> creditlim;
    getbud.close();

    ofstream fout(reportmonth + "report.txt");
    fout << "*********************************************************************************************************\n";
    double totalexpense = calexpense(reportmonth);//get total expense
    double totalincome = calincome(reportmonth);//get total income
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
    fout << "Total income:   " << setw(20) << totalincome << "        ||Salary: " << salary << "||Others: " << otherin << endl;
    //tell user if there is a loss or profit for the month
    if (totalexpense > totalincome){fout << "Loss of " << totalexpense-totalincome << " for " << reportmonth << endl;}
    else if(totalincome > totalexpense){ fout << "Profit of " << totalincome - totalexpense << " for " << reportmonth << endl;}
    else{fout << "Even for " << reportmonth << endl;}
    fout << "**********************************************End of Report**********************************************\n";

    fout.close();
}

void report(string reportmonth){
    ifstream fin(reportmonth + ".txt");
    string line;
    record record;
    double salary(0), entertainments(0), food(0), bill(0), transports(0), otherin(0), otherex(0), credit(0);
    //calculate the corresponding total for the five types of expenses
    //calculate the corresponding total for the two types of income
    while (getline(fin, line)){
        record = stringtoRecord(line);
        if (record.getUsage() == "Entertainments"){entertainments += record.getAmount();}
        else if(record.getUsage() == "Food"){food += record.getAmount();}
        else if(record.getUsage() == "Transports"){transports += record.getAmount();}
        else if(record.getUsage() == "Bill"){bill += record.getAmount();}
        else if(record.getUsage() == "Salary"){salary += record.getAmount();}
        else if((record.getUsage() == "Others")){
            if (record.getType()== "R"){
                otherin += record.getAmount();
            }
            else{
                otherex += record.getAmount();
            }
        }
        //get corresponding total for the three account
        if(record.getAccount() == "Card"){credit += record.getAmount();}
    }
    fin.close();
    //write report with the corresponding total of the types of expense, income and account
    writereport(reportmonth, entertainments, food, bill, transports, otherin, otherex, salary, credit);
}



#include <iostream>
#include <fstream>
#include <string>
#include "getdate.h"
#include "recordmanip.h"
#include "alarm.h"
#include "addrecords.h"
#include "filemanip.h"
#include "report.h"
#include "structs.h"

using namespace std;

int main(){
    string todaydate = gettime();
    string todaymonth = getmonth();
	double budget{ 0 };
	double creditlim = 0;
    int command, x, index = 0;
    ifstream fin;
    ofstream fout;
    struct record monthrecords[2000] = {};
    string filename = todaymonth + ".txt";

    fin.open(filename);
    if (fin.fail()){
        fout.open(filename);
        fout.close();
        system(("sort " + filename + " >> " + todaymonth + "sorted.txt").c_str());
        fin.close();
    }
    fin.close();

    fin.open((todaymonth + "sorted.txt"));
    while (fin >> monthrecords[index].date >> monthrecords[index].account >> monthrecords[index].type >> monthrecords[index].usage >> monthrecords[index].amount >> monthrecords[index].notes){
        monthrecords[index].exist = true;
        index++;
    }
    fin.close();

    fin.open(todaymonth + "budget.txt");
    if (fin.fail()){
        fout.open(todaymonth + "budget.txt");
        fout << "0\n0";
        fout.close();
    }
    fin >> budget >> creditlim;
    fin.close();

    fin.open(todaymonth + "stat.txt");
    if (fin.fail()){
        fout.open(todaymonth + "stat.txt");
        fout.close();
        fin.close();
    }
    fin.close();

    if (budget == 0){
        printf("What is your budget for %6s?\n", todaymonth.c_str());
        cin >> budget;
        fout.open(todaymonth + "budget.txt");
        fout << budget;
        fout.close();
    }
    if (creditlim == 0){
        printf("What is your credit limit for %6s?\n", todaymonth.c_str());
        cin >> creditlim;
        fout.open(todaymonth + "budget.txt", ios::app);
        fout << "\n" << creditlim;
        fout.close();
    }

    printallrecords(todaymonth, monthrecords);

    while (true){
        for (int i = 0; i < 2000; i++){
            if (!monthrecords[i].exist){
                x = i;
                break;
            }
        }

        report(todaymonth, creditlim, budget, monthrecords);
        cout << "What do you want to do?\n";
        cout << "0. Exit\n";
        cout << "1. Display records   2. New Expense           3. New Income\n";
        cout << "4. Edit Records      5. Delete Record         6. Statistic report" << endl;
        cout << "7. Change budget     8. Change Credit limit   9. Change month" << endl;
        cout << "***************************************************************************\n";
        cin >> command;

        if (command == 0){
            break;
        }
        else if (command == 1){
            printallrecords(todaymonth, monthrecords);
            alarm(todaymonth, creditlim, budget, monthrecords);
        }
        else if(command == 2){
            addexpense(todaymonth, todaydate, monthrecords[x]);
            printallrecords(todaymonth, monthrecords);
        }
        else if(command == 3){
            addincome(todaymonth, todaydate, monthrecords[x]);
            printallrecords(todaymonth, monthrecords);
        }
        else if(command == 4){
            int edit;
            printf("Which record?\t");
            printf("0. Return\n");
            printallrecords(todaymonth, monthrecords);
            cin >> edit;
            if (edit != 0){
               editrecord(monthrecords[edit-1]);
            }
            printallrecords(todaymonth, monthrecords);
            alarm(todaymonth, creditlim, budget, monthrecords);
        }
        else if(command == 5){
            int del;
            printf("Which record?\t");
            printf("0. Return\n");
            printallrecords(todaymonth, monthrecords);
            cin >> del;
            if (del != 0){
                deleterecord(monthrecords[del-1]);
            }
            printallrecords(todaymonth, monthrecords);
            alarm(todaymonth, creditlim, budget, monthrecords);
        }
        else if (command == 6){
            string outline;
            fin.open(todaymonth + "stat.txt");
            while (getline(fin, outline)){
                cout << outline << endl;
            }
        }
        else if(command == 7){
            printf("Old budget: %.0f\n", budget);
            printf("New budget: ");
            cin >> budget;
            fout.open("budget.txt");
            fout << budget << endl;
            fout << creditlim;
            fout.close();
        }
        else if(command == 8){
            printf("Old Credit Limit: %.0f\n", creditlim);
            printf("New Credit Limit: ");
            cin >> creditlim;
            fout.open("budget.txt");
            fout << budget << endl;
            fout << creditlim;
            fout.close();
        }
        else if(command == 9){
            printf("Which month? (yyyymm)\n");
            cin >> todaymonth;
            fin.open(todaymonth + "sorted.txt");
            if (fin.fail()){
                cout << "No records for " << todaymonth << ".\n";
                todaymonth = getmonth();
            }
            else{
                index = 0;
                filename = todaymonth + ".txt";
                for (int i = 0; i<2000; i++){
                    monthrecords[i].exist = false;
                }
                while (fin >> monthrecords[index].date >> monthrecords[index].account >> monthrecords[index].type >> monthrecords[index].usage >> monthrecords[index].amount >> monthrecords[index].notes){
                    monthrecords[index].exist = true;
                    index++;
                }
            }
            fin.close();
            fin.open(todaymonth + "budget.txt");
            fin >> budget >> creditlim;
            fin.close();
            printallrecords(todaymonth, monthrecords);
        }


        writetorecord(todaymonth, filename, monthrecords);
        remove((todaymonth + "sorted.txt").c_str());
        system(("sort " + filename + " >> " + todaymonth + "sorted.txt").c_str());
    }
}

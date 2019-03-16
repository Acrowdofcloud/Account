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
    int command, x, index = 0;
    ifstream fin;
    ofstream fout;
    struct record monthrecords[2000] = {};
    string filename = todaymonth + ".txt";

    fin.open(filename);
    if (fin.fail()){
        system(("touch " + filename).c_str());
        system(("sort -k1 -k2 " + filename + " >> " + todaymonth + "sorted.txt").c_str());
        exit(1);
    }
    fin.close();

    fin.open((todaymonth + "sorted.txt"));
    while (fin >> monthrecords[index].date >> monthrecords[index].account >> monthrecords[index].type >> monthrecords[index].usage >> monthrecords[index].amount >> monthrecords[index].notes){
        monthrecords[index].exist = true;
        index++;
    }
    fin.close();

    fin.open("budget.txt");
    fin >> budget;
    fin.close();
    if (budget == 0){
        printf("What is your monthly budget?\n");
        cin >> budget;
        fout.open("budget.txt");
        fout << budget;
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

        cout << "What do you want to do?\n";
        cout << "0. Exit\n";
        cout << "1. Display records 2. New Expense      3. New Income       4. Edit Record\n";
        cout << "5. Delete Record   6. Statistic report 7. Change budget    8. Change month" << endl;
        cout << "***************************************************************************\n";
        cin >> command;

        if (command == 0){
            break;
        }
        else if (command == 1){
            printallrecords(todaymonth, monthrecords);
            alarm(todaymonth, budget, monthrecords);
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
            printf("Which record?\n");
            printallrecords(todaymonth, monthrecords);
            cin >> edit;
            editrecord(monthrecords[edit-1]);
            printallrecords(todaymonth, monthrecords);
        }
        else if(command == 5){
            int del;
            printf("Which record?\n");
            printallrecords(todaymonth, monthrecords);
            cin >> del;
            deleterecord(monthrecords[del-1]);
            printallrecords(todaymonth, monthrecords);
        }
        else if (command == 6){
            report(todaymonth, budget, monthrecords);
        }
        else if(command == 7){
            printf("New budget: ");
            cin >> budget;
            fout.open("budget.txt");
            fout << budget;
            fout.close();
        }
        else if(command == 8){
            printf("Which month? (yyyymm)\n");
            cin >> todaymonth;
            fin.open(todaymonth + "sorted.txt");
            if (fin.fail()){
                cout << "No records for " << todaymonth << ".\n";
                todaymonth = getmonth();
                exit(1);
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
            printallrecords(todaymonth, monthrecords);
        }


        writetorecord(todaymonth, filename, monthrecords);
        system(("rm " + todaymonth + "sorted.txt").c_str());
        system(("sort -k1 -k2 " + filename + " >> " + todaymonth + "sorted.txt").c_str());
    }
}

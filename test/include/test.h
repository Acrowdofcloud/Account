#pragma once
// ^^^ prevent redfining the same thing,
#include <string>

//width for each data in file
const int account_width{20};
const int amount_width{15};         //precision of double is 15 digits,so max width = 16
const int usage_width{20};
const int note_width{30};

class record {
public:
    record();

    std::string getDate() const;
    std::string getAccount() const;
    std::string getUsage() const;
    std::string getNote() const;
    double getAmount() const;
    std::string getType() const;
    int getLineNum() const;

    std::string setDate(std::string);
    std::string setAccount(std::string);
    std::string setAmount(std::string);
    std::string setUsage(std::string);
    std::string setNote(std::string);
    std::string setType(std::string);
    int setLineNum(int);

    void input(std::string);

    std::string toString() const;

private:
    std::string type;
    std::string date;
    std::string account;
    double amount;
    std::string usage;
    std::string note;
};

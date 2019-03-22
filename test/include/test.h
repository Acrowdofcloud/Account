#pragma once
// ^^^ prevent redfining the same thing,
#include <string>

const int account_width{20};        //width for each data in file
const int amount_width{15};
const int usage_width{20};
const int note_width{30};

class record {
public:
    std::string getDate() const;
    std::string getAccount() const;
    std::string getUsage() const;
    std::string getNote() const;
    double getAmount() const;
    char getType() const;

    std::string setDate(std::string);
    std::string setAccount(std::string);
    std::string setAmount(std::string);
    std::string setUsage(std::string);
    std::string setNote(std::string);
    std::string setType(char);

    std::string toString() const;
    void toRecord(std::string);

private:
    std::string date;
    std::string account;
    double amount;
    std::string usage;
    char type;
    std::string note;

};

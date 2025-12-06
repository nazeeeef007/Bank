#ifndef ADDUSEROP_H
#define ADDUSEROP_H 
#include "TransactionOp.h"
#include "Account.h"
#include "User.h"
#include <string>
#include "Bank.h"

class AddUserOp: public TransactionOp {
private:
    std::string name;
    int age;
    double balance;
public:

    AddUserOp(std::string name, int age, double balance)
        : name(std::move(name)), age(age), balance(balance) {}

    std::string getName() {
        return name;
    }
    int getAge() {
        return age;
    }
    double getBalance() {
        return balance;
    }

    void execute(Bank & bank) override {
        Account acc(balance);
        User user(name, age, acc);
        bank.addUser(user);
    };

};

#endif

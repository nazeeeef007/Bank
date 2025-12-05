#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <stdexcept>
#include <string> // If you planned to use std::string for errors/names
#include <unordered_map>
#include "Transaction.h"

class Account {
private:
    // NOTE: nextId MUST be defined in Account.cpp
    static int nextId; 
    double balance;
    int id;


public:
    // Constructors (using initializer lists)
    Account(double balance) : balance(balance), id(nextId++) {}
    Account() : balance(0.0), id(nextId++) {}
    
    // Core methods (made public)
    double withdraw(double amount);
    void deposit(double amount);

    // Getters (made const)
    double getBalance() const {
        return balance;
    }

    int getAccountId() const { // Return type corrected to int
        return id;
    }

    std::string print() {
        return "AccountId: " + std::to_string(id) + " Balance: " + std::to_string(balance);
    }

    // --- Custom Comparator Definition ---
    
    // 1. Overload the less-than operator (<)
    // This allows comparison syntax like: if (acc1 < acc2)
    // The comparison logic is: acc1 < acc2 if acc1 has LESS balance than acc2.
    // To sort by LARGER balance, we reverse the logic in the sorting context.
    // For general comparison, we stick to standard "less than".
    
    bool operator<(const Account& other) const {
        // Return true if THIS account's balance is strictly less than the OTHER account's balance.
        return this->balance < other.balance;
    }

    // 2. Overload the greater-than operator (>)
    // This allows comparison syntax like: if (acc1 > acc2)
    bool operator>(const Account& other) const {
        // Return true if THIS account's balance is strictly greater than the OTHER account's balance.
        return this->balance > other.balance;
    }

};

#endif // ACCOUNT_H
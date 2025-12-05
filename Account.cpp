#include "Account.h"
#include <iostream> // For demonstration, not strictly necessary

// Static member definition and initialization
int Account::nextId = 1;

double Account::withdraw(double amount) {
    if (amount > balance) {
        // Correct exception name used
        throw std::invalid_argument("Insufficient Balance!"); 
    }
    if (amount <= 0) {
        throw std::invalid_argument("Amount must be positive!");
    }
    balance -= amount;
    return amount;
}

void Account::deposit(double amount) {
    if (amount <= 0) {
        throw std::invalid_argument("Amount must be positive!");
    }
    balance += amount;
}



// Note: getBalance and getAccountId were defined inline in the header
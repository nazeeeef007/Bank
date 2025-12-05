#ifndef TRANSACTION_H
#define TRANSACTION_H 

// Include necessary standard libraries
#include <string>
#include <stdexcept> 

class Transaction {
private:
    // NOTE: nextId MUST be defined in Transaction.cpp
    static int nextId;
    int id;
    int fromAccount;
    int toAccount;
    double amount;
    int date; // Assuming this is an integer representing a date (e.g., YYYYMMDD)
    int fromUser;
    int toUser;

public:
    // Constructors (using initializer lists)
    Transaction(int fromUser, int toUser, int fromAccount, int toAccount, double amount, int date) 
        : fromUser(fromUser), toUser(toUser), fromAccount(fromAccount), toAccount(toAccount), amount(amount), date(date), id(nextId++) {}

    Transaction() 
        : fromUser(0), toUser(0), fromAccount(0), toAccount(0), amount(0), date(0), id(nextId++) {}

    // Getters (made const-correct)
    int getFromAccount() const { return fromAccount; }
    int getToAccount() const { return toAccount; }
    double getAmount() const { return amount; }
    int getId() const { return id; }
    int getDate() const { return date; }
    int getFromUser() const {return fromUser;}
    int getToUser() const {return toUser;}

    // Optional: Default operator< for generic sorting (e.g., by ID)
    bool operator<(const Transaction & t) const {
        return this->id < t.id;
    }

    bool operator==(const Transaction & t) const {
        return this->id == t.id;
    }
    
    // NOTE: Removed the conflicting operator> and operator< definitions
};


// --- CUSTOM COMPARATOR FUNCTORS ---

// 1. Comparator for sorting by amount (Largest to Smallest)
struct CompareByAmountDesc {
    // The operator() takes two Transaction objects and returns a bool.
    // std::sort needs it to return true if 'a' should come before 'b'.
    bool operator()(const Transaction& a, const Transaction& b) const {
        // We want the LARGER amount first, so we define 'a' < 'b' if a.amount > b.amount
        return a.getAmount() > b.getAmount(); 
    }
};

// 2. Comparator for sorting by date (Oldest to Newest)
struct CompareByDateAsc {
    bool operator()(const Transaction& a, const Transaction& b) const {
        // We want the SMALLER/Older date first, so we use standard less-than logic.
        return a.getDate() < b.getDate(); 
    }
};

#endif // TRANSACTION_H
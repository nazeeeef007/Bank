#ifndef USER_H
#define USER_H

#include <string.h>
#include "Account.h"
#include <unordered_map>

class User {
    private:
        static int nextId;
        std::string name;
        int age;
        int id;
        std::unordered_map<int, Account> accounts;

    
    public:
        
        User(std::string name, int age, Account account) {
            this->name = name;
            this->age = age;
            if (age < 0) {
                throw std::invalid_argument("Age cannot be negative!");
            }
            this->accounts.emplace(account.getAccountId(), account);
            this->id = nextId++;
        }

        User() {
            this->name = "Tania";
            this->age = 25;
            this->accounts.clear();
            this->id = nextId++;
        }

        int getId() const {
            return id;
        }

        int getAge() const {
            return age;
        }

        Account& getAccount(int id) {
            if (accounts.find(id) == accounts.end()) {
                throw std::invalid_argument("User " + std::to_string(this->id) + "does not have Account " + std::to_string(id));
            }
            return accounts.at(id);
        }

        void addAccount(Account account) {
            int accountId = account.getAccountId();
            if (accounts.find(accountId) == accounts.end()) {
                accounts.emplace(accountId, account);
                // accounts[accountId] = account;
            }
        }

        void deposit(double amount, int accountId) {
            
            Account & acc = getAccount(accountId);
            acc.deposit(amount);
            
           
        }

        void withdraw(double amount, int accountId) {
            
            Account & acc = getAccount(accountId);
            acc.withdraw(amount);
            
        }

        std::string getName() {
            return name;
        }

        void setAge (int age) {
            if (age < 0) {
                throw std::invalid_argument("Age cannot be negative!");
            }
            this->age = age;
        }

        void setName(std::string name) {
            this->name = name;
        } 

        std::string print() {
            return "Name: " + name + " Age: " + std::to_string(age);
        }


};

#endif
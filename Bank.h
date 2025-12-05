#ifndef BANK_H
#define BANK_H

#include <unordered_map>
#include <queue>
#include <memory>
#include "User.h"
#include "Transaction.h"
#include "Task.h"
#include "TransactionOp.h"

class Bank {
    private:
        std::unordered_map<int, User> users;
        // Queue of generic transaction operations wrapped in Tasks
        std::queue<Task<std::unique_ptr<TransactionOp>>> taskQueue;
        int queueSize;
    public:

        Bank(int queueSize){
            this->queueSize = queueSize;
        }

        Bank() = default;
        void enqueueTask(int startTime, int duration, std::unique_ptr<TransactionOp> op) {
            if (static_cast<int>(taskQueue.size()) >= queueSize) {
                throw std::runtime_error("Task queue is full");
            }
            taskQueue.emplace(startTime, duration, std::move(op));
        }

        void processNextTask() {
            if (taskQueue.empty()) {
                return;
            }
            Task<std::unique_ptr<TransactionOp>>& task = taskQueue.front();
            task.execute(*this);
            taskQueue.pop();
        }

        void processTransaction(const Transaction & t) {
            int toUserId = t.getToUser();
            int fromUserId = t.getFromUser();
            int toAccountId = t.getToAccount();
            int fromAccountId = t.getFromAccount();
            double amount = t.getAmount();
            if (users.find(fromUserId) == users.end()) {
                throw std::invalid_argument("The sender doesn't exist!");
            }
            if (users.find(toUserId) == users.end()) {
                throw std::invalid_argument("The recipient doesn't exist!");
            }
            
            User toUser = users.at(toUserId);
            User fromUser = users.at(fromUserId);
            try {
                fromUser.withdraw(fromAccountId, amount);
                toUser.deposit(toAccountId, amount);
            }
            catch (std::invalid_argument e){
                e.what();
            }
        }

        // this is not a good implementation imo, u can easily add in users that dont have accounts already i think?
        void addUser(const User & newUser) {
            users.emplace(newUser.getId(), newUser) ;
            // users[newUser.getId()] = newUser; this is bad, well not really bad 
            // but it causes our static int nextId of the user class to increment by 2 , so our userIds will only be odd 
            // eg 1 3 5 7, the reason is because, eg we do  bank.addUser(User("tania",25,40)), this User(...) constructor is called

        }

        User getUser(int userId) {
            if (users.find(userId) == users.end()) {
                throw std::invalid_argument("User doesn't exist!");
            }
            return users.at(userId);
        }





};

#endif 

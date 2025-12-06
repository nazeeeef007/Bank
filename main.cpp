#include "Account.h"
#include "User.h"
#include "Transaction.h"
#include "Bank.h"
#include "DepositOp.h"
#include "WithdrawOp.h"
#include "AddUserOp.h"
#include <iostream>
#include <memory>
#include <random>

int main() {
    // Create a bank with a queue capacity big enough for our simulation
    Bank bank(100);

    try {
        // Set up some initial users and accounts
        Account a1(1000.0);
        Account a2(500.0);
        Account a3(2000.0);

        User u1("Tania", 25, a1);
        User u2("James", 27, a2);
        User u3("Lee", 19, a3);

        bank.addUser(u1);
        bank.addUser(u2);
        bank.addUser(u3);

        std::cout << "Initial users created:\n";
        std::cout << "User " << u1.getId() << " account " << a1.getAccountId() << " balance " << a1.getBalance() << "\n";
        std::cout << "User " << u2.getId() << " account " << a2.getAccountId() << " balance " << a2.getBalance() << "\n";
        std::cout << "User " << u3.getId() << " account " << a3.getAccountId() << " balance " << a3.getBalance() << "\n\n";

        // Random duration generator in [1, 10]
        std::mt19937 rng(42); // fixed seed for reproducibility
        std::uniform_int_distribution<int> durationDist(1, 10);

        int currentTime = 0;
        int totalTasks = 0;

        // Enqueue a series of deposit, withdraw and add-user tasks
        auto enqueueDeposit = [&](int userId, int accountId, double amount) {
            int duration = durationDist(rng);
            auto op = std::make_unique<DepositOp>(userId, accountId, amount);
            bank.enqueueTask(currentTime, duration, std::move(op));
            std::cout << "Enqueued DEPOSIT of " << amount
                      << " for user " << userId
                      << " account " << accountId
                      << " with duration " << duration
                      << " at time " << currentTime << "\n";
            currentTime += duration;
            ++totalTasks;
        };

        auto enqueueAddUser = [&](const std::string& name, int age, double amount) {
            int duration = durationDist(rng);
            auto op = std::make_unique<AddUserOp>(name, age, amount);
            bank.enqueueTask(currentTime, duration, std::move(op));
            std::cout << "Enqueued ADDUSER '" << name << "' age " << age
                      << " with initial balance " << amount
                      << " and duration " << duration
                      << " at time " << currentTime << "\n";
            currentTime += duration;
            ++totalTasks;
        };

        auto enqueueWithdraw = [&](int userId, int accountId, double amount) {
            int duration = durationDist(rng);
            auto op = std::make_unique<WithdrawOp>(userId, accountId, amount);
            bank.enqueueTask(currentTime, duration, std::move(op));
            std::cout << "Enqueued WITHDRAW of " << amount
                      << " for user " << userId
                      << " account " << accountId
                      << " with duration " << duration
                      << " at time " << currentTime << "\n";
            currentTime += duration;
            ++totalTasks;
        };

        // We know the first three accounts created have IDs 1, 2, 3
        int u1Id = u1.getId();
        int u2Id = u2.getId();
        int u3Id = u3.getId();
        int acc1Id = a1.getAccountId();
        int acc2Id = a2.getAccountId();
        int acc3Id = a3.getAccountId();

        // A few initial tasks
        enqueueDeposit(u1Id, acc1Id, 200.0);
        enqueueWithdraw(u2Id, acc2Id, 50.0);
        enqueueDeposit(u3Id, acc3Id, 1000.0);
        enqueueWithdraw(u1Id, acc1Id, 150.0);
        enqueueDeposit(u2Id, acc2Id, 75.0);
        enqueueWithdraw(u3Id, acc3Id, 300.0);

        // Additional deposits
        for (int i = 0; i < 15; ++i) {
            int userIdx = i % 3;
            int userId = (userIdx == 0) ? u1Id : (userIdx == 1 ? u2Id : u3Id);
            int accId  = (userIdx == 0) ? acc1Id : (userIdx == 1 ? acc2Id : acc3Id);
            double amount = 50.0 + 10.0 * i;
            enqueueDeposit(userId, accId, amount);
        }

        // Additional withdrawals
        for (int i = 0; i < 15; ++i) {
            int userIdx = i % 3;
            int userId = (userIdx == 0) ? u1Id : (userIdx == 1 ? u2Id : u3Id);
            int accId  = (userIdx == 0) ? acc1Id : (userIdx == 1 ? acc2Id : acc3Id);
            double amount = 20.0 + 5.0 * i;
            enqueueWithdraw(userId, accId, amount);
        }

        // Add a batch of new users
        for (int i = 0; i < 12; ++i) {
            std::string name = "User_" + std::to_string(i);
            int age = 18 + i;
            double initialBalance = 100.0 * (i + 1);
            enqueueAddUser(name, age, initialBalance);
        }

        // Intentionally problematic tasks to trigger errors
        enqueueDeposit(999, acc1Id, 100.0);          // invalid user id
        enqueueWithdraw(u2Id, 9999, 10.0);           // invalid account id
        enqueueDeposit(u1Id, acc1Id, -25.0);         // negative deposit amount
        enqueueWithdraw(u3Id, acc3Id, -10.0);        // negative withdraw amount
        enqueueWithdraw(u1Id, acc1Id, 1'000'000.0);  // withdraw more than balance
        enqueueAddUser("BadUser", -5, 500.0);        // invalid age for new user

        std::cout << "\nProcessing all " << totalTasks << " queued tasks by time...\n\n";

        int simulationTime = 0;
        while (bank.hasPendingTasks()) {
            std::cout << "== Simulation time " << simulationTime << " ==\n";
            bank.processReadyTasks(simulationTime);
            ++simulationTime;
        }

        std::cout << "\nSimulation complete at time " << simulationTime << ".\n";

    } catch (const std::invalid_argument& e) {
        std::cerr << "Caught Exception: " << e.what() << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "Caught Unexpected Exception: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Caught Unknown Exception." << std::endl;
        return 1;
    }

    return 0;
}

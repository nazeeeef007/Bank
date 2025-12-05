#include "Account.h"
#include "User.h"
#include "Transaction.h"
#include "Bank.h"
#include "DepositOp.h"
#include "WithdrawOp.h"
#include <iostream>
#include <memory>
#include <random>

int main() {
    // Create a bank with a queue capacity of 100 tasks
    Bank bank(3);

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

        // Enqueue a series of deposit and withdraw tasks
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
        };

        // We know the first three accounts created have IDs 1, 2, 3
        int u1Id = u1.getId();
        int u2Id = u2.getId();
        int u3Id = u3.getId();
        int acc1Id = a1.getAccountId();
        int acc2Id = a2.getAccountId();
        int acc3Id = a3.getAccountId();

        // Build a fixed simulation scenario
        enqueueDeposit(u1Id, acc1Id, 200.0);
        enqueueWithdraw(u2Id, acc2Id, 50.0);
        enqueueDeposit(u3Id, acc3Id, 1000.0);
        enqueueWithdraw(u1Id, acc1Id, 150.0);
        enqueueDeposit(u2Id, acc2Id, 75.0);
        enqueueWithdraw(u3Id, acc3Id, 300.0);

        std::cout << "\nProcessing all queued tasks...\n\n";

        // We enqueued 6 tasks above
        for (int i = 0; i < 6; ++i) {
            std::cout << "Processing task " << (i + 1) << "...\n";
            bank.processNextTask();
        }

        std::cout << "\nSimulation complete.\n";

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

#ifndef TRANSACTIONOP_H
#define TRANSACTIONOP_H

// Forward declaration to avoid circular include
class Bank;

// Abstract base class for all bank operations that can be queued
class TransactionOp {
public:
    virtual ~TransactionOp() = default;

    // Execute this operation against the given Bank
    virtual void execute(Bank& bank) = 0;
};

#endif // TRANSACTIONOP_H


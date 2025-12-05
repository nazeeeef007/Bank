// WithdrawOp.h
#ifndef WITHDRAWOP_H
#define WITHDRAWOP_H

#include "TransactionOp.h"

class WithdrawOp : public TransactionOp {
private:
    int userId;
    int accountId;
    double amount;

public:
    WithdrawOp(int userId, int accountId, double amount);

    int getUserId() const;
    int getAccountId() const;
    double getAmount() const;

    // Perform the withdraw using the Bank interface
    void execute(Bank& bank) override;
};

#endif // WITHDRAWOP_H

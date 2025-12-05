// DepositOp.h
#ifndef DEPOSITOP_H
#define DEPOSITOP_H

#include "TransactionOp.h"

class DepositOp : public TransactionOp {
private:
    int userId;
    int accountId;
    double amount;

public:
    DepositOp(int userId, int accountId, double amount);

    int getUserId() const;
    int getAccountId() const;
    double getAmount() const;

    // Perform the deposit using the Bank interface
    void execute(Bank& bank) override;
};

#endif // DEPOSITOP_H

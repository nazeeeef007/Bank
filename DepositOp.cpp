// DepositOp.cpp
#include "DepositOp.h"
#include "Bank.h"
#include "User.h"

DepositOp::DepositOp(int userId, int accountId, double amount)
    : userId(userId), accountId(accountId), amount(amount) {}

int DepositOp::getUserId() const {
    return userId;
}

int DepositOp::getAccountId() const {
    return accountId;
}

double DepositOp::getAmount() const {
    return amount;
}

void DepositOp::execute(Bank& bank) {
    // Uses existing Bank/User APIs; exceptions propagate if something is invalid
    User user = bank.getUser(userId);
    user.deposit(amount, accountId);
}

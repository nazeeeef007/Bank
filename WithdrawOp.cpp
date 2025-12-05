// WithdrawOp.cpp
#include "WithdrawOp.h"
#include "Bank.h"
#include "User.h"

WithdrawOp::WithdrawOp(int userId, int accountId, double amount)
    : userId(userId), accountId(accountId), amount(amount) {}

int WithdrawOp::getUserId() const {
    return userId;
}

int WithdrawOp::getAccountId() const {
    return accountId;
}

double WithdrawOp::getAmount() const {
    return amount;
}

void WithdrawOp::execute(Bank& bank) {
    // Uses existing Bank/User APIs; exceptions propagate if something is invalid
    User user = bank.getUser(userId);
    user.withdraw(amount, accountId);
}

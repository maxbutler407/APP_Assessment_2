#include "Current.h"

// initialisation
Current::Current(double o) : overdraft(o), Account(0, "Current") {
	//std::cout << "Current account constructor called\n";
}

// accessor gets the class' balance
float Current::getBalance() {
	return balance;
}

// withdraw logic for Current account
void Current::withdraw(int withdrawAmount) {
	// if the user wants to withdraw an amount that is greater than the available balance and overdraft - user is taken out of if statement
	if (withdrawAmount > balance + overdraft) {
		std::cout << "Account and overdraft balance do not have sufficient funds\n";
	}
	// if the user is requesting an amount that is available
	else {
		std::cout << "Withdrawing funds from your account...\n";
		// if the balance isn't enough, this logic will then deduct funds from the £500 overdraft
		if (withdrawAmount > balance) {
			std::cout << "Account does not have sufficient funds...withdrawing funds from overdraft balance...\n";

			// deducts from the balance first
			int remainingAmount = withdrawAmount - balance;
			balance = 0;

			// deducts the remaining from the overdraft
			overdraft -= remainingAmount;
			if (overdraft < 0) {
				std::cout << "Overdraft limit exceeded! Withdraw declined\n";
			}
		}
		// if there's enough in the balance
		else {
			balance -= withdrawAmount;
		}
	}
}

// deposit logic for Current account
void Current::deposit(int depositAmount) {
	// increases balance by the user's deposit amount
	balance += depositAmount;
	std::cout << "Successfully deposited \x9C" << depositAmount << "\n";
}

void Current::computeInterest(double balance, float interestRate, int timeSpan) {}

float Current::getInterestRate(float interestRate) {
	return interestRate;
}

// destructor
Current::~Current() {
	//std::cout << "Current Account destructor called\n";
}
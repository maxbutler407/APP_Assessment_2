#include "Savings.h"

// initialisation
Savings::Savings(float iR, bool i) : interestRate(iR), isa(i), Account(0, "Savings") {
	//std::cout << "Savings account constructor called\n";
}

// withdraw logic for Savings account
void Savings::withdraw(int withdrawAmount) {
	if (withdrawAmount > balance) {
		std::cout << "Account does not have sufficient funds\n";
	}
	// deducts balance if account has sufficient funds
	else {
		balance -= withdrawAmount;
	}
}

// deposit logic for Savings account
void Savings::deposit(int depositAmount) {
	// increases balance by the requested deposit amount
	balance += depositAmount;
	std::cout << "Successfully deposited \x9C" << depositAmount << "\n";
}

// calculates the compound interest from argument list
void Savings::computeInterest(double balance, float interestRate, int timeSpan) {
	// uses formula given in brief - I converted it into multiple steps for easier understanding
	double adjustedIR = interestRate / 100; // need to adjust the interest rate to output correct computed interest
	double monthly1 = 1 + (adjustedIR / 12);
	double monthly2 = pow(monthly1, 12 * timeSpan);
	double monthly3 = balance * monthly2;
	std::cout << "Calculated interested over a " << timeSpan << " year period: " << monthly3 << "\n";
}

// accessor gets the class' balance
float Savings::getBalance() {
	return balance;
}

// accessor gets the class' interest rate
float Savings::getInterestRate(float interestRate) {
	return interestRate;
}

// destructor
Savings::~Savings() {
	//std::cout << "Savings Account destructor called\n";
}
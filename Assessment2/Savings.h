#ifndef SAVINGS_H
#define SAVINGS_H

#include "Account.h"
#include "InterestEarning.h"

class Savings : public Account, public InterestEarning {
private: // private offers greater encapsulation
	float interestRate;
	bool isa;

public:
	// constructor initialises Savings vars
	Savings(float iR, bool i);

	// Overrides the virtual functions of abstract Account class
	void withdraw(int withdrawAmount) override;
	void deposit(int depositAmount) override;
	void computeInterest(double balance, float interestRate, int timeSpan) override;
	float getBalance() override;
	float getInterestRate(float interestRate) override;

	// Savings destructor
	~Savings();
};

#endif

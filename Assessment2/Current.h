#ifndef CURRENT_H
#define CURRENT_H

#include "Account.h"
#include "InterestEarning.h"

class Current : public Account {
private: // private offers encapsulation by 'hiding' this var
	double overdraft;

public:
	// current account is initialised with a minimum overdraft of £500
	Current(double o = 500);

	// Overrides the virtual functions of abstract Account class
	float getBalance() override;
	void withdraw(int withdrawAmount) override;
	void deposit(int depositAmount) override;
	void computeInterest(double balance, float interestRate, int timeSpan) override;
	float getInterestRate(float interestRate) override;

	// Current destructor
	~Current();
};

#endif
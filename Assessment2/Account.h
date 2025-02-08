#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "InterestEarning.h"

#include <iostream>
#include <cmath>

// Blueprint for other classes. Must not be instantiated. Derived classes must provide an implementation for the following v functions to be instantiable themselves.
class Account : public InterestEarning {

protected: // protected allows this class and derived classes access to the vars
	float balance;
	std::string history;

public:
	// constructor used to initiliase vars (as we already know what the vars are)
	Account(int b = 0, std::string h = "No current history for this account");

	// this is an abstract class - all methods must be pure virtual functions
	virtual float getBalance() = 0;
	virtual void withdraw(int withdrawAmount) = 0;
	virtual void deposit(int depositAmount) = 0;

	// Account destructor
	virtual ~Account();
};

#endif
#ifndef INTERESTEARNING_H
#define INTERESTEARNING_H

#include <iostream>

class InterestEarning {
public:
	// only pure virtual functions are used
	virtual void computeInterest(double balance, float interestRate, int timeSpan) = 0;
	virtual float getInterestRate(float interestRate) = 0;

	// AccountEarning destructor
	virtual ~InterestEarning();
};

#endif

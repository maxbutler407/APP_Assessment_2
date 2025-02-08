#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <iostream>
#include <vector>
#include <map>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

class Transaction {
private: // private offers greater encapsulation
	std::string desc;
	double value;
	time_t timestamp; // set as time_t type to ensure the value doesn't get altered in any way
public:

	// constructor used to initialise vars
	Transaction(std::string d = "", double v = 0.0, double t = 0.0);

	// getters
	std::string getDesc();
	double getValue();
	std::string getTimestamp();
	void setTimestamp(time_t t);

	// Transaction destructor
	~Transaction();
};

#endif

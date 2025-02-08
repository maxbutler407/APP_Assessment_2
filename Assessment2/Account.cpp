#include "Account.h"

// initialisation
Account::Account(int b, std::string h) : balance(b), history(h) {}

// destructor
Account::~Account() {
	//std::cout << "Account destructor called\n";
}
#include "Transaction.h"

// initialisation
Transaction::Transaction(std::string d, double v, double t) : desc(d), value(v), timestamp(t) {
    // records the current time
    auto now = std::chrono::system_clock::now();
    timestamp = std::chrono::system_clock::to_time_t(now);
    //std::cout << "Transaction constructor called\nTimestamp recorded\n";
}

// accessor gets the transaction description
std::string Transaction::getDesc() {
	return desc;
}

// accessor gets the transaction value
double Transaction::getValue() {
	return value;
}

// accessor calculates the transaction timestamp
std::string Transaction::getTimestamp() {

    // converts time_t to tm for local time 
    std::tm localTime;
    localtime_s(&localTime, &timestamp); // taken as reference to avoid copying

    // formats the timestamp into a string (year-month-day, hour-minute-second)
    std::ostringstream oss;
    oss << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S") << "\n";
    return oss.str();
}

void Transaction::setTimestamp(time_t t) {
    t = timestamp;
}

// destructor
Transaction::~Transaction() {
	//std::cout << "Transaction destructor called\n";
}
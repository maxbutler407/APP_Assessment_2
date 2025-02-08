/* ------------------------------------------------------
CMP2811: Applied Programming Paradigms
Driver program for "LincBank" Assessment Item 2
Semester A 2024

During marking, we will use the exact same notation
as provided in the brief, so make sure you follow that guideline.

You should avoid removing parts of this driver program, but
add to it the necessary code to produce your implementation.

Good luck!
------------------------------------------------------ */
#define _CRT_SECURE_NO_WARNINGS

// no "#include" need to be included here (the directives are included in header files)

// class header files
#include "Account.h"
#include "Current.h"
#include "Transaction.h"
#include "Savings.h"
#include "InterestEarning.h"

// method simply displays the command options for the user
void displayOptions() {
	std::cout << "~~~ Welcome to LincBank! ~~~" << "\n\n";
	std::cout << "You can call the following commands for your bank accounts: " << "\n";
	std::cout << "open: Open a new bank account" << "\n";
	std::cout << "view: View an account's balance and recent transactions" << "\n";
	std::cout << "withdraw: Withdraw funds from an account" << "\n";
	std::cout << "deposit: Deposit funds into an account" << "\n";
	std::cout << "transfer: Transfer funds between accounts" << "\n";
	std::cout << "project: Project the interest earned on a savings account for a given period (in years)" << "\n";
	std::cout << "search: Show records of all transactions" << "\n";
}

// method simply displays each account - this is used repeatedly (better readability)
void displayAccountOptions() {
	std::cout << "1. Current Account\n";
	std::cout << "2. Regular Savings Account\n";
	std::cout << "3. ISA Savings Account\n";
	std::cout << ">>> ";
}

// method deals with how much the user wants to withdraw and with what description
void askWithdraw(double& withdrawAmount, std::string& withdrawDesc) {
	std::cout << "How much would you like to withdraw?\n>>> ";
	std::cin >> withdrawAmount;
	std::cout << "Withdrawing \x9C" << withdrawAmount << "...\n";
	std::cout << "Please add a description for this withdrawal\n>>> ";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // will read spaces too that the user inputs
	std::getline(std::cin, withdrawDesc);
	std::cout << "Withdrawal description: " << withdrawDesc << "\n";
}

// method deals with how much the user wnats to deposit and with what what description
void askDeposit(double& depositAmount, std::string& depositDesc) {
	std::cout << "How much would you like to deposit?\n>>> ";
	std::cin >> depositAmount;
	std::cout << "Depositing \x9C" << depositAmount << "...\n";
	std::cout << "Please add a description for this deposit\n>>> ";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // will read spaces too that the user inputs
	std::getline(std::cin, depositDesc);
	std::cout << "Deposit description: " << depositDesc << "\n";
}

// method deals with how much the user wants to transfer (involves a withdrawal and deposit)
void askTransfer(int& from, int& to, double& transferAmount) {
	std::cout << "Which account would you like to transfer from?\n";
	displayAccountOptions();
	std::cin >> from;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear newline left by std::cin
	std::cout << "Which account would you like to transfer to?\n";
	displayAccountOptions();
	std::cin >> to;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear newline left by std::cin
	std::cout << "How much would you like to transfer?\n";
	std::cin >> transferAmount;
}

// adds each transaction to the history map with its own description, value and timestamp
void addTransaction(int& transactionID, std::map<int, Transaction*>& history, std::string& desc, double& value) {

	// creates a Transaction object based on user input and adds it to the history map with a unique ID
	Transaction* newTransaction = new Transaction(desc, value);

	// gets the current time as time_t
	auto currentTime = std::chrono::system_clock::now();
	std::time_t now_time = std::chrono::system_clock::to_time_t(currentTime);

	// sets the timestamp for this transaction
	newTransaction->setTimestamp(now_time);

	// increments and stores the transactionID of this transaction
	history[transactionID] = newTransaction;
	transactionID++;
}

// method displays each Regular Savings account that's in the opened accounts map
void showOpenedAccounts(std::map<int, Savings*>& openedAccounts) {
	for (auto& pair : openedAccounts) {
		std::cout << "Account ID: " << pair.first << "\n";
		std::cout << "Account Type: Regular Savings\n";
		std::cout << "Balance: \x9C" << pair.second->getBalance() << "\n";
		std::cout << "Interest Rate: 0.85%\n";
	}
}

// method holds the logic for transferring funds between every account type
void transferTo(int& to, Account* current, Account* isa, double& transferAmount, std::string& transferDesc, std::map<int, Savings*>& openedAccounts) {
	// switch statement deals with inputted 1, 2, or 3 (that decides on which account type is being deposited into)
	switch (to) {
	case 1:
		// deposits into current account if it exists
		if (current) {
			current->deposit(transferAmount);
		}
		else {
			std::cout << "Current account does not exist.\n";
		}
		break;
	case 2:
		// asks user which regular savings account is to be deposited into
		int savingsChoice;
		std::cout << "Which regular savings account would you like to transfer to?\n";
		showOpenedAccounts(openedAccounts);
		std::cout << ">>> ";
		std::cin >> savingsChoice;

		// prints out each regular savers account
		for (auto& pair : openedAccounts) {
			if (savingsChoice == pair.first) {
				pair.second->deposit(transferAmount);
				std::cout << "Account ID: " << pair.first << "\n";
				std::cout << "Account Type: Regular Savings\n";
				std::cout << "Balance: " << pair.second->getBalance() << "\n";
			}
		}
		break;
	case 3:
		// deposits into ISA account if it exists
		if (isa) {
			isa->deposit(transferAmount);
		}
		else {
			std::cout << "ISA account does not exist.\n";
		}
		break;
	default:
		std::cout << "Please enter either 1, 2 or 3\n";
		break;
	}
}

// prints out the transaction ID, description name, value and timestamp of each transaction stored in the history map
void showHistory(std::map<int, Transaction*>& history) {
	for (auto& pair : history) {
		std::cout << "Transaction ID: " << pair.first << "\tTransaction Description: " << pair.second->getDesc() << "\tTransaction Value: \x9C" << pair.second->getValue() << "\tTransaction Timestamp: " << pair.second->getTimestamp() << "\n";
	}
}

int main()
{
	// current and ISA are null pointer instantiations - the null pointer is used to detect whether they exist (nullptr is true if they don't exist)
	Account* current = nullptr;
	Account* isa = nullptr;

	// global declarations
	std::vector <std::string> parameters;
	std::string userCommand;

	// IDs will be incremented from 1 for easier readability
	int transactionID = 1;
	int accountID = 1;

	// records of withdrawals and deposits are stored in this "appropriate data structure" - pointer to Transaction objects ensures the actual address is altered throughout the programme
	std::map<int, Transaction*> history;

	// non-ISA savings accounts are stored in this map, each with a unique ID - pointer to Savings objects is also used here to avoid copies being made
	std::map<int, Savings*> openedAccounts;

	// calls method to display the options for the user
	displayOptions();

	while (userCommand != "exit")
	{
		parameters.clear(); // clear ready for next command
		std::cout << "Please enter a command:\n";
		std::cout << ">>> ";

		std::getline(std::cin, userCommand);
		char* cstr = new char[userCommand.length() + 1];
		strcpy(cstr, userCommand.c_str());

		char* token;
		token = strtok(cstr, " ");

		while (token != NULL)
		{
			parameters.push_back(token);
			token = strtok(NULL, " ");
		}

		// Define all commands as per the brief
		std::string command = parameters[0];

		// the following commands enable the user to open and make changes to their bank accounts
		if (command.compare("options") == 0)
		{
			// calls the method to display the options available to the user again
			displayOptions();
		}
		else if (command.compare("open") == 0)
		{
			// allow a user to open an account
			// e.g., Account* a = new Savings(...);
			// calls method to show the account options - takes in an integer (1-3) as input
			std::cout << "What type of account would you like to open?\n";
			displayAccountOptions();
			int option;
			std::cin >> option;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clears the newline left by std::cin

			// switch statement ensures only an int (1-3) is inputted
			switch (option) {
			case 1:
				// if statement ensures a maximum of 1 current account is opened
				if (current == nullptr) {
					current = new Current(500.00); // Current account is instantiated with a £500 overdraft available
					std::cout << "Current account successfully opened!\n";
				}
				else {
					std::cout << "You can only open 1 current account\n";
				}
				break;
			case 2:
			// use of {} to keep the assigning of "regular" within a specified scope
			{
				// no if statement required (as user can open as many regular savers accounts as they'd like)
				Savings* regular = new Savings(0.85, false); // each instantiation sets the interest rate to 0.85% and isa to false
				openedAccounts[accountID] = regular; // adds the instantiation to the openedAccounts map with a unique ID
				std::cout << "Regular savings account successfully opened with ID: " << accountID << "\n";
				accountID++; // incremented by 1 to ensure each opened account is unique
				break;
			}
			case 3:
				// if statament ensures a maximum of 1 ISA is opened
				if (isa == nullptr) {
					// user is asked to deposit a minimum of £1000 to open an ISA
					std::cout << "Please enter \x9C 1000 or more as a deposit, in order to open you ISA\n";
					std::cout << ">>> ";
					float isaDeposit;
					std::cin >> isaDeposit;
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clears the newline left by std::cin

					// if statement checks to see whether the deposit is sufficient to open an ISA
					if (isaDeposit >= 1000) {
						isa = new Savings(1.15, true); // this instantiation sets the interest rate to 1.15% and isa to true
						isa->deposit(isaDeposit); // deposits the initial amount into the created isa
						std::cout << "ISA account successfully opened!\n";
					}
					else {
						std::cout << "Please enter the minimum deposit as a number only\n";
					}
				}
				else {
					std::cout << "You can only open 1 ISA account\n";
				}
				break;
			default:
				std::cout << "Please enter either 1, 2 or 3\n";
			}
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // prevents programme from crashing at the end of this command section.
		}
		else if (command.compare("view") == 0)
		{
			// display an account according to an index (starting from 1)
			// alternatively, display all accounts if no index is provided
			// method displays every opened regular savers account
			showOpenedAccounts(openedAccounts);

			// this if logic checks to see whether the Current or ISA accounts exists and displays them (with detail) if they do
			if (isa != nullptr) {
				std::cout << "\nAccount Type: ISA Account\n";
				std::cout << "Balance: " << isa->getBalance() << "\n";
				std::cout << "Interest Rate: 1.15%\n";
			}
			if (current != nullptr) {
				std::cout << "Account Type: Current Account\n";
				std::cout << "Balance: " << current->getBalance() << "\n";
			}
		}
		else if (command.compare("withdraw") == 0)
		{
			// allow user to withdraw funds from an account
			// displays which accounts can be withdrawn from
			std::cout << "Which account would you like to withdraw from?\n";
			displayAccountOptions();

			int option;
			double withdrawAmount;
			std::string withdrawDesc;
			std::cin >> option;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			switch (option) {
			case 1:
				// if statement checks whether a current account has been opened
				if (current != nullptr) {

					// calls method to ask user which account is being withdrawn from
					askWithdraw(withdrawAmount, withdrawDesc);

					// withdraws the specified amount and displays the balance
					current->withdraw(withdrawAmount);
					current->getBalance();

					// adds transaction to history map
					addTransaction(transactionID, history, withdrawDesc, withdrawAmount);
				}
				else {
					std::cout << "You need to open a current account first!\n";
				}
				break;
			case 2:
				// if statement checks whether any regular savers have been opened
				if (!openedAccounts.empty()) {
					
					// asks user which account is being withdrawn from
					int savingsChoice;
					std::cout << "Which regular savings account would you like to withdraw from?\n";
					showOpenedAccounts(openedAccounts);
					std::cout << ">>> ";
					std::cin >> savingsChoice;

					// calls method to ask user the value and description of the withdrawal
					askWithdraw(withdrawAmount, withdrawDesc);

					// for and if find the correct account to withdraw from
					for (auto& pair : openedAccounts) {
						if (savingsChoice == pair.first) {

							// withdraws the specified amount and displays the balance
							pair.second->withdraw(withdrawAmount);
							std::cout << "Account ID: " << pair.first << "\n";
							std::cout << "Account Type: Regular Savings\n";
							std::cout << "Balance: " << pair.second->getBalance() << "\n";
						}
					}
					// adds transaction to history map
					addTransaction(transactionID, history, withdrawDesc, withdrawAmount);
				}
				else {
					std::cout << "You need to open a regular savings account first!\n";
				}
				break;
			case 3:
				// if statement checks to see if ISA exists
				if (isa != nullptr) {

					// calls method to ask user the value and description of the withdrawal
					askWithdraw(withdrawAmount, withdrawDesc);

					// withdraws the specified amount and displays the balance
					isa->withdraw(withdrawAmount);
					isa->getBalance();

					// adds transaction to history map
					addTransaction(transactionID, history, withdrawDesc, withdrawAmount);
				}
				else {
					std::cout << "You need to open an ISA account first!\n";
				}
				break;
			default:
				std::cout << "Please enter either 1, 2 or 3\n";
				break;
			}
		}
		else if (command.compare("deposit") == 0)
		{
			// allow user to deposit funds into an account
			// displays the accounts to which the user can deposit into
			std::cout << "Which account would you like to deposit into?\n";
			displayAccountOptions();

			int option;
			double depositAmount;
			std::string depositDesc;
			std::cin >> option;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			// switch ensures user inputs an integer (1-3)
			switch (option) {
			case 1:
				// if checks whether a current account exists
				if (current != nullptr) {

					// method asks user for deposit amount and description
					askDeposit(depositAmount, depositDesc);

					// the amount is deposited into the account and its new balance is displayed
					current->deposit(depositAmount);
					current->getBalance();

					// adds transaction to history map
					addTransaction(transactionID, history, depositDesc, depositAmount);
				}
				else {
					std::cout << "You need to open a current account first!\n";
				}
				break;
			case 2:
				// if checks whether a regualr savers account exists
				if (!openedAccounts.empty()) {

					// user is asked which regular savers they'd like to deposit into
					int savingsChoice;
					std::cout << "Which regular savings account would you like to deposit into?\n";
					showOpenedAccounts(openedAccounts);
					std::cout << ">>> ";
					std::cin >> savingsChoice;

					// method asks user for deposit amount and description
					askDeposit(depositAmount, depositDesc);

					// for and if findd the correct account to deposit into
					for (auto& pair : openedAccounts) {
						if (savingsChoice == pair.first) {

							// deposits the specified amount and displays the balance
							pair.second->deposit(depositAmount);
							std::cout << "Account ID: " << pair.first << "\n";
							std::cout << "Account Type: Regular Savings\n";
							std::cout << "Balance: " << pair.second->getBalance() << "\n";
						}
					}

					// adds transaction to history map
					addTransaction(transactionID, history, depositDesc, depositAmount);
				}
				else {
					std::cout << "You need to open a regular savings account first!\n";
				}
				break;
			case 3:
				// if checks whether an ISA account exists
				if (isa != nullptr) {

					// method asks user for deposit amount and description
					askDeposit(depositAmount, depositDesc);

					// the amount is deposited into the account and its new balance is displayed
					isa->deposit(depositAmount);
					isa->getBalance();

					// adds transaction to history map
					addTransaction(transactionID, history, depositDesc, depositAmount);

					for (auto& pair : history) {
						std::cout << "\nTransaction ID: " << pair.first << "\tDescription: " << pair.second->getDesc() << "\n";
					}
				}
				else {
					std::cout << "You need to open an ISA account first!\n";
				}
				break;
			default:
				std::cout << "Please enter either 1, 2 or 3\n";
				break;
			}
		}
		else if (command.compare("transfer") == 0)
		{
			// allow user to transfer funds between accounts
			// i.e., a withdrawal followed by a deposit!
			int from;
			int to;
			double transferAmount;
			std::string transferDesc;

			// method sets the from, to and amount variables to be used
			askTransfer(from, to, transferAmount);

			// switch stement decides which account is being withdrawn from
			switch (from) {
			case 1:
				// if checks whether account current account exists
				if (current == nullptr) {
					std::cout << "Current account does not exist.\n";
				}
				else {
					// withdraws from current
					current->withdraw(transferAmount);

					// calls transfer method to determine which account is being deposited into
					transferTo(to, current, isa, transferAmount, transferDesc, openedAccounts);
					std::cout << "Please add a description for this transfer\n>>> ";
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // will read spaces too that the user inputs
					std::getline(std::cin, transferDesc);
					std::cout << "Withdrawal description: " << transferDesc << "\n";

					// adds transaction to history map
					addTransaction(transactionID, history, transferDesc, transferAmount);
				}
				break;
			case 2:
				// if checks whether any regualr savers exist
				if (openedAccounts.empty()) {
					std::cout << "No regular saver accounts exist.\n";
				}
				else {
					// determines which regular savers is being transferred from
					int savingsChoice;
					std::cout << "Which regular savings account would you like to transfer from?\n";
					showOpenedAccounts(openedAccounts);
					std::cout << ">>> ";
					std::cin >> savingsChoice;

					for (auto& pair : openedAccounts) {
						if (savingsChoice == pair.first) {

							// ensures money is transferred to an open account
							if (current != nullptr || isa != nullptr) {

								// withdraws from regualr savers
								pair.second->withdraw(transferAmount);
								std::cout << "Account ID: " << pair.first << "\n";
								std::cout << "Account Type: Regular Savings\n";
								std::cout << "Balance: " << pair.second->getBalance() << "\n";
							}
						}
					}
					// calls transfer method to determine which account is being deposited into
					transferTo(to, current, isa, transferAmount, transferDesc, openedAccounts);
					std::cout << "Please add a description for this transfer\n>>> ";
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // will read spaces too that the user inputs
					std::getline(std::cin, transferDesc);
					std::cout << "Withdrawal description: " << transferDesc << "\n";

					// adds transaction to history map
					addTransaction(transactionID, history, transferDesc, transferAmount);
				}
				break;
			case 3:
				// if checks whether ISA exists
				if (isa == nullptr) {
					std::cout << "ISA account does not exist.\n";
				}
				else {
					// withdraws from ISA
					isa->withdraw(transferAmount);

					// calls transfer method to determine which account is being deposited into
					transferTo(to, current, isa, transferAmount, transferDesc, openedAccounts);
					std::cout << "Please add a description for this transfer\n>>> ";
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // will read spaces too that the user inputs
					std::getline(std::cin, transferDesc);
					std::cout << "Withdrawal description: " << transferDesc << "\n";

					// adds transaction to history map
					addTransaction(transactionID, history, transferDesc, transferAmount);
				}
				break;
			default:
				std::cout << "Please enter either 1, 2 or 3\n";
				break;
			}
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clears newline left by std::cin - stops programme from crashing at the end of this logic
		}
		else if (command.compare("project") == 0)
		{
			// compute compound interest for years into the future
			int calcChoice;
			int timeSpan;
			std::cout << "Which account would you like to compute its compound interest for?\n";
			std::cout << "1. Regular Savings Account\n";
			std::cout << "2. ISA Savings Account\n";
			std::cout << ">>> ";
			std::cin >> calcChoice;
			std::cout << "And for how many years would you like to project for?\n";
			std::cin >> timeSpan;

			// switch determines which saving account's compund interest is being calculated
			switch (calcChoice) {
			case 1:
				int savingsChoice;
				std::cout << "Which regular savings account would you like to calculate the compound interest for?\n";
				showOpenedAccounts(openedAccounts);
				std::cout << ">>> ";
				std::cin >> savingsChoice;
				std::cout << "Calculating compound interest for your selected savings account...\n";

				// searches the openedAccounts map for the correct regualr savers and calls the computeInterest method
				for (auto& pair : openedAccounts) {
					if (savingsChoice == pair.first) {
						pair.second->computeInterest(pair.second->getBalance(), pair.second->getInterestRate(0.85), timeSpan);
					}
				}
				break;
			case 2:
				// calls the computeInterest method for the ISA
				std::cout << "Calculating compound interest for your ISA...\n";
				isa->computeInterest(isa->getBalance(), isa->getInterestRate(1.15), timeSpan);
				break;
			}
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clears newline left by std::cin - stops programme from crashing at the end of this logic
		}
		else if (command.compare("search") == 0)
		{
			// allow users to search their account history for a transaction
		    // (this is a stretch task)
			// displays the entire transaction history
			std::cout << "Printing out transaction history...\n";
			showHistory(history);

			// asks user to search for a transaction based off its description (that the user has described it as)
			std::string search;
			std::cout << "Please enter the transaction description to search for a transaction\n";
			std::cout << ">>> ";
			std::getline(std::cin, search);
			
			// displays all transactions with the name inputted - if the name doesn't match a message will be displayed
			std::cout << "The following transaction(s) has been found:\n";
			for (auto& pair : history) {
				if (search == pair.second->getDesc()) {
					std::cout << "Transaction ID: " << pair.first << "\tTransaction Description: " << pair.second->getDesc() << "\tTransaction Value: \x9C" << pair.second->getValue() << "\tTransaction Timestamp: " << pair.second->getTimestamp() << "\n";
				}
				else if (search != pair.second->getDesc()) {
					std::cout << "No match found. Please enter the correct transaction description\n";
				}
			}
		}
	}
	// deletes dynamically allocated memory - ensures there's no memory leak
	delete current;
	delete isa;
	for (auto pair : openedAccounts) {
		delete pair.second; // deletes the dynamically allocated Savings objects (the pair.first doesn't need to be deleted, only cleared)
	}
	openedAccounts.clear(); // clears the openedAccounts map
	for (auto& pair : history) {
		delete pair.second; // frees the dynamically allocated memory of each Transaction object
	}
	history.clear();

	std::cout << "Press any key to quit...";
	std::getchar();
}
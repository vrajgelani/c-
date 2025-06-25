#include <iostream>
#include <vector>

using namespace std;

class BankAccount 
{
protected:
    string accountNumber;
    string accountHolderName;
    double balance;

public:
    BankAccount(string accNum, string accHolder, double bal)
        : accountNumber(accNum), accountHolderName(accHolder), balance(bal) {}

    virtual void deposit(double amount) 
	{
        if (amount > 0) 
		{
            balance += amount;
            cout << "Deposited: " << amount << endl;
        }
    }

    virtual void withdraw(double amount) 
	{
        if (amount > 0 && amount <= balance) 
		{
            balance -= amount;
            cout << "Withdrawn: " << amount << endl;
        } else 
		{
            cout << "Insufficient balance or invalid amount." << endl;
        }
    }

    double getBalance() const
	{
        return balance;
    }

    virtual void displayAccountInfo() const 
	{
        cout << "Account Number: " << accountNumber << endl;
        cout << "Account Holder: " << accountHolderName << endl;
        cout << "Balance: " << balance << endl;
    }

    virtual void calculateInterest() const 
    {}

    virtual ~BankAccount() 
	{}
};
class SavingsAccount : public BankAccount 
{
    double interestRate;

public:
    SavingsAccount(string accNum, string accHolder, double bal, double rate)
        : BankAccount(accNum, accHolder, bal), interestRate(rate) 
		{}

    void calculateInterest() const override 
	{
        double interest = balance * (interestRate / 100.0);
        cout << "Savings Account Interest: " << interest << endl;
    }
};

class CheckingAccount : public BankAccount 
{
    double overdraftLimit;

public:
    CheckingAccount(string accNum, string accHolder, double bal, double overdraft)
        : BankAccount(accNum, accHolder, bal), overdraftLimit(overdraft) 
		{}

    void withdraw(double amount) override 
	{
        if (amount <= balance + overdraftLimit) 
		{
            balance -= amount;
            cout << "Withdrawn: " << amount << endl;
        } else 
		{
            cout << "Withdrawal exceeds overdraft limit!" << endl;
        }
    }

    void checkOverdraft() const 
	{
        cout << "Overdraft Limit: " << overdraftLimit << endl;
    }
};

class FixedDepositAccount : public BankAccount
{
    int term;
    double interestRate;

public:
    FixedDepositAccount(string accNum, string accHolder, double bal, int t, double rate)
        : BankAccount(accNum, accHolder, bal), term(t), interestRate(rate) 
		{}

    void calculateInterest() const override 
	{
        double interest = balance * (interestRate / 100.0) * (term / 12.0);
        cout << "Fixed Deposit Interest: " << interest << endl;
    }
};

void menu() 
{
    cout << "\n---- Bank Management Menu ----\n";
    cout << "1. Create Savings Account\n";
    cout << "2. Create Checking Account\n";
    cout << "3. Create Fixed Deposit Account\n";
    cout << "4. Display Account Info\n";
    cout << "5. Deposit\n";
    cout << "6. Withdraw\n";
    cout << "7. Calculate Interest\n";
    cout << "8. Exit\n";
    cout << "-------------------------------\n";
    cout << "Enter your choice: ";
}

int main() 
{
    vector<BankAccount*> accounts;
    int choice;
    
    do 
	{
        menu();
        cin >> choice;

        switch (choice) 
		{
            case 1: 
			{
                string num, name;
                double bal, rate;
                cout << "Enter Account Number, Holder Name, Balance, Interest Rate: ";
                cin >> num >> name >> bal >> rate;
                accounts.push_back(new SavingsAccount(num, name, bal, rate));
                break;
            }
            case 2: 
			{
                string num, name;
                double bal, limit;
                cout << "Enter Account Number, Holder Name, Balance, Overdraft Limit: ";
                cin >> num >> name >> bal >> limit;
                accounts.push_back(new CheckingAccount(num, name, bal, limit));
                break;
            }
            case 3: 
			{
                string num, name;
                double bal, rate;
                int term;
                cout << "Enter Account Number, Holder Name, Balance, Term (months), Interest Rate: ";
                cin >> num >> name >> bal >> term >> rate;
                accounts.push_back(new FixedDepositAccount(num, name, bal, term, rate));
                break;
            }
            case 4: 
			{
                for (auto acc : accounts)
                    acc->displayAccountInfo();
                break;
            }
            case 5: 
			{
                int index;
                double amount;
                cout << "Enter account index and deposit amount: ";
                cin >> index >> amount;
                if (index >= 0 && index < accounts.size())
                    accounts[index]->deposit(amount);
                break;
            }
            case 6: 
			{
                int index;
                double amount;
                cout << "Enter account index and withdraw amount: ";
                cin >> index >> amount;
                if (index >= 0 && index < accounts.size())
                    accounts[index]->withdraw(amount);
                break;
            }
            case 7: 
			{
                for (auto acc : accounts)
                    acc->calculateInterest();
                break;
            }
            case 8: 
			{
                cout << "Exiting...\n";
                break;
            }
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 8);

    for (auto acc : accounts)
        delete acc;
}
/*
output:---- Bank Management Menu ----
1. Create Savings Account
2. Create Checking Account
3. Create Fixed Deposit Account
4. Display Account Info
5. Deposit
6. Withdraw
7. Calculate Interest
8. Exit
-------------------------------
Enter your choice: 1
Enter Account Number, Holder Name, Balance, Interest Rate: 2000
20.
23
23
*/

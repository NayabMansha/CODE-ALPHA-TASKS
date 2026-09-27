#include <iostream>
#include <string>
using namespace std;

const int MAX_TRANS = 20;
const int MAX_ACC = 20;
const int MAX_CUST = 10;

class Transaction {
public:
    string type;
    double amount;

    Transaction() {
        type = "";
        amount = 0;
    }

    Transaction(string t, double a) {
        type = t;
        amount = a;
    }

    void print() {
        cout << type << " -> Rs. " << amount << endl;
    }
};


class Account {
public:
    int accNo;
    int custId;      
    string accType;
    double balance;
    Transaction transactions[MAX_TRANS];
    int transCount;

    Account() {
        accNo = 0;
        custId = 0;
        accType = "";
        balance = 0;
        transCount = 0;
    }

    Account(int no, int cId, string type, double startBalance) {
        accNo = no;
        custId = cId;
        accType = type;
        balance = startBalance;
        transCount = 0;
    }

    void addTransaction(string type, double amount) {
        if (transCount < MAX_TRANS) {
            transactions[transCount] = Transaction(type, amount);
            transCount++;
        }
    }

    void deposit(double amount) {
        if (amount <= 0) {
            cout << "Invalid amount!" << endl;
            return;
        }
        balance = balance + amount;
        addTransaction("Deposit", amount);
        cout << "Deposit successful. New balance = " << balance << endl;
    }

    void withdraw(double amount) {
        if (amount <= 0) {
            cout << "Invalid amount!" << endl;
            return;
        }
        if (amount > balance) {
            cout << "Not enough balance!" << endl;
            return;
        }
        balance = balance - amount;
        addTransaction("Withdraw", amount);
        cout << "Withdraw successful. New balance = " << balance << endl;
    }

    void showTransactions() {
        cout << "\nTransaction history for account " << accNo << ":" << endl;
        if (transCount == 0) {
            cout << "No transactions yet." << endl;
        }
        for (int i = 0; i < transCount; i++) {
            transactions[i].print();
        }
    }

    void showInfo() {
        cout << "Account No: " << accNo << " | Type: " << accType
            << " | Balance: " << balance << endl;
    }
};


class Customer {
public:
    int custId;
    string name;

    Customer() {
        custId = 0;
        name = "";
    }

    Customer(int id, string n) {
        custId = id;
        name = n;
    }
};

Customer customers[MAX_CUST];
int customerCount = 0;

Account accounts[MAX_ACC];
int accountCount = 0;

int nextAccNo = 1001;

// returns the index of the customer in the customers array, or -1 if not found
int findCustomerIndex(int id) {
    for (int i = 0; i < customerCount; i++) {
        if (customers[i].custId == id) {
            return i;
        }
    }
    return -1;
}

int findAccountIndex(int accNo) {
    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].accNo == accNo) {
            return i;
        }
    }
    return -1;
}

void showCustomerDetails(int custIndex) {
    cout << "\nCustomer: " << customers[custIndex].name
        << " (ID: " << customers[custIndex].custId << ")" << endl;

    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].custId == customers[custIndex].custId) {
            accounts[i].showInfo();
        }
    }
}

int main() {
    int choice;

    cout << "===== SIMPLE BANKING SYSTEM =====" << endl;

    do {
        cout << "\n1. Add Customer\n2. Add Account\n3. Deposit\n4. Withdraw\n5. Transfer\n6. Show Account Info\n7. Show All Customers\n0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            string name;
            cout << "Enter customer name: ";
            cin >> name;

            if (customerCount < MAX_CUST) {
                int id = customerCount + 1;
                customers[customerCount] = Customer(id, name);
                customerCount++;
                cout << "Customer added with ID " << id << endl;
            }
            else {
                cout << "Customer list is full!" << endl;
            }
        }

        else if (choice == 2) {
            int id;
            string type;
            double startBalance;

            cout << "Enter customer ID: ";
            cin >> id;

            int custIndex = findCustomerIndex(id);
            if (custIndex == -1) {
                cout << "Customer not found!" << endl;
            }
            else if (accountCount >= MAX_ACC) {
                cout << "Account list is full!" << endl;
            }
            else {
                cout << "Enter account type (Savings/Current): ";
                cin >> type;
                cout << "Enter starting balance: ";
                cin >> startBalance;

                accounts[accountCount] = Account(nextAccNo, id, type, startBalance);
                accountCount++;
                cout << "Account " << nextAccNo << " created for "
                    << customers[custIndex].name << endl;
                nextAccNo++;
            }
        }

        else if (choice == 3) {
            int accNo;
            double amount;
            cout << "Enter account number: ";
            cin >> accNo;

            int accIndex = findAccountIndex(accNo);
            if (accIndex == -1) {
                cout << "Account not found!" << endl;
            }
            else {
                cout << "Enter amount to deposit: ";
                cin >> amount;
                accounts[accIndex].deposit(amount);
            }
        }

        else if (choice == 4) {
            int accNo;
            double amount;
            cout << "Enter account number: ";
            cin >> accNo;

            int accIndex = findAccountIndex(accNo);
            if (accIndex == -1) {
                cout << "Account not found!" << endl;
            }
            else {
                cout << "Enter amount to withdraw: ";
                cin >> amount;
                accounts[accIndex].withdraw(amount);
            }
        }

        else if (choice == 5) {
            int fromAcc, toAcc;
            double amount;

            cout << "Enter FROM account number: ";
            cin >> fromAcc;
            cout << "Enter TO account number: ";
            cin >> toAcc;
            cout << "Enter amount to transfer: ";
            cin >> amount;

            int fromIndex = findAccountIndex(fromAcc);
            int toIndex = findAccountIndex(toAcc);

            if (fromIndex == -1 || toIndex == -1) {
                cout << "One or both accounts not found!" << endl;
            }
            else if (amount > accounts[fromIndex].balance) {
                cout << "Not enough balance to transfer!" << endl;
            }
            else {
                accounts[fromIndex].withdraw(amount);
                accounts[toIndex].deposit(amount);
                cout << "Transfer successful!" << endl;
            }
        }

        else if (choice == 6) {
            int accNo;
            cout << "Enter account number: ";
            cin >> accNo;

            int accIndex = findAccountIndex(accNo);
            if (accIndex == -1) {
                cout << "Account not found!" << endl;
            }
            else {
                accounts[accIndex].showInfo();
                accounts[accIndex].showTransactions();
            }
        }

        else if (choice == 7) {
            if (customerCount == 0) {
                cout << "No customers yet." << endl;
            }
            for (int i = 0; i < customerCount; i++) {
                showCustomerDetails(i);
            }
        }

        else if (choice == 0) {
            cout << "Exiting program. Bye!" << endl;
        }

        else {
            cout << "Wrong choice, try again." << endl;
        }

    } while (choice != 0);

    return 0;
}

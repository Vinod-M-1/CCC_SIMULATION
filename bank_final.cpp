#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream> // Included for robustness, though mostly handled by stoi/stod

using namespace std;

class Accounts
{
private:
    int accN;
    string name;
    int pin;
    double balance;

public:
    void createAcc();
    void setAcc(int accN, string n, double b, int p);
    void display();
    void deposit(int p, double m);
    void withdraw(int p, double m);
    int get_pin() { return pin; }
    int getAccNo() { return accN; }
    string getName() { return name; }
    double get_balance() { return balance; }
    void addBalance(double amt) { balance += amt; }
    bool deductBalance(double amt)
    {
        if (amt <= balance)
        {
            balance -= amt;
            return true;
        }
        return false;
    }
};

void Accounts::createAcc()
{
    cout << "\nEnter Account number: ";
    cin >> accN;
    cin.ignore();
    cout << "Enter name: ";
    getline(cin, name);
    cout << "Enter pin for your account: ";
    cin >> pin;
    cout << "Enter balance: ";
    cin >> balance;
    cout << "--- Account successfully created.---\n";
}

void Accounts::setAcc(int accnum, string n, double b, int p)
{
    accN = accnum;
    name = n;
    balance = b;
    pin = p;
}

void Accounts::display()
{
    cout << "\nAccount Number: " << accN;
    cout << "\nName: " << name;
    cout << "\nBalance: " << balance << "\n";
}

void Accounts::deposit(int p, double m)
{
    if (pin == p)
    {
        balance += m;
        cout << "New balance : " << balance;
    }
    else
    {
        cout << "Transaction cannot be processed -> Incorrect pin.";
    }
}

void Accounts::withdraw(int p, double m)
{
    if (pin == p)
    {
        if (m <= balance)
        {
            balance -= m;
            cout << "\nNew balance: " << balance;
            cout << "\nAmount " << m << " withdrawn successfully.";
        }
        else
        {
            cout << "\nInsufficient balance.";
        }
    }
    else
    {
        cout << "Transaction cannot be processed -> Incorrect pin.";
    }
}

class Bank
{
private:
    vector<Accounts> accounts;

public:
    void createAccounts();
    Accounts *findAcc(int AccNo);
    void deposit();
    void withdraw();
    void displayAcc();
    void transfer();
    void savetofile();
    void loadfromfile();
};

void Bank::loadfromfile()
{
    ifstream file("accounts.txt");
    if (!file)
        return;

    accounts.clear();
    int acc, p;
    string n;
    double bal;

    while (file >> acc >> n >> p >> bal)
    {
        Accounts a;
        a.setAcc(acc, n, bal, p);
        accounts.push_back(a);
    }
    file.close();
}

void Bank::savetofile()
{
    ofstream file("accounts.txt");
    if (!file)
    {
        cout << "File cannot be opened" << endl;
        return;
    }

    for (auto &a : accounts)
    {
        file << a.getAccNo() << " "
             << a.getName() << " "
             << a.get_pin() << " "
             << a.get_balance() << "\n";
    }
    file.close();
}

void Bank::createAccounts()
{
    Accounts a;
    a.createAcc();
    accounts.push_back(a);
}

Accounts *Bank::findAcc(int AccNo)
{
    for (auto &acc : accounts)
    {
        if (acc.getAccNo() == AccNo)
        {
            return &acc;
        }
    }
    return nullptr;
}

void Bank::deposit()
{
    string input;
    int acc, p;
    double m;

    cout << "Enter Account Number: ";
    // Clear any leftover newline character from previous inputs (like the menu choice)
    cin.ignore();

    // Read input safely as a string and convert to int
    getline(cin, input);
    acc = stoi(input);

    cout << "Enter pin: ";
    // Read input safely as a string and convert to int
    getline(cin, input);
    p = stoi(input);

    cout << "Enter amount to deposit: ";
    // Read input safely as a string and convert to double
    getline(cin, input);
    m = stod(input);

    Accounts *ptr = findAcc(acc);

    if (ptr == nullptr)
    {
        cout << "ACCOUNT NOT FOUND";
        return;
    }
    ptr->deposit(p, m);
}

void Bank::withdraw()
{
    string input;
    int acc, p;
    double m;

    cout << "Enter Account Number: ";
    // Clear any leftover newline character from previous inputs (like the menu choice)
    cin.ignore();

    // Read input safely as a string and convert to int
    getline(cin, input);
    acc = stoi(input);

    cout << "Enter pin: ";
    // Read input safely as a string and convert to int
    getline(cin, input);
    p = stoi(input);

    cout << "Enter amount to withdraw: ";
    // Read input safely as a string and convert to double
    getline(cin, input);
    m = stod(input);

    Accounts *ptr = findAcc(acc);

    if (ptr == nullptr)
    {
        cout << "ACCOUNT NOT FOUND";
        return;
    }
    ptr->withdraw(p, m);
}

void Bank::displayAcc()
{
    string input;
    int acc, p;

    cout << "Enter Account Number: ";
    // Clear any leftover newline character from previous inputs (like the menu choice)
    cin.ignore();

    // Read input safely as a string and convert to int
    getline(cin, input);
    acc = stoi(input);

    cout << "Enter pin: ";
    // Read input safely as a string and convert to int
    getline(cin, input);
    p = stoi(input);

    Accounts *ptr = findAcc(acc);

    if (ptr == nullptr)
    {
        cout << "ACCOUNT NOT FOUND";
        return;
    }

    if (ptr->get_pin() == p)
        ptr->display();
    else
        cout << "Incorrect pin";
}

void Bank::transfer()
{
    string input;
    int fromAcc, toAcc, pin;
    double amount;

    cout << "Enter Sender Account Number: ";
    // Clear previous newline from main menu input
    cin.ignore();
    getline(cin, input);
    fromAcc = stoi(input);

    cout << "Enter Sender Account PIN: ";
    getline(cin, input);
    pin = stoi(input);

    Accounts *sender = findAcc(fromAcc);

    if (sender == nullptr)
    {
        cout << "Sender account does not exist.";
        return;
    }
    if (sender->get_pin() != pin)
    {
        cout << "Incorrect PIN.";
        return;
    }

    cout << "Enter Receiver Account Number: ";
    getline(cin, input);
    toAcc = stoi(input);

    if (fromAcc == toAcc)
    {
        cout << "Cannot transfer to the same account.";
        return;
    }

    Accounts *receiver = findAcc(toAcc);

    if (receiver == nullptr)
    {
        cout << "Receiver account does not exist.";
        return;
    }

    cout << "Enter Amount to Transfer: ";
    getline(cin, input);
    amount = stod(input); // Safely read amount

    if (!sender->deductBalance(amount))
    {
        cout << "Insufficient funds.";
        return;
    }

    receiver->addBalance(amount);

    cout << "\n--- Transfer Successful ---\n";
    cout << "Amount Transferred: " << amount << "\n";
    cout << "Sender New Balance: " << sender->get_balance() << "\n";
    cout << "Receiver New Balance: " << receiver->get_balance() << "\n";
}

int main()
{
    int choice = 1;
    Bank Acc;

    Acc.loadfromfile();

    while (choice)
    {
        cout << "\n\n--- MINI BANKING SYSTEM --- ";
        cout << "\n1. Create New Account";
        cout << "\n2. Display Account Details";
        cout << "\n3. Deposit Amount";
        cout << "\n4. Withdraw Amount";
        cout << "\n5. Transfer Between Accounts";
        cout << "\n6. Exit\n\n";

        int c;
        // This is the only place we use cin >> int without immediate cin.ignore()
        // The cin.ignore() in the functions below handles the leftover newline here.
        cin >> c;

        switch (c)
        {
        case 1:
            // This function already uses cin >> and then cin.ignore() for the subsequent getline
            Acc.createAccounts();
            break;
        case 2:
            Acc.displayAcc();
            break;
        case 3:
            Acc.deposit();
            break;
        case 4:
            Acc.withdraw();
            break;
        case 5:
            Acc.transfer();
            break;
        case 6:
            choice = 0;
            break;
        default:
            cout << "Invalid Option";
        }
    }

    Acc.savetofile();
    return 0;
}
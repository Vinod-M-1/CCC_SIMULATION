#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stack>
#include <sstream>
using namespace std;

class Accounts
{
private:
    int accN;
    string name;
    int pin;
    double balance;
    stack<string> history;

public:
    void createAcc();
    void setAcc(int accN, string n, double b, int p);
    void display();
    void deposit(int p, double m);
    void withdraw(int p, double m);
    void addHistory(string h);
    void showHistory();
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

void Accounts::addHistory(string h)
{
    if (history.size() == 5)
    {
        stack<string> temp;
        while (history.size() > 1)
        {
            temp.push(history.top());
            history.pop();
        }
        history.pop();
        while (!temp.empty())
        {
            history.push(temp.top());
            temp.pop();
        }
    }
    history.push(h);
}

void Accounts::showHistory()
{
    if (history.empty())
    {
        cout << "No recent transactions.\n";
        return;
    }
    stack<string> temp = history;
    while (!temp.empty())
    {
        cout << temp.top() << "\n";
        temp.pop();
    }
}

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
    addHistory("Account created with balance: " + to_string(balance));
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
        addHistory("Deposited: " + to_string(m));
        cout << "New balance : " << balance;
    }
    else
        cout << "Incorrect pin.";
}

void Accounts::withdraw(int p, double m)
{
    if (pin == p)
    {
        if (m <= balance)
        {
            balance -= m;
            addHistory("Withdrawn: " + to_string(m));
            cout << "New balance: " << balance;
        }
        else
            cout << "Insufficient balance.";
    }
    else
        cout << "Incorrect pin.";
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
    void viewRecentTransactions();
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
    for (auto &a : accounts)
        file << a.getAccNo() << " " << a.getName() << " " << a.get_pin() << " " << a.get_balance() << "\n";
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
        if (acc.getAccNo() == AccNo)
            return &acc;
    return nullptr;
}

void Bank::deposit()
{
    string input;
    int acc, p;
    double m;

    cout << "Enter Account Number: ";
    cin.ignore();
    getline(cin, input);
    acc = stoi(input);

    cout << "Enter pin: ";
    getline(cin, input);
    p = stoi(input);

    cout << "Enter amount to deposit: ";
    getline(cin, input);
    m = stod(input);

    Accounts *ptr = findAcc(acc);
    if (!ptr)
        cout << "ACCOUNT NOT FOUND";
    else
        ptr->deposit(p, m);
}

void Bank::withdraw()
{
    string input;
    int acc, p;
    double m;

    cout << "Enter Account Number: ";
    cin.ignore();
    getline(cin, input);
    acc = stoi(input);

    cout << "Enter pin: ";
    getline(cin, input);
    p = stoi(input);

    cout << "Enter amount to withdraw: ";
    getline(cin, input);
    m = stod(input);

    Accounts *ptr = findAcc(acc);
    if (!ptr)
        cout << "ACCOUNT NOT FOUND";
    else
        ptr->withdraw(p, m);
}

void Bank::displayAcc()
{
    string input;
    int acc, p;

    cout << "Enter Account Number: ";
    cin.ignore();
    getline(cin, input);
    acc = stoi(input);

    cout << "Enter pin: ";
    getline(cin, input);
    p = stoi(input);

    Accounts *ptr = findAcc(acc);
    if (!ptr)
        cout << "ACCOUNT NOT FOUND";
    else if (ptr->get_pin() == p)
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
    cin.ignore();
    getline(cin, input);
    fromAcc = stoi(input);

    cout << "Enter Sender Account PIN: ";
    getline(cin, input);
    pin = stoi(input);

    Accounts *sender = findAcc(fromAcc);
    if (!sender)
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
        cout << "Cannot transfer to same account.";
        return;
    }

    Accounts *receiver = findAcc(toAcc);
    if (!receiver)
    {
        cout << "Receiver account does not exist.";
        return;
    }

    cout << "Enter Amount to Transfer: ";
    getline(cin, input);
    amount = stod(input);

    if (!sender->deductBalance(amount))
    {
        cout << "Insufficient funds.";
        return;
    }

    receiver->addBalance(amount);

    sender->addHistory("Transferred: " + to_string(amount) + " to " + to_string(toAcc));
    receiver->addHistory("Received: " + to_string(amount) + " from " + to_string(fromAcc));

    cout << "Transfer Successful\n";
}

void Bank::viewRecentTransactions()
{
    string input;
    int acc, p;

    cout << "Enter Account Number: ";
    cin.ignore();
    getline(cin, input);
    acc = stoi(input);

    cout << "Enter pin: ";
    getline(cin, input);
    p = stoi(input);

    Accounts *ptr = findAcc(acc);
    if (!ptr)
        cout << "ACCOUNT NOT FOUND";
    else if (ptr->get_pin() == p)
        ptr->showHistory();
    else
        cout << "Incorrect pin";
}

int main()
{
    int choice = 1;
    Bank Acc;
    Acc.loadfromfile();

    while (choice)
    {
        cout << "\n--- MINI BANKING SYSTEM ---\n";
        cout << "1. Create New Account\n2. Display Account Details\n3. Deposit Amount\n4. Withdraw Amount\n5. Transfer\n6. Recent Transactions\n7. Exit\n";
        int c;
        cin >> c;

        switch (c)
        {
        case 1:
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
            Acc.viewRecentTransactions();
            break;
        case 7:
            choice = 0;
            break;
        default:
            cout << "Invalid Option";
        }
    }

    Acc.savetofile();
    return 0;
}

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

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
    int acc, p;
    double m;

    cout << "Enter Account Number: ";
    cin >> acc;
    cout << "Enter pin: ";
    cin >> p;
    cout << "Enter amount to deposit: ";
    cin >> m;

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
    int acc, p;
    double m;

    cout << "Enter Account Number: ";
    cin >> acc;
    cout << "Enter pin: ";
    cin >> p;
    cout << "Enter amount to withdraw: ";
    cin >> m;

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
    int acc, p;

    cout << "Enter Account Number: ";
    cin >> acc;
    cout << "Enter pin: ";
    cin >> p;

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
    int fromAcc, toAcc, pin;
    double amount;

    cout << "Enter Sender Account Number: ";
    cin >> fromAcc;
    cout << "Enter Sender Account PIN: ";
    cin >> pin;

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
    cin >> toAcc;

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
    cin >> amount;

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
            choice = 0;
            break;
        default:
            cout << "Invalid Option";
        }
    }

    Acc.savetofile();
    return 0;
}



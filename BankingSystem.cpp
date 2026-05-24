#include<iostream>
#include<string>
#include<vector>
using namespace std;
class Transaction
{
    public:
    string type;
    double amount;
    Transaction(string t, double a)
    {
        type = t;
        amount = a;
    }
};
class Account
{
    private:
    int accountNumber;
    double balance;
    vector<Transaction> transactions;
    public:
    Account(int accNum)    
    {
        accountNumber = accNum;
        balance = 0.0;
    }
    int getAccountNumber()
    {
        return accountNumber;
    }
    double getBalance()
    {
        return balance;
    } 
    void deposit(double amount)
    {
        balance += amount;
        transactions.push_back(Transaction("Deposit", amount));
        cout<<"Deposit successful. New balance: "<<balance<<endl;
    }
    void withdraw(double amount)
    {
        if(amount > balance)
        {
            cout<<"Insufficient funds. Withdrawal failed."<<endl;
        }
        else
        {
        balance -= amount;
        transactions.push_back(Transaction("Withdrawal", amount));
        cout<<"Withdrawal successful. New balance: "<<balance<<endl;
    }
}
void transfer(Account& toAccount, double amount)
{
    if(amount > balance)
    {
        cout<<"Insufficient funds. Transfer failed."<<endl;
    }
    else
    {
        balance -= amount;
        toAccount.balance+=amount;
        transactions.push_back(Transaction("Transfer Sent", amount));
        toAccount.transactions.push_back(Transaction("Transfer Received", amount));
        cout<<"Transfer successful. New balance: "<<balance<<endl;
    }
}
void displayTransactions()
{
    cout<<"Transaction History for Account "<<accountNumber<<":"<<endl;
   if(transactions.empty())
   {
       cout<<"No transactions found."<<endl;
   }
   else
   {
       for(int i=0; i<transactions.size(); i++)
       {
           cout<<i+1<<". "<<transactions[i].type<<"- Rs. "<<transactions[i].amount<<endl;
       }
   }
}
void displayAccountDetails()
{
    cout<<"Account Number: "<<accountNumber<<endl;
    cout<<"Current Balance: Rs. "<<balance<<endl;
}
};
class Customer
{
    private:
    string name;
    int customerID;
    Account account;
    public:
    Customer(string n, int id, int accNum): account(accNum)
    {
        name = n;
        customerID = id;
    }
    int getCustomerID()
    {
        return customerID;
    }
    string getName()
    {
        return name;
    }
    Account& getAccount()
    {
        return account;
    }
    void displayCustomerDetails()
    {
        cout<<"Customer ID: "<<customerID<<endl;
        cout<<"Customer Name: "<<name<<endl;
        account.displayAccountDetails();
    }

};
int main()
{
    vector<Customer> customers;
    int choice;
    while(true)
    {
        cout<<"1. Create Account"<<endl;
        cout<<"2. Deposit Money"<<endl;
        cout<<"3. Withdraw Money"<<endl;
        cout<<"4. Transfer Money"<<endl;
        cout<<"5. Display Account Details"<<endl;
        cout<<"6. Display Transaction History"<<endl;
        cout<<"7. Exit"<<endl;
        cout<<"Enter your choice: ";
        cin>>choice;
        if(choice == 1)
        {
            string name;
            int id, accNum;
            cin.ignore(); // Clear the input buffer
            cout<<"Enter customer name: ";
            getline(cin, name);
            cout<<"Enter customer ID: ";
            cin>>id;
            cout<<"Enter account number: ";
            cin>>accNum;
            customers.push_back(Customer(name, id, accNum));
            cout<<"Account created successfully."<<endl;
        }
        else if(choice == 2)
        {
            int accNumber;
             cout<<"Enter account number: ";
             cin>>accNumber;
             bool found = false;
             for(int i=0; i<customers.size(); i++)
             {
                 if(customers[i].getAccount().getAccountNumber() == accNumber)
                 {
                     double amount;
                     cout<<"Enter amount to deposit: ";
                     cin>>amount;
                     customers[i].getAccount().deposit(amount);
                     found = true;
                     break;
                 }
             }
             if(!found)
             {
                 cout<<"Account not found."<<endl;
             }
        }
        else if(choice == 3)
        {
            int accNumber;
            double amount;
            cout<<"Enter account number: ";
            cin>>accNumber;
             bool found = false;
             for(int i=0; i<customers.size(); i++)
             {
                 if(customers[i].getAccount().getAccountNumber() == accNumber)
                 {
                     cout<<"Enter amount to withdraw: ";
                     cin>>amount;
                     customers[i].getAccount().withdraw(amount);
                     found = true;
                     break;
                 }
             }
             if(!found)
             {
                 cout<<"Account not found."<<endl;
             }
            
        }
        else if(choice == 4)
        {
             int senderacc, receiveracc;
             double amount;
             cout<<"Enter sender account number: ";
             cin>>senderacc;
             cout<<"Enter receiver account number: ";
             cin>>receiveracc;
             cout<<"Enter amount to transfer: ";
             cin>>amount;
             Account* sender = nullptr;
             Account* receiver = nullptr;
             for(int i=0; i<customers.size(); i++)
             {
                 if(customers[i].getAccount().getAccountNumber() == senderacc)
                 {
                     sender = &customers[i].getAccount();
                 }
                 if(customers[i].getAccount().getAccountNumber() == receiveracc)
                 {
                     receiver = &customers[i].getAccount();
                 }
             }
             if(sender!=NULL && receiver!=NULL)
             {
                 sender->transfer(*receiver, amount);
             }
             else
             {
                 cout<<"One or both customers not found."<<endl;
             }
        }
        else if(choice == 5)
        {
            int accNo;

            cout << "Enter Account Number: ";
            cin >> accNo;

            bool found = false;

            for (int i = 0; i < customers.size(); i++)
            {
                if (customers[i].getAccount().getAccountNumber() == accNo)
                {
                    customers[i].displayCustomerDetails();
                    found = true;
                    break;
                }
            }

            if (!found)
            {
                cout << "Account Not Found!\n";
            }
        }
        else if(choice == 6)
        {
            int accNo;

            cout << "Enter Account Number: ";
            cin >> accNo;

            bool found = false;

            for (int i = 0; i < customers.size(); i++)
            {
                if (customers[i].getAccount().getAccountNumber() == accNo)
                {
                    customers[i].getAccount().displayTransactions();
                    found = true;
                    break;
                }
            }

            if (!found)
            {
                cout << "Account Not Found!\n";
            }
        }
        else if(choice == 7)
        {
            cout<<"Exiting the program. Goodbye!"<<endl;
            break;
        }
        else
        {
            cout<<"Invalid choice. Please try again."<<endl;
        }
    }
    return 0;
}
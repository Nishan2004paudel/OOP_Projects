#include <iostream>
#include <string>
using namespace std;

class BankAccount{
private:
    string name;
    int accountNumber;
    double balance;
public:
    void createAccount();
    void deposit(double amount);
    void withdraw(double amount);
    void display();
};

void BankAccount::createAccount(){
    cout<< "Enter account holder name: ";
    cin.ignore();
    getline(cin, name);

    cout<<"Enter account number: ";
    cin>>accountNumber;

    balance = 0;
    cout<< "Account created successfully!\n";
}

void BankAccount::deposit(double amount){
    if(amount > 0){
        balance += amount;
        cout<<"Amount deposited successfully!\n";
    }else{
        cout<< "Invalid amount!\n";
    }
}

void BankAccount::withdraw(double amount){
    if(amount<= balance && amount > 0){
        balance -=amount;
        cout<< "Withdrawal successful!\n";
    }else{
        cout<<"Insufficient balance or invalid amount!\n";
    }
}

void BankAccount::display(){
    cout<<"\n Account Holder: "<<name<<endl;
    cout<<"Account Number: "<<accountNumber<<endl;
    cout<<"Balance: $"<<balance<<endl;
}

int main(){
    BankAccount account;
    int choice;
    double amount;

    while(true){
        cout<<"\n1. Create Account\n2. Deposit\n3. Withdraw\n4. Display\n5. Exit\n Enter choice: ";
        cin>>choice;


        switch(choice){
            case 1:
                account.createAccount();
                break;
            case 2:
                cout<<"Enter amount to deposit: ";
                cin>>amount;
                account.deposit(amount);
                break;
            case 3:
                cout<<"Enter amount to withdraw";
                cin>> amount;
                account.withdraw(amount);
                break;
            case 4:
                account.display();
                break;
            case 5:
                cout<<"Exiting Bank System. GoodBye!\n";
                return 0;
            default:
                cout<<"Invalid choice!\n";
        }
    }

}
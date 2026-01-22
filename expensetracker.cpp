#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

class Expense{
private:
    string title;
    float amount;
    string category;

public:
    Expense(string t, float a, string c){
        title = t;
        amount = a;
        category = c;
    }

    float getAmount() const{
        return amount;
    }

    string toFileString() const{
        return title + "," + to_string(amount)+","+category;
    }

    void display() const{
        cout<<"Title: "<<title<<" | Amount: "<<amount<<" | Category: "<<category<<endl;
    }

    static Expense fromFileString(const string &line){
        int p1 = line.find(',');
        int p2 = line.find(',',p1+1);

        string t = line.substr(0,p1);
        float a = stof(line.substr(p1+1,p2-p1-1));
        string c = line.substr(p2+1);

        return Expense(t,a,c);
    }
};

void showMenu(){

    cout<<"\n1. Add Expense";
    cout<<"\n2. View Expenses";
    cout<<"\n3. Show Total Spending";
    cout<<"\n4. Save & Exit";
    cout<<"\n Enter choice: ";

}

void saveToFile(const vector<Expense> &data){
    ofstream file("expense.txt");
    for (const Expense &e: data){
        file << e.toFileString()<<endl;
    }
    file.close();
}


void loadFromFile(vector<Expense> &data){
    ifstream file("expenses.txt");
    string line;
    while (getline(file,line)){
        if(!line.empty()){
            data.push_back(Expense::fromFileString(line));
        }
    }
    file.close();
}

int main(){
    vector<Expense> expenses;
    int choice;

    loadFromFile(expenses);

    while(true){
        showMenu();
        cin>>choice;
        cin.ignore();

        if(choice ==1 ){
            string title, category;
            float amount;

            cout <<"Enter title: ";
            getline(cin,title);

            cout<<"Enter amount: ";
            cin>>amount;
            cin.ignore();

            cout<<"Enter category: ";
            getline(cin,category);

            expenses.emplace_back(title,amount,category);
            cout<<"Expense added.\n";
        }
        else if(choice ==2){
            if (expenses.empty()){
                cout<<"No expenses recorded.\n";
                continue;
            }

            for(const Expense &e: expenses){
                e.display();
            }
        }
        else if(choice == 3){
            float total = 0;
            for (const Expense &e: expenses){
                total += e.getAmount();
            }

            cout<<"Total Spending: "<<total<<endl;
        }
        else if(choice == 4){
            saveToFile(expenses);
            cout<<"Data Saved. Exiting.\n";
            return 0;
        }
        else{
            cout<<"Invalid Choice.\n";
        }
    }
    return 0;
}
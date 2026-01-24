#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class Contact{
private:
    string name;
    string phone;
    string email;

public:

    Contact(){}

    Contact(string n, string p, string e){
        name = n;
        phone = p;
        email=e;
    }

    string getName(){
        return name;
    }

    string getPhone(){
        return phone;
    }

    string getEmail(){
        return email;
    }

    void display(){
        cout<<"Name : "<<name<<endl;
        cout<<"Phone : "<<phone<<endl;
        cout<<"Email : "<<email<<endl;
        cout<<"--------------------------"<<endl;
    }

    string serialize(){
        return name + "|"+phone+"|"+email;
    }

    static Contact deserialize(string line){
        string name, phone, email;
        int p1= line.find('|');
        int p2= line.rfind('|');

        name= line.substr(0,p1);
        phone = line.substr(p1+1, p2-p1-1);
        email= line.substr(p2+1);

        return Contact(name, phone, email);

    }
};

class ContactManager{
private: 
    vector<Contact> contacts;
    const string filename = "contacts.txt";

public:
    void addContact(){
        string name, phone, email;

        cin.ignore();
        cout<<"Enter name: ";
        getline(cin,name);
        cout<<"Enter phone: ";
        getline(cin,phone);
        cout<<"Enter email: ";
        getline(cin,email);

        contacts.push_back(Contact(name,phone,email));
        cout<<"Contact added successfully!\n";
    }

    void viewContacts(){
        if(contacts.empty()){
            cout<<"No contacts found.\n";
            return;
        }

        for (Contact &c: contacts){
            c.display();
        }
    }

    void searchContact(){
        string name;
        cin.ignore();
        cout<<"Enter name to search: ";
        getline(cin,name);

        for (Contact &c: contacts){
            if(c.getName() == name){
                c.display();
                return;
            }
        }

        cout<<"Contact not found.\n";
    }

    void deleteContact(){
        string name;
        cin.ignore();
        cout<<"Enter name to delete: ";
        getline(cin,name);
        for (int i = 0; i<contacts.size();i++){
            if(contacts[i].getName() == name){
                contacts.erase(contacts.begin()+i);
                cout<<"Contact deleted successfully.\n";
                return;
            }
        }

        cout<<"Contact not found.\n";
    }

    void saveToFile(){
        ofstream file(filename);
        for (Contact &c: contacts){
            file<<c.serialize()<<endl;
        }
        file.close();
        cout<<"Contacts saved to file.\n";
    }

    void loadFromFile(){
        ifstream file(filename);
        string line;
        contacts.clear();

        while(getline(file,line)){
            contacts.push_back(Contact::deserialize(line));
        }

        file.close();
        cout<<"Contacts loaded from file.\n";
    }
};


int main(){
    ContactManager manager;
    int choice;

    manager.loadFromFile();

    while(true){
        cout<<"\n--- Contact Management System---\n";
        cout<<"1. Add Contact\n";
        cout<<"2. View Contacts\n";
        cout<<"3. Search Contact\n";
        cout<<"4. Delete Contact\n";
        cout<<"5. Save And Exit\n";
        cout<<"Enter Choice: ";
        cin>> choice;

        switch(choice){
            case 1: 
                manager.addContact();
                break;
            case 2: 
                manager.viewContacts();
                break;
            case 3:
                manager.searchContact();
                break;
            case 4:
                manager.deleteContact();
                break;
            case 5:
                manager.saveToFile();
                cout<<"Exiting Program........\n";
                return 0;
            default: 
                cout<<"Invalid Choice.\n";
        }
    }
    return 0;
}
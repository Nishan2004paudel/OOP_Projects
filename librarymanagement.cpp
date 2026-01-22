#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

class Book{
private:
    int id;
    string title;
    string author;
    bool isAvailable;
public:
    Book(int i, string t, string a, bool available = true){
        id = i;
        title = t;
        author = a;
        isAvailable = available;
    }
    int getId() const{
        return id;
    }

    bool available() const{
        return isAvailable;
    }

    void borrowBook(){
        isAvailable = false;
    }

    void returnBook(){
        isAvailable = true;
    }

    void display() const{
        cout<< "ID: "<<id<< ", Title: "<<title<<", Author: "<<author<<", Status: "<<(isAvailable? "Available": "Borrowed")<<endl;
    }

    string toFileString() const{
        return to_string(id)+","+title+","+author+","+(isAvailable ?"1":"0");
    }

    static Book fromFileString(const string &line){
        int id;
        string title, author;
        bool available;
        char comma;
        int avail;

        stringstream ss(line);
        ss >> id>>comma;
        getline(ss, title,',');
        getline(ss, author,',');
        ss>>avail;

        available = (avail==1);
        return Book(id, title, author, available);
    }
};

void showMenu(){
    cout<<"\n1. Add Book";
    cout<<"\n2. View Books";
    cout<<"\n3. Borrow Book";
    cout<<"\n4. Return Book";
    cout<<"\n5. Save & Exit";
    cout<<"\n Enter choice: ";
}

void saveToFile(const vector<Book> &library){
    ofstream file("library.txt");
    for (const Book &b : library){
        file << b.toFileString()<<endl;
    }
    file.close();
    cout<<"Library saved to file. \n";
}

void loadFromFile(vector<Book> &library){
    ifstream file("library.txt");
    string line;

    while (getline(file, line)){
        if(!line.empty()){
            library.push_back(Book::fromFileString(line));
        }
    }
    file.close();
}


int main(){
    vector<Book> library;
    int choice;

    loadFromFile(library);

    while (true){
        showMenu();
        cin>> choice;

        if(choice ==1){
            int id;
            string title, author;

            cout<<"Enter book ID: ";
            cin>>id;
            cin.ignore();

            cout<<"Enter title: ";
            getline(cin, title);

            cout<<"Enter author: ";
            getline(cin, author);

            library.emplace_back(id, title, author);
            cout<<"Book added successfully.\n";
        }
        else if(choice == 2){
            if (library.empty()){
                cout<< "No books available.\n";
                continue;
            }
            for (const Book &b: library){
                b.display();
            }
        }
        else if(choice == 3){
            int id;
            cout<<"Enter book ID to borrow: ";
            cin>> id;

            bool found = false;
            for (Book &b : library){
                if (b.getId() == id && b.available()){
                    b.borrowBook();
                    cout<<"Book Borrowed Successfully.\n";
                    found = true;
                    break;
                }
            }
            if (!found){
                cout<<"Book not found or already borrowed.\n";
            }
        }
        else if(choice == 4){
            int id;
            cout<<"Enter book ID to return: ";
            cin>> id;

            bool found = false;
            for (Book &b: library){
                if(b.getId() == id && !b.available()){
                    b.returnBook();
                    cout<<"Book Returned Successfully.\n";
                    found = true;
                    break;
                }
            }
            if(!found){
                cout<<"Book not found or already available.\n";
            }
        }
        else if(choice == 5){
            saveToFile(library);
            cout<<"Exiting Library System. Goodbye!\n";
            return 0;
        }
        else {
            cout<<"Invalid choice.\n";
        }
    }
}
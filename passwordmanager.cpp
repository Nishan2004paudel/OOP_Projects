#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

class Credential{
private:
    string website;
    string username;
    string password;

public:
    Credential(string w, string u, string p){
        website = w;
        username = u;
        password = p;
    }
    string toFileString() const{
        return website + "," + username + ","+ password;
    }

    void display() const{
        cout<< "Website: "<<website<<", Username: "<<username<<", Password: "<<password<<endl;

    }

    static Credential fromFileString(const string &line){
        string w,u,p;
        int pos1= line.find(',');
        int pos2= line.find(',',pos1+1);

        w=line.substr(0,pos1);
        u=line.substr(pos1+1,pos2-pos1-1);
        p = line.substr(pos2+1);

        return Credential(w,u,p);
    }
};



void showMenu(){
    cout<<"\n1. Add Credential";
    cout<<"\n2. View Credential";
    cout<<"\n3. Save & Exit";
    cout<<"\n Enter Choice: ";
}

void saveToFile(const vector<Credential> &data){
    ofstream file("passwords.txt");

    for (const Credential &c: data){
        file <<c.toFileString()<<endl;
    }

    file.close();
}


void loadFromFile(vector<Credential> &data){
    ifstream file("passwords.txt");
    string line;

    while(getline(file,line)){
        if(!line.empty()){
            data.push_back(Credential::fromFileString(line));
        }
    }
    file.close();
}

int main(){
    vector<Credential> vault;
    int choice;

    loadFromFile(vault);

    while(true){
        showMenu();
        cin>>choice;
        cin.ignore();

        if(choice == 1){
            string w,u,p;

            cout<<"Enter website: ";
            getline(cin,w);

            cout<<"Enter username: ";
            getline(cin,u);

            cout<<"Enter password: ";
            getline(cin,p);

            vault.emplace_back(w,u,p);
            cout<<"Credential added.\n";
        }
        else if(choice == 2){
            if(vault.empty()){
                cout<<"No credentials saved. \n";
                continue;
            }

            for(const Credential &c: vault){
                c.display();
            }
        }

        else if(choice == 3){
            saveToFile(vault);
            cout<<"Data Saved. Exiting.\n";
            return 0;
        }

        else{
            cout<<"Invalid choice.\n";
        }
    }
}

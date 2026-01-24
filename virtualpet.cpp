#include <iostream>
#include <vector>
#include <memory>
using namespace std;

class Pet{
protected:
    string name;
    int hunger;
    int happiness;

public:
    Pet(string n){
        name = n;
        hunger = 5;
        happiness = 5;
    }

    virtual void feed(){
        hunger -= 2;
        if(hunger < 0) hunger = 0;
        cout<<name<<" has been fed. \n";
    }

    virtual void play(){
        happiness += 2;
        if(happiness > 10) happiness = 10;
        hunger += 1;
        cout<<name<<" played and is happier now!\n";
    }

    virtual void makeSound() = 0;

    void showStatus(){
        cout<<"Name   : "<<name<<endl;
        cout<<"Hunger  : "<<hunger<<"/10"<<endl;
        cout<<"Happiness : "<<happiness<<"/10"<<endl;
        cout<<"------------------------\n";
    }

    string getName() const {
        return name;
    }

    virtual ~Pet(){}
};


class Dog : public Pet{
public: 
    Dog(string n): Pet(n){}

    void makeSound() override{
        cout<<name<<" says: Woof! \n";
    }
};

class Cat: public Pet{
public: 
    Cat(string n): Pet(n){}

    void makeSound() override{
        cout<<name<<" says: Meow! \n";
    }
};

class Bird: public Pet{
public: 
    Bird(string n): Pet(n){}

    void makeSound() override{
        cout<<name<<" says: Tweet! \n";
    }
};

int main(){
    vector<shared_ptr<Pet>> pets;
    int choice;
    string name;
    int type;

    cout<<"Welcome to the Virtual Pet Simulator!\n";

    while (true){
        cout<<"\n--- Menu ---\n";
        cout<<"1. Adopt a Pet \n";
        cout<<"2. Feed a Pet \n";
        cout<<"3. Play with a Pet \n";
        cout<<"4. Make Pet Sound \n";
        cout<<"5. Show Pet Status \n";
        cout<<"6. Exit \n";
        cout<<"Enter choice: ";
        cin>>choice;

        switch(choice){
            case 1:
                cout<<"Enter pet name: ";
                cin>>name;
                cout<<"Choose type: 1. Dog 2. Cat 3. Bird: ";
                cin>>type;

                if(type ==1 ) pets.push_back(make_shared<Dog>(name));
                else if(type == 2) pets.push_back(make_shared<Cat>(name));
                else if(type == 3)pets.push_back(make_shared<Bird>(name));
                else cout<<"Invalid Type !\n";

                cout<<name<<" has been adopted!\n";
                break;

            case 2:
                if (pets.empty()) {cout<< "No pets yet!\n"; break;}

                for(int i = 0; i<pets.size(); i++)
                    cout<<i+1<<"."<<pets[i]->getName()<<endl;
                cout<<"Choose pet number to feed: ";
                int f; cin>>f;
                if(f>=1 && f<=pets.size()) pets[f-1]->feed();
                else cout<<"Invalid selection.\n";
                break;

            case 3:
                if (pets.empty()){ cout <<"No pets yet!\n"; break;}
                for (int i = 0; i< pets.size(); i++)
                    cout<<i+1<<"."<<pets[i]->getName()<<endl;
                cout<<"Choose pet number to play: ";
                int p; cin>>p;
                if (p>=1 && p <= pets.size()) pets[p-1]->play();
                else cout<<"Invalid selection.\n";
                break;

            case 4:
                if(pets.empty()) {cout<<"No pets yet!\n"; break;}
                for (int i = 0; i< pets.size(); i++)
                    cout<<i+1<<"."<<pets[i]->getName()<<endl;
                cout<<"Choose pet number to hear sound: ";
                int s; cin>>s;
                if (s>= 1&& s<= pets.size()) pets[s-1]->makeSound();
                else cout<< "Invalid selection.\n";
                break;

            case 5:
                if(pets.empty()) {cout<<"No pets yet!\n"; break;}
                for(auto &pet : pets)pet->showStatus();
                break;

            case 6:
                cout<<"Exiting Virtual Pet Simulator. Bye!\n";
                return 0;

            default:
                cout<<"Invalid choice.\n";
        }
    }
    return 0;
}
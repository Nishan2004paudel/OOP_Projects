#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Entity{
protected:
    string name;
public: 
    Entity(string n): name(n){}
    virtual void update() = 0;
    virtual void render() const = 0;
    virtual ~Entity() {}
};

class Player: public Entity{
private: 
    int health;

public: 
    Player(string n): Entity(n), health(100){}

    void update() override{
        cout<<name<<" moves and explores. Health: "<<health<<endl;

    }

    void render() const override{
        cout<< "[Render] Player: "<<name<<endl;
    }

};

class Enemy: public Entity{
private:
    int damage;
public:
    Enemy(string n): Entity(n), damage(20){}

    void update() override{
        cout<<name<<" attacks with damage "<<damage<<endl;
    }

    void render() const override{
        cout<<"[Render] Enemy: "<<name<<endl;
    }
};

class NPC : public Entity{
public: 
    NPC(string n): Entity(n){}

    void update() override{
        cout<<name<<" talks to the player. "<<endl;
    }

    void render() const override{
        cout<<"[Render] NPC: "<<name<<endl;
    }
};

int main(){
    vector<Entity*> entities;

    entities.push_back(new Player("Hero"));
    entities.push_back(new Player("Goblin"));
    entities.push_back(new Player("villager"));

    cout<<"====Game Loop Start====\n";

    for (int frame= 1; frame<=3;frame++){
        cout<<"\n--- Frame"<<frame<<"---\n";

        for(Entity* e: entities){
            e-> update();
            e-> render();
        }
    }

    for(Entity* e: entities){
        delete e;
    }

    cout<<"\n=== Game Loop End===\n";

    return 0;


}
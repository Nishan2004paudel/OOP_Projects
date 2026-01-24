#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

class MenuItem{
private:
    int id;
    string name;
    string category;
    double price;
public:
    MenuItem(){}

    MenuItem(int i, string n, string c, double p){
        id = i;
        name = n;
        category = c;
        price = p;
    }

    int getId() {return id;}
    string getName() {return name;}
    string getCategroy() {return category;}
    double getPrice() {return price;}

    void display(){
        cout<<id<<"."<<name<<" ("<<category<<") - $"<<price<<endl;
    }


    string serialize(){
        return to_string(id)+"|"+name+"|"+category+"|"+to_string(price);
    }

    static MenuItem deserialize(string line){
        int id;
        string name, category;
        double price;

        size_t p1 = line.find('|');
        size_t p2= line.find('|',p1+1);
        size_t p3 = line.find('|',p2+1);

        id = stoi(line.substr(0,p1));
        name = line.substr(p1+1,p2-p1-1);
        category = line.substr(p2+1,p3-p2-1);
        price = stod(line.substr(p3+1));

        return MenuItem(id, name,category, price);
    }
};

class OrderItem{
public:
    MenuItem item;
    int quantity;

    OrderItem(MenuItem i, int q){
        item = i;
        quantity = q;

    }

    double getTotalPrice(){
        return item.getPrice() * quantity;
    }

    void display(){
        cout<<item.getName()<<" x"<<quantity<<"- $"<<getTotalPrice()<<endl;
    }
};

class Order{
private:
    int orderId;
    vector<OrderItem> items;

public:
    Order(int id) { orderId = id;}
    void addItem(MenuItem menuItem, int quantity){
        items.push_back(OrderItem(menuItem,quantity));
    }

    double getTotalBill(){
        double total = 0;
        for(auto &oi : items)
            total += oi.getTotalPrice();
        return total;
    }

    void displayOrder(){
        cout<<"\nOrder ID: "<<orderId <<endl;
        for (auto &oi : items)
            oi.display();
        cout<<"Total Bill: $"<<getTotalBill()<<endl;
        cout<<"----------------------------\n";
    }

    string serialize(){
        string line= to_string(orderId) + "|";
        for (auto &oi : items)
            line += to_string(oi.item.getId()) + "," + to_string(oi.quantity) + ";";
            line +=to_string(getTotalBill());
            return line;
    }
};

class RestaurantManager{
private:
    vector<MenuItem> menu;
    vector<Order> orders;
    int nextOrderId = 1;

    const string menuFile = "menu.txt";
    const string ordersFile = "orders.txt";

public:
    RestaurantManager(){
        loadMenu();
        loadOrders();
    }

    void addMenuItem(){
        int id;
        string name, category;
        double price;
        cout<<"Enter item ID: ";cin>>id;
        cin.ignore();
        cout<<"Enter item name: ";getline(cin,name);
        cout<<"Enter category: ";getline(cin,category);
        cout<<"Enter price: ";cin>>price;

        menu.push_back(MenuItem(id,name,category,price));
        cout<<"Menu item added!\n";
    }

    void viewMenu(){
        if(menu.empty()) { cout<<"Menu is empty!\n"; return;}
        cout<<"\n--- Menu ---\n";
        for(auto &item : menu)
            item.display();
    }

    void placeOrder(){
        if(menu.empty()) { cout<< "Menu is empty! Cannot place order.\n"; return;}
        
        Order order(nextOrderId++);
        int choice, quantity;

        while(true){
            viewMenu();
            cout<<"Enter Menu Item ID to and to order (0 to finish)";
            cin>> choice;
            if(choice == 0) break;

            auto it = find_if(menu.begin(),menu.end(),[choice](MenuItem &m) {return m.getId() == choice;});

            if(it!= menu.end()){
                cout<<"Enter quantity: "; cin>> quantity;
                order.addItem(*it, quantity);

            }else{
                cout<<"Invalid Menu ID !\n";
            }
        }
        orders.push_back(order);
        cout<<"Order Placed Successfully!\n";
        order.displayOrder();
    }

    void viewOrders(){
        if (orders.empty()) {cout<<"No orders yet!\n"; return;}
        cout<<"\n--- All Orders---\n";
        for (auto &o : orders)
            o.displayOrder();
    }

    void saveMenu(){
        ofstream file(menuFile);
        for (auto &item :menu)
            file<<item.serialize()<<endl;
        file.close();
    }

    void loadMenu(){
        ifstream file(menuFile);
        string line;
        while(getline(file,line)){
            menu.push_back(MenuItem:: deserialize(line));
        }
        file.close();
    }

    void saveOrders(){
        ofstream file(ordersFile);
        for (auto &o : orders)
            file<<o.serialize()<<endl;
        file.close();
    }

    void loadOrders(){
        ifstream file(ordersFile);
        string line;
        while(getline(file,line))
            nextOrderId++;
        file.close();
    }

    void exitSystem(){
        saveMenu();
        saveOrders();
        cout<<"Data saved. Exiting system.\n";
    }


};


int main(){
    RestaurantManager manager;
    int choice ;


    cout<<"Welcome to the Restaurant Management System !\n";

    while(true){
        cout<<"\n ---Menu---\n";
        cout<<"1. Add Menu Item\n";
        cout<<"2. View Menu\n";
        cout<<"3. Place Order\n";
        cout<<"4. View Orders\n";
        cout<<"5. Exit\n";
        cout<<"Enter choice: ";
        cin>> choice;

        switch(choice){
            case 1: manager.addMenuItem(); break;
            case 2: manager.viewMenu(); break;
            case 3: manager.placeOrder(); break;
            case 4: manager.viewOrders(); break;
            case 5: manager.exitSystem(); return 0;
            default: cout<<"Invalid Choice!\n";
        }
    }

    return 0;
}
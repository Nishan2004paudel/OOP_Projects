#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class Shape{
public: 
    virtual double area() const = 0;
    virtual void input() = 0;
    virtual string getName() const = 0;
    virtual ~Shape() {}
};

class Rectangle: public Shape{
private: 
    double length, width;
public:
    void input() override{
        cout<<"Enter length and width: ";
        cin>>length>> width;
    }
    double area() const override{
        return length * width;
    }
    string getName() const override{
        return "Rectangle";
    }
};

class Circle : public Shape{
private:
    double radius;
public: 
    void input() override {
        cout<< "Enter radius: ";
        cin>> radius;

    }
    double area() const override{
        return M_PI * radius * radius;
    }
    string getName() const override{
        return "Circle";
    }
};

class Triangle : public Shape{
private:
    double base, height;
public: 
    void input() override{
        cout<< "Enter base and height: ";
        cin>>base>> height;
    }

    double area() const override{
        return 0.5* base* height;
    }
    string getName() const override{
        return "Triangle";
    }
};

int main(){
    vector<Shape*> shapes;
    int choice;

    while (true){
        cout<< "\n1. Rectangle";
        cout<<"\n2. Circle";
        cout<<"\n3. Triangle";
        cout<<"\n4. Calculate Areas and Exit";
        cout<<"\nChoose Shape: ";
        cin>>choice;

        if(choice == 4)
            break;

        Shape* shape = nullptr;

        if (choice == 1)
            shape = new Rectangle();
        else if(choice == 2)
            shape = new Circle();
        else if(choice == 3)
            shape = new Triangle();
        else{
            cout<<"Invalid Choice\n";
            continue;
        }

        shape-> input();
        shapes.push_back(shape);
        cout << "Shape added successfully!\n" << flush;
    }
    cout<<"\n=== Calculated Areas ===\n";
    cout << "Total shapes: " << shapes.size() << "\n" << flush;
    for (const Shape* s: shapes){
        cout<<s->getName()<<" Area: "<<s->area()<<endl;
    }

    for (Shape* s : shapes){
        delete s;
    }

    return 0;
}

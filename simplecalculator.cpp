#include <iostream>
using namespace std;

double add(double a, double b);
double subtract(double a, double b);
double multiply(double a, double b);
double divide(double a, double b);

int main(){
    double num1, num2;
    char operation;

    cout<<"Simple Calculator"<<endl;
    cout<<"Enter first number: ";
    cin>>num1;

    cout<<"Enter operation (+,-,*,/): ";
    cin>>operation;

    cout<<"Enter second number: ";
    cin>>num2;

    switch (operation){
        case '+':
            cout<< "Result: "<< add(num1, num2)<<endl;
            break;
        case '-':
            cout<<"Result: "<< subtract(num1,num2)<<endl;
            break;
        case '*':
            cout<< "Result: "<< multiply(num1, num2)<< endl;
            break;
        case '/':
            cout<< "Result: "<< divide(num1, num2)<< endl;
    }
    return 0;
}
double add(double a , double b){
    return a + b;
}
double subtract(double a, double b){
    return a - b;
}
double multiply(double a, double b){
    return a * b;
}
double divide(double a, double b){
    return a/ b;
}
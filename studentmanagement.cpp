#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int MAX_STUDENTS = 100;
struct Student{
    int id;
    string name;
    int age;
};

void showMenu();
void addStudent(Student students[],int &count);
void viewStudents(Student students[], int count);
void saveToFile(Student students[],int count);
void loadFromFile(Student students[], int &count);

int main(){
    Student students[MAX_STUDENTS];
    int studentCount = 0;
    int choice;

    loadFromFile(students, studentCount);
    while(true){
        showMenu();
        cin>> choice;

        switch(choice){
            case 1:
                addStudent(students, studentCount);
                break;
            case 2:
                viewStudents(students, studentCount);
                break;
            case 3:
                saveToFile(students, studentCount);
                break;
            case 4: 
                saveToFile(students, studentCount);
                cout<< "Exiting program. Data saved."<<endl;
                return 0;
            default: 
                cout<< "Invalid Choice. "<<endl;
        }
    }
}
void showMenu(){
    cout<< "\n1. Add Student";
    cout<<"\n2. View Student";
    cout<<"\n3. Save to File";
    cout<<"\n4. Exit";
    cout<<"\n Enter choice: ";
}

void addStudent(Student students[], int &count){
    if(count >= MAX_STUDENTS){
        cout<< "Student list full!"<<endl;
        return;
    }

    cout<< "Enter ID: ";
    cin>> students[count].id;
    cin.ignore();
    cout<<"Enter Name: ";
    getline(cin, students[count].name);

    cout<< "Enter Age: ";
    cin>>students[count].age;

    count++;
    cout<<"Student added successfully."<<endl;
}

void viewStudents(Student students[],int count){
    if (count ==0){
        cout<< "No students available. "<<endl;
        return;
    }

    cout<<"\nStudent Records: \n";
    for (int i = 0; i< count; i++){
        cout<< "ID: "<<students[i].id<< ", Name: "<<students[i].name<<", Age: "<<students[i].age<<endl;

    }
}

void saveToFile(Student students[], int count){
    ofstream file("students.txt");

    for (int i = 0; i< count; i++){
        file<< students[i].id<<","<<students[i].name<<","<<students[i].age<<endl;
    }

    file.close();
    cout<<"Data saved to file."<<endl;
}


void loadFromFile(Student students[], int &count){
    ifstream file("students.txt");
    count = 0;

    while (file>> students[count].id){
        file.ignore();
        getline(file, students[count].name, ',');
        file>> students[count].age;
        count++;
    }
    file.close();
}

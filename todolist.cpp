#include <iostream>
#include <string>

using namespace std;

const int MAX_TASKS = 100;

void showMenu();
void addTask(string tasks[], int &count);
void viewTasks(string tasks[], int count);
void deleteTask(string tasks[], int &count);

int main(){
    string tasks[MAX_TASKS];
    int taskCount= 0;
    int choice;

    while(true){
        showMenu();

        cin>> choice;
        switch (choice){
            case 1:
                addTask(tasks,taskCount);
                break;
            case 2:
                viewTasks(tasks, taskCount);
                break;
            case 3:
                deleteTask(tasks,taskCount);
                break;
            case 4:
                cout<< "Exiting To-Do List. Good Bye!"<< endl;
                return 0;
            default:
                cout<< "invalid choice. Try again."<< endl;
        }
    }
}
void showMenu(){
    cout<< "\n1. Add Task";
    cout<< "\n2. View Tasks";
    cout<<"\n3. Delete Task";
    cout<<"\n4. Exit";
    cout<<"\nEnter choice: ";
}

void addTask(string tasks[],int &count){
    if (count >= MAX_TASKS){
        cout<<"Task List Full!"<<endl;
        return;
    }
    cin.ignore();
    cout<< "Enter task: ";
    getline(cin, tasks[count]);
    count++;

    cout<< "Task added successfully."<<endl;
}

void viewTasks(string tasks[],int count){
    if(count == 0){
        cout<<"No tasks available."<<endl;
        return;
    }

    cout<< "\n Your Tasks: \n";
    for (int i = 0; i< count; i++){
        cout<< i+1<<". "<<tasks[i]<<endl;
    }
}

void deleteTask(string tasks[], int &count){
    if(count == 0){
        cout<< "No tasks to delete. "<<endl;
        return;
    }

    int index;
    viewTasks(tasks, count);
    cout<< "Enter task number to delete: ";
    cin>> index;

    if(index < 1 || index > count){
        cout<< "Invalid task number."<<endl;
        return;
    }

    for (int i = index -1; i< count-1; i++){
        tasks[i] = tasks[i+1];
    }

    count --;
    cout<< "Task deleted successfully. "<<endl;
}
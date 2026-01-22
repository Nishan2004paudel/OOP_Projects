#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>
#include <sstream>
#include <cstring>

using namespace std;

vector<char*> parseCommand(string input){
    vector<char*> args;
    stringstream ss(input);
    string token;

    while (ss>>token){
        char *arg = new char[token.size()+1];
        strcpy(arg, token.c_str());
        args.push_back(arg);
    }

    args.push_back(nullptr);
    return args;
}

int main(){
    string input;

    while(true){
        char cwd[1024];
        getcwd(cwd, sizeof(cwd));

        cout<<"mini-shell: "<<cwd<<"$ ";
        getline(cin,input);

        if(input.empty())
            continue;

        if (input == "exit"){
            cout<<"Exiting shell.\n";
            break;
        }

        if(input.substr(0,2)=="cd"){
            string path = input.substr(3);
            if (chdir(path.c_str())!= 0){
                perror("cd failed");
            }
            continue;
        }

        pid_t pid = fork();

        if (pid == 0){
            vector<char*> args = parseCommand(input);
            execvp(args[0],args.data());

            perror("Command Failded.");
            exit(1);
        }
        else if(pid >0){
            wait(nullptr);
        }
        else{
            perror("Fork Failed");
        }
    }
    return 0;
}
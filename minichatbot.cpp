#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>

using namespace std;

class Chatbot{
private:
    unordered_map<string, string> knowledge;
    const string filename = "chatbot_data.txt";

public:
    Chatbot(){
        loadKnowledge();
    }
    void loadKnowledge(){
        ifstream file(filename);
        string line;
        while(getline(file,line)){
            size_t sep = line.find('|');
            if (sep != string::npos){
                string question = line.substr(0,sep);
                string answer = line.substr(sep+1);
                knowledge[question]= answer;
            }

        }
        file.close();
    }

    void saveKnowledge(){
        ofstream file(filename);
        for(auto &pair: knowledge){
            file<<pair.first<<"|"<<pair.second<<endl;
        }
        file.close();
    }

    void greet(){
        cout<<"Hello! I am your friendly chatbot. Type 'exit' to quit.\n";
    }

    void chat(){
        string input;
        while(true){
            cout<<"\n You:";
            cin.ignore();
            getline(cin,input);

            if(input== "exit"){
                cout<<"Chatbot: Goodbye!\n";
                break;
            }

            for(auto &c: input) c= tolower(c);

            if(knowledge.find(input) != knowledge.end()){
                cout<<"Chatbot: "<<knowledge[input]<<endl;
            }else{
                string response;
                cout<<"Chatbot: I don't know the answer. How should I respond? ";
                getline(cin,response);
                knowledge[input] = response;
                cout<<"Chatbot: Got it! It will remember that.\n";

            }
        }
        saveKnowledge();
    }
};

int main(){
    Chatbot bot;
    bot.greet();
    bot.chat();

    return 0;
}


#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(){
    srand(time(0));

    int secretNumber = rand()% 100 + 1;
    int guess;
    int attempts = 0;
    cout<<"Welcome to Number Guessing Game! "<< endl;
    cout<<"I have chosen a number between 1 and 100"<< endl;

    while(true){
        cout<< "Enter your guess: ";
        cin >> guess;
        attempts++;
        if (guess > secretNumber){
            cout<< "Too high!"<< endl;
        }
        else if(guess < secretNumber){
            cout<< "Too Low!"<< endl;
        }
        else{
            cout<< "Correct! You guessed it in "<<attempts<< " attempts. "<<endl;
            break;

        }
    }
    return 0;
}
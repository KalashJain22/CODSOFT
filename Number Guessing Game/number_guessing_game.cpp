#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;

int main() {
    int range, guess, times = 0;
    char choice;

    cout<< endl << "----------------------------------------------------------" << endl;
    cout<< "\t*** Welcome To Number Guessing Game ***" << endl;

    play:
    cout<< endl << "Please enter the range of the number. \n(Starting from 1): ";
    cin >> range;

    srand(time(0));
    int random = (rand() % range) + 1; //Generates a random number.
    
    do {
        cout<< endl << "Enter your guess (1 to " << range << "): ";
        cin>> guess;
        times++;

        if(guess == random) {
            cout<< "\nYou have successfuly guess the number in " << times << " times." << endl;
            times = 0;
            goto start;
        } else if(guess > random) {
            cout<< "Your guess is higher than the number." << endl;
        } else {
            cout<< "Your guess is lower than the number." << endl;
        }

    } while(guess != random);

    start:
    while (true) {
        cout<< endl << "Do you want to play again(y for yes/n for no): ";
        cin >> choice;
        if(choice == 'y') {
            goto play;
        } else {
            cout<< endl << "\t*** Thank Yoy For Playing ***" <<endl;
            return 0;
        }
    }

}

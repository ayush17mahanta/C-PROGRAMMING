#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
using namespace std;

int main() {
    srand(time(0)); // Initialize random seed
    int number = rand() % 100 + 1, guess;

    cout << "Guess the number (between 1 and 100): ";

    while (!(cin >> guess)) {
        cout << "Invalid input. Please enter a number: ";
        cin.clear(); // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
    }

    while (guess != number) {
        if (guess < number) {
            cout << "Too low! Try again: ";
        } else {
            cout << "Too high! Try again: ";
        }

        while (!(std::cin >> guess)) {
            cout << "Invalid input. Please enter a number: ";
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        }
    }

    cout << "Congratulations! You guessed the correct number!" << endl;
    return 0;
}

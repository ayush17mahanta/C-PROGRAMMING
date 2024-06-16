#include <iostream>
using namespace std;

int main() {
    char operation;
    double num1, num2, result;

    cout << "Enter first number: ";
    while (!(cin >> num1)) {
        cout << "Invalid input. Please enter a number: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    cout << "Enter second number: ";
    while (!(cin >> num2)) {
        cout << "Invalid input. Please enter a number: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    cout << "Enter operation (+, -, *, /): ";
    cin >> operation;

    switch (operation) {
        case '+':
            result = num1 + num2;
            break;
        case '-':
            result = num1 - num2;
            break;
        case '*':
            result = num1 * num2;
            break;
        case '/':
            if (num2 != 0) {
                result = num1 / num2;
            } else {
                cout << "Error: Division by zero is not allowed." << endl;
                return 1;
            }
            break;
        default:
            cout << "Invalid operation. Please choose from +, -, *, /." << endl;
            return 1;
    }

    cout << "Result: " << result << endl;

    return 0;
}

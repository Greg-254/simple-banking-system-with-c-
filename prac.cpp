#include <iostream>
#include <string>  // For string handling
using namespace std;

int balance = 10000;
const int PIN = 1234;  // Pre-defined 4-digit PIN for simplicity

void displaymenu() {
    cout << "=================================================" << "\n";
    cout << "                        MENU                        " << "\n";
    cout << "=================================================" << "\n";
    cout << "       1. Balance    " << "\n";
    cout << "       2. Deposit    " << "\n";
    cout << "       3. Withdrawal    " << "\n";
    cout << "       4. Transfer  " << "\n";
    cout << "       5. Exit   " << "\n";
}

int bal() {
    return balance;
}

int deposit(int dep) {
    balance += dep;
    return balance;
}

int withdraw(int amount) {
    if (amount > balance) {
        cout << "Insufficient balance!" << "\n";
    } else {
        balance -= amount;
    }
    return balance;
}

int transfer(int amount, string number, int entered_pin) {
    if (amount > balance) {
        cout << "Insufficient balance to transfer!" << "\n";
    } else if (entered_pin != PIN) {
        cout << "Incorrect PIN! Transfer failed." << "\n";
    } else {
        balance -= amount;
        cout << "Transfer to " << number << " successful!" << "\n";
    }
    return balance;
}

bool verifyPin() {
    int entered_pin;
    for (int attempts = 0; attempts < 3; attempts++) { // Allow 3 attempts
        cout << "Enter your 4-digit PIN: ";
        cin >> entered_pin;

        if (entered_pin == PIN) {
            return true; // PIN is correct
        } else {
            cout << "Incorrect PIN! You have " << (2 - attempts) << " attempts left." << "\n";
        }
    }
    cout << "Too many incorrect attempts. Operation denied." << "\n";
    return false; // PIN is incorrect after 3 attempts
}

int main() {
    string ussd_code;
    int choice, amount;
    string transfer_number;
    char confirm = 'y'; // Declare and initialize confirm

    // Simulate USSD input
    cout << "Please enter USSD code (e.g., *537#): ";
    cin >> ussd_code;

    // Check if the input matches *537#
    if (ussd_code == "*537#") {
        while (confirm == 'y' || confirm == 'Y') {
            displaymenu();
            cout << "Enter your choice (1-5): \n";
            cin >> choice;

            switch (choice) {
                case 1: // Balance
                    if (verifyPin()) {
                        cout << "Your account balance is " << bal() << "\n";
                    }
                    break;

                case 2: // Deposit
                    if (verifyPin()) {
                        cout << "Enter the deposit amount: ";
                        cin >> amount;
                        cout << "Your updated account balance is " << deposit(amount) << '\n';
                    }
                    break;

                case 3: // Withdrawal
                    if (verifyPin()) {
                        cout << "Enter the amount to withdraw: ";
                        cin >> amount;
                        cout << "Your updated account balance is " << withdraw(amount) << '\n';
                    }
                    break;

                case 4: // Transfer
                    if (verifyPin()) {
                        cout << "Enter the recipient's phone number: ";
                        cin >> transfer_number;
                        cout << "Enter the amount to transfer: ";
                        cin >> amount;
                        cout << "Enter your 4-digit PIN to confirm: ";
                        int entered_pin; // Declare entered_pin for transfer confirmation
                        cin >> entered_pin;
                        cout << "Your updated account balance is " << transfer(amount, transfer_number, entered_pin) << '\n';
                    }
                    break;

                case 5: // Exit
                    cout << "Exiting the program." << "\n";
                    return 0; // Exit the program

                default:
                    cout << "Invalid choice!" << "\n";
                    break;
            }

            // Ask if the user wants to continue
            cout << "\nPress 'y' or 'Y' to continue, or any other key to exit: ";
            cin >> confirm; // Get confirmation from the user
        }
    } else {
        cout << "Invalid USSD code. Exiting program." << endl;
    }

    return 0;
}

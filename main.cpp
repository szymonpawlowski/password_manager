#include "Vault.h"

#include <string>
#include <iostream>
#include <filesystem>

using namespace std;

int main() {
    Vault vault;

    if (!filesystem::exists("vault.dat")) {
        if (vault.initializeVault()) {
            cout << "Registration successfull! Proceeding to log in...\n";
        } else {
            cout << "Error during initialization!";
            return 1;
        }
    }

    string password;
    bool loggedIn = false;

    while (!loggedIn) {
        cout << "--- Log in ---\n";
        cout << "Insert password: ";
        getline(cin, password);

        if (vault.unlockVault(password)) {
            loggedIn = true;
            cout << "Successfully logged in!" << endl;
        } else {
            cout << "Incorrect password!" << endl;
        }
    }

    int choice = 0;

    while (choice != 4) {
        cout << "--- MAIN MENU ---" << endl;
        cout << "1. Show all passwords" << endl;
        cout << "2. Add new password" << endl;
        cout << "3. Remove existing password" << endl;
        cout << "4. Exit" << endl;
        cin >> choice;

        if (choice == 1) {
            cout << "Show all passwords (WIP)" << endl;
            // TODO: display passwords
        } else if (choice == 2) {
            cout << "Add new password (WIP)" << endl;
            // TODO: add new password
        } else if (choice == 3) {
            cout << "Remove existing password (WIP)" << endl;
            // TODO: remove existing password
        }
    }

    cout << "Vault locked" << endl;

    return 0;
}
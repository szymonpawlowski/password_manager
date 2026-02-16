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
        cout << "2. Add new entry" << endl;
        cout << "3. Remove entry" << endl;
        cout << "4. Exit" << endl;
        cin >> choice;

        if (choice == 1) {
            cout << "Show all passwords (WIP)" << endl;
            // TODO: display passwords
        } else if (choice == 2) {
            cout << "--- Adding new entry ---" << endl;

            string s;
            string u;
            string l;
            string p;

            cout << "Enter service name: ";
            cin >> s;
            cout << "Enter username: ";
            cin >> u;
            cout << "Enter login: ";
            cin >> l;
            cout << "Enter password: ";
            cin >> p;

            vault.addEntry(s, u, l, p);

        } else if (choice == 3) {
            cout << "--- Removing existing entry --- (WIP)" << endl;
            // TODO: remove existing password
        }
    }

    cout << "Vault closed" << endl;

    return 0;
}
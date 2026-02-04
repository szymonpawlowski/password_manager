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
            system("cls");
            cout << "Successfully logged in!" << endl;
        } else {
            system("cls");
            cout << "Incorrect password!" << endl;
        }
    }

    return 0;
}
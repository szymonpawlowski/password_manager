#include "picosha2.h"
#include "PasswordEntry.h"
#include "Vault.h"

#include <fstream>
#include <string>
#include <iostream>

using namespace std;

int main() {
    string masterPassword;
    string salt = "PasswordManager";

    cout << "--- Password Manager Setup ---" << endl;
    cout << "Set master password: ";
    cin >> masterPassword;

    string toHash = masterPassword + salt;
    string hashedPassword = picosha2::hash256_hex_string(toHash);

    cout << "Hashed password: " << hashedPassword << endl;

    return 0;
}
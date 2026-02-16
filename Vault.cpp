#include "Vault.h"
#include "picosha2.h"

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

Vault::Vault() {}

Vault::~Vault() {
    this->entries.clear();
    this->masterKey = "";
}

bool Vault::initializeVault() {
    cout << "--- Password Manager Setup ---" << endl;
    cout << "Set master password: ";
    cin >> masterKey;

    string hashKey = masterKey + SALT;

    ofstream file("vault.dat");
    if (!file.is_open()) return false;

    string hashedPassword = picosha2::hash256_hex_string(hashKey);

    file << hashedPassword << "\n";
    file.close();

    return true;
}

bool Vault::unlockVault(string key) {
    ifstream file("vault.dat");
    if (!file.is_open()) return false;

    string storedHash;
    getline(file, storedHash);
    file.close();

    string hashedPassword = picosha2::hash256_hex_string(key + SALT);

    if (hashedPassword == storedHash) {
        this->masterKey = key;
        return true;
    }

    return false;
}

void Vault::lockVault() {
    // TODO: add logging out of vault
}

void Vault::addEntry(string s, string u, string l, string p) {
    PasswordEntry newEntry(s, u, l, p);
    this->entries.push_back(newEntry);

    ofstream file("vault.dat", ios::app);

    if (file.is_open()) {
        file << s << " | " << u << " | " << l << " | " << p << endl;
        file.close();
        cout << "Entry added successfully!" << endl;
    } else {
        cout << "Adding entry failed!" << endl;
    }

}

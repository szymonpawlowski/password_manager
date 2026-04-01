#include "Vault.h"
#include "picosha2.h"

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

string trim(const string& str) {
    size_t first = str.find_first_not_of(' ');
    if (string::npos == first) return str;
    size_t last = str.find_last_not_of(' ');

    return str.substr(first, (last - first + 1));
}

string Vault::cipher(const string& input) {
    string output = input;
    for (int i=0; i<input.length(); i++) {
        output[i] = input[i] ^ masterKey[i % masterKey.length()];
    }
    return output;
}

string Vault::toHex(const string& input) {
    stringstream ss;
    ss << hex << setfill('0');
    for (size_t i; i < input.length(); i++) {
        ss << setw(2) << static_cast<int>(static_cast<char>(input[i]));
    }
    return ss.str();
}

string Vault::fromHex(const string& input) {
    string output;
    if (input.length() % 2 != 0) return "";

    for (size_t i = 0; i < input.length(); i += 2) {
        string byteString = input.substr(i, 2);
        char byte = static_cast<char>(stoi(byteString, nullptr, 16));
        output.push_back(byte);
    }
    return output;
}

Vault::Vault() {}

Vault::~Vault() {
    this->masterKey = "";
    this->entries.clear();
}

bool Vault::initializeVault() {
    cout << "--- Password Manager Setup ---" << endl;
    cout << "Set master password: ";
    getline(cin >> ws, masterKey);
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
        loadEntries();
        return true;
    }

    return false;
}

void Vault::loadEntries() {
    ifstream file("vault.dat");
    if (!file.is_open()) return;

    string line;
    getline(file, line);

    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string s, u, l, cipheredP;

        string temp;
        if (getline(ss, temp, '|')) s = trim(temp);
        if (getline(ss, temp, '|')) u = trim(temp);
        if (getline(ss, temp, '|')) l = trim(temp);

        string tempHex;
        if (getline(ss, tempHex)) {
            string encrypted = fromHex(trim(tempHex));
            string p = cipher(encrypted);
            entries.emplace_back(s, u, l, p);
        }
    }

    file.close();
}

void Vault::updateFile() {
    ifstream inFile("vault.dat");
    string hash;
    getline(inFile, hash);
    inFile.close();

    ofstream outFile("vault.dat");
    if (outFile.is_open()) {
        outFile << hash << "\n";

        for (const auto& entry : entries) {
            outFile << entry.getServiceName() << " | "
                    << entry.getUsername() << " | "
                    << entry.getLogin() << " | "
                    << entry.getPassword() << "\n";
        }

        outFile.close();
    }

}

void Vault::addEntry(string s, string u, string l, string p) {
    PasswordEntry newEntry(s, u, l, p);
    this->entries.push_back(newEntry);

    ofstream file("vault.dat", ios::app);

    if (file.is_open()) {
        file << s << " | " << u << " | " << l << " | " << toHex(cipher(p)) << endl;
        file.close();
        cout << "Entry added successfully!" << endl;
    } else {
        cout << "Adding entry failed!" << endl;
    }

}

void Vault::removeEntry(string s) {
    vector<int> matchesIndexes;

    for (int i = 0; i < entries.size(); i++) {
        if (entries[i].getServiceName() == s) {
            matchesIndexes.push_back(i);
        }
    }

    if (matchesIndexes.empty()) {
        cout << "No matches found!" << endl;
        return;
    }

    int indexToRemove = -1;

    if (matchesIndexes.size() > 0) {
        for (int i = 0; i < matchesIndexes.size(); i++) {
            int id = matchesIndexes[i];
            cout << i+1 << ". " << entries[id].getServiceName() << "\n";
            cout << "\t" << "- USERNAME: " << entries[id].getUsername() << "\n";
            cout << "\t" << "- LOGIN: " << entries[id].getLogin() << "\n";
            cout << "\t" << "- PASSWORD: " << entries[id].getPassword() << "\n";
        }
        int choice;
        cout << "\nChoose an entry to remove: ";
        cin >> choice;
        indexToRemove = matchesIndexes[choice-1];

    }

    char confirm;
    cout << "Are you sure you want to remove this entry? [Y/N]" << endl;
    cin >> confirm;

    if (confirm == 'y' || confirm == 'Y') {
        entries.erase(entries.begin() + indexToRemove);
        updateFile();
        cout << "Entry deleted successfully!" << endl;
    } else {
        cout << "Deletion cancelled." << endl;
    }
}

void Vault::showAllEntries() {
    if (entries.empty()) return;

    cout << "\n" << "=== ENTRIES ===" << endl;
    for (int i = 0; i < entries.size(); i++) {
        cout << i+1 << ". " << entries[i].getServiceName() << "\n";
        cout << "\t" << "- USERNAME: " << entries[i].getUsername() << "\n";
        cout << "\t" << "- LOGIN: " << entries[i].getLogin() << "\n";
        cout << "\t" << "- PASSWORD: " << entries[i].getPassword() << "\n";
        cout << "\n";
    }
}

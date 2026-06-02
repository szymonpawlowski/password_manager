#include "Vault.h"
#include "picosha2.h"

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <random>
#include <sstream>

using namespace std;


Vault::Vault() {}

Vault::~Vault() {
    this->vaultName = "";
    this->salt = "";
    this->hashKey = "";
    this->entries.clear();
}

bool Vault::initializeVault(
    const string& vaultName,
    const string& vaultKey, 
    const string& confirmVaultKey
) {
    if (vaultName.empty() || vaultKey.empty()) {
        return false;
    }

    if (confirmVaultKey != vaultKey) {
        return false;
    }

    this->vaultName = vaultName;
    this->salt = generateSalt();
    this->hashKey = hash(vaultKey, salt);

    return saveVaultMetadata(vaultName, salt, hashKey);
}

string Vault::generateSalt() {
    random_device rd;
    uniform_int_distribution<int> dist(0, 255);

    stringstream ss;

    for (int i = 0; i < 16; i++) {
        ss << hex << setw(2) << setfill('0') << dist(rd);
    }

    return ss.str();
}

string Vault::hash(const string& password, const string& salt) {
    string saltedPassword = password + salt;
    return picosha2::hash256_hex_string(saltedPassword);    // temp hashing
}

bool Vault::saveVaultMetadata(const string& vaultName, const string& salt, const string& hashKey) {
    ofstream file("vault.json");

    if (!file.is_open()) {
        return false;
    }

    file << "{\n";
    file << "  \"vaultName\": \"" << vaultName << "\",\n";
    file << "  \"salt\": \"" << salt << "\",\n";
    file << "  \"hashKey\": \"" << hashKey << "\"\n";
    file << "}";

    file.close();

    return true;
}

bool Vault::unlockVault(const string& vaultKey) {
    if (hash(vaultKey, salt) == hashKey) {   // TODO: replace with hashed password
        return true;
    }

    return false;
}

void Vault::loadEntries() {
    // read vault.json file > load entries to vector (sort alphabetically)
}

void Vault::updateFile() {
    // after adding, removing or updating any entries
}

void Vault::addEntry(string s, string u, string l, string p) {
    // opens vault file adds new entry
}

void Vault::removeEntry(string s) {
    // removes selected entry - selection through click or search (WIP)
}

void Vault::showAllEntries() {
    // renders list of all entries (?)
}

string Vault::getVaultName() const {
    return this->vaultName;
}

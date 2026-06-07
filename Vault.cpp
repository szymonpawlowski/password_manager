#include "Vault.h"
#include "picosha2.h"

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <random>
#include <sstream>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;


Vault::Vault() {}

Vault::~Vault() {
    this->vaultName = "";
    this->salt = "";
    this->hashKey = "";
    this->entries.clear();
}

bool Vault::initializeVault(
    const string& inputVaultName,
    const string& inputVaultKey, 
    const string& confirmVaultKey
) {
    if (inputVaultName.empty() || inputVaultKey.empty()) {
        return false;
    }

    if (confirmVaultKey != inputVaultKey) {
        return false;
    }

    this->vaultName = inputVaultName;
    this->salt = generateSalt();
    this->hashKey = hash(inputVaultKey, this->salt);

    return saveVaultMetadata(this->vaultName, this->salt, this->hashKey);
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

bool Vault::saveVaultMetadata(const string& inputVaultName, const string& inputSalt, const string& inputHashKey) {
    ofstream file("vault.json");

    if (!file.is_open()) {
        return false;
    }

    file << "{\n";
    file << "  \"vaultName\": \"" << inputVaultName << "\",\n";
    file << "  \"salt\": \"" << inputSalt << "\",\n";
    file << "  \"hashKey\": \"" << inputHashKey << "\"\n";
    file << "}";

    file.close();

    return true;
}

bool Vault::loadVaultMetadata() {
    ifstream file("vault.json");

    if (!file.is_open()) {
        return false;
    }

    json vaultData;
    file >> vaultData;

    this->vaultName = vaultData["vaultName"];
    this->salt = vaultData["salt"];
    this->hashKey = vaultData["hashKey"];

    return true;
}

bool Vault::unlockVault(const string& inputVaultKey) {
    if (!loadVaultMetadata()) {
        return false;
    }

    string inputHash = hash(inputVaultKey, this->salt);

    return inputHash == this->hashKey;
}

string Vault::getVaultName() const {
    return this->vaultName;
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



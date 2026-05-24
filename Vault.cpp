#include "Vault.h"
#include "picosha2.h"

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;


Vault::Vault() {}

Vault::~Vault() {
    this->vaultName = "";
    this->vaultKey = "";

    this->entries.clear();
}

bool Vault::initializeVault(const string& vaultName, const string& vaultKey, const string& confirmVaultKey) {
    if (vaultName != "" && vaultKey != "" && confirmVaultKey == vaultKey) {
        this->vaultName = vaultName;
        this->vaultKey = vaultKey;

        return true;
    }

    return false;
}

bool Vault::unlockVault(const string& vaultKey) {
    if (vaultKey == "haslo123") {   // TODO: replace with hashed password
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

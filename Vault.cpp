#include "Vault.h"

Vault::Vault() {}

Vault::~Vault() {
    this->entries.clear();
    this->masterKey = "";
}


void Vault::unlockVault(string key) {
    // TODO: add logging into vault
}

void Vault::lockVault() {
    // TODO: add logging out of vault
}

void Vault::addEntry(PasswordEntry entry) {
    this->entries.push_back(entry);
}

void Vault::showEntries() {
    for (int i = 0; i < this->entries.size(); i++) {
        this->entries[i].info();
    }
}
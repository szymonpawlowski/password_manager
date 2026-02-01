#include "Vault.h"

#include <fstream>

using namespace std;

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

void Vault::addEntry(string s, string u, string l, string p) {
    this->entries.emplace_back(s, u, l, p);
}

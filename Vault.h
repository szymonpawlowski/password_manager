#ifndef PASSWORD_MANAGER_VAULT_H
#define PASSWORD_MANAGER_VAULT_H

#include "PasswordEntry.h"

#include <vector>
#include <string>

using namespace std;

class Vault {
private:
    vector<PasswordEntry> entries;
    string masterKey;

public:
    Vault();
    void unlockVault(string key);
    void lockVault();
};


#endif //PASSWORD_MANAGER_VAULT_H
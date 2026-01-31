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
        ~Vault();

        void unlockVault(string key);
        void lockVault();

        void addEntry(PasswordEntry entry);
        void showEntries();
};


#endif //PASSWORD_MANAGER_VAULT_H
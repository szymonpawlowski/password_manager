#ifndef PASSWORD_MANAGER_VAULT_H
#define PASSWORD_MANAGER_VAULT_H

#include "PasswordEntry.h"

#include <vector>
#include <string>

using namespace std;

class Vault {
    private:
        string vaultName;
        vector<PasswordEntry> entries;
        string vaultKey;

    public:
        Vault();
        ~Vault();

        bool initializeVault(const string& vaultName, const string& vaultKey, const string& confirmVaultKey);
        bool unlockVault(const string& vaultKey);

        string getVaultName() const;

        void loadEntries();
        void updateFile();
        void addEntry(string s, string u, string l, string p);
        void removeEntry(string s);
        void showAllEntries();
};


#endif
#ifndef PASSWORD_MANAGER_VAULT_H
#define PASSWORD_MANAGER_VAULT_H

#include "PasswordEntry.h"

#include <vector>
#include <string>

using namespace std;

class Vault {
    private:
        string vaultName;
        string salt;
        string hashKey;
        vector<PasswordEntry> entries;
        
    public:
        Vault();
        ~Vault();

        bool initializeVault(const string& inputVaultName, const string& inputVaultKey, const string& confirmVaultKey);

        string generateSalt();
        string hash(const string& password, const string& salt);

        bool saveVaultMetadata(const string& inputVaultName, const string& inputSalt, const string& inputHashKey);
        bool loadVaultMetadata();

        bool unlockVault(const string& inputVaultKey);

        string getVaultName() const;

        void loadEntries();
        void updateFile();
        void addEntry(string s, string u, string l, string p);
        void removeEntry(string s);
        void showAllEntries();
};


#endif
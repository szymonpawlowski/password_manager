#ifndef PASSWORD_MANAGER_VAULT_H
#define PASSWORD_MANAGER_VAULT_H

#include "PasswordEntry.h"

#include <vector>
#include <string>

using namespace std;

class Vault {
    private:
        const string SALT = "PasswordManager4444";
        vector<PasswordEntry> entries;
        string masterKey;

        string cipher(const string& input);
        string toHex(const string& input);
        string fromHex(const string& input);

    public:
        Vault();
        ~Vault();

        bool initializeVault();
        bool unlockVault(string key);

        void loadEntries();
        void updateFile();
        void addEntry(string s, string u, string l, string p);
        void removeEntry(string s);
        void showAllEntries();
};


#endif
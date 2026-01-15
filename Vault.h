#ifndef PASSWORD_MANAGER_VAULT_H
#define PASSWORD_MANAGER_VAULT_H

#include "PasswordEntry.h"

#include <vector>
#include <string>

using namespace std;

class Vault {
private:
    vector<PasswordEntry> passwordEntries;
};


#endif //PASSWORD_MANAGER_VAULT_H
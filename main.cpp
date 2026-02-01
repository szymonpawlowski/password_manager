#include "PasswordEntry.h"
#include "Vault.h"

#include <fstream>

using namespace std;

int main() {
    Vault vault = Vault();
    PasswordEntry entry1 = PasswordEntry("Google", "jkowalski", "email@poczta.com", "haslo123");
    PasswordEntry entry2 = PasswordEntry("Facebook", "Jan Kowalski", "email@poczta.pl", "haslo321");

    vault.addEntry(entry1);
    vault.addEntry(entry2);

    vault.showEntries();
}
#include "PasswordEntry.h"

#include <string>

PasswordEntry::PasswordEntry(std::string useFor, std::string login, std::string password) {
    this->useFor = useFor;
    this->login = login;
    this->password = password;
}

PasswordEntry::~PasswordEntry() {
    this->useFor = "";
    this->login = "";
    this->password = "";
}
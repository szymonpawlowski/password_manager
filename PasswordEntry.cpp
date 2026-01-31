#include "PasswordEntry.h"

#include <string>

PasswordEntry::PasswordEntry(std::string serviceName, std::string login, std::string password) {
    this->serviceName = serviceName;
    this->login = login;
    this->password = password;
}

PasswordEntry::~PasswordEntry() {
    this->serviceName = "";
    this->login = "";
    this->password = "";
}
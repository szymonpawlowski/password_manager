#ifndef PASSWORD_MANAGER_PASSWORDENTRY_H
#define PASSWORD_MANAGER_PASSWORDENTRY_H

#include <string>


class PasswordEntry
{
private:
    std::string serviceName;
    std::string login;
    std::string password;

public:
    PasswordEntry(std::string useFor, std::string login, std::string password);
    ~PasswordEntry();
};


#endif //PASSWORD_MANAGER_PASSWORDENTRY_H
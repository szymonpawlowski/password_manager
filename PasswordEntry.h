#ifndef PASSWORD_MANAGER_PASSWORDENTRY_H
#define PASSWORD_MANAGER_PASSWORDENTRY_H

#include <string>

using namespace std;

class PasswordEntry
{
    private:
        string serviceName;
        string login;
        string password;

    public:
        PasswordEntry(string serviceName, string login, string password);
        ~PasswordEntry();

        void info();
        void editEntry();
};


#endif
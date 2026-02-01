#ifndef PASSWORD_MANAGER_PASSWORDENTRY_H
#define PASSWORD_MANAGER_PASSWORDENTRY_H

#include <string>

using namespace std;

struct PasswordEntry
{
    string serviceName;
    string username;
    string login;
    string password;

    PasswordEntry(string s, string u, string l, string p)
        : serviceName(s), username(u), login(l), password(p) {};
};


#endif
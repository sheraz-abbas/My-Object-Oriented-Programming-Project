#ifndef AUTH_H
#define AUTH_H

#include "globals.h"
#include "Player.h"

// ============================================================
// USER ACCOUNT  --  holds login info + player data
// ============================================================
struct Account
{
    string username;
    string password;
    bool   isAdmin;
    Player player;

    Account();
    Account(string u, string p, bool adm);

    string toStr() const;
};

// ============================================================
// AUTH SYSTEM
// Demonstrates: File Handling, STL map, Exception Handling
// ============================================================
class AuthSystem
{
private:
    map<string, Account> accounts;
    string               filename;

    void load();
    void save();

public:
    AuthSystem();

    Account* login(const string& user, const string& pass);
    bool     signup(const string& user, const string& pass);
    bool     exists(const string& user) const;
    void     update(const Account& acc);

    // Admin features
    void viewUsers()               const;
    void deleteUser(const string& user);

    map<string, Account>& getAll() { return accounts; }
};

#endif

#include "Auth.h"

// ============================================================
// Account
// ============================================================
Account::Account() : isAdmin(false) {}

Account::Account(string u, string p, bool adm)
    : username(u), password(p), isAdmin(adm)
{
    player.setName(u);
}

string Account::toStr() const
{
    return username + "|" + password + "|"
           + (isAdmin ? "1" : "0") + "|" + player.toStr();
}

// ============================================================
// AuthSystem
// ============================================================
AuthSystem::AuthSystem() : filename("users.txt")
{
    load();
    // Create default admin if file was empty
    if (accounts.find("admin") == accounts.end())
    {
        accounts["admin"] = Account("admin", "admin123", true);
        save();
    }
}

void AuthSystem::load()
{
    accounts.clear();
    ifstream f(filename.c_str());
    if (!f.is_open()) return;

    string line;
    while (getline(f, line))
    {
        if (line.empty()) continue;

        istringstream ss(line);
        string        tok;
        vector<string> parts;
        while (getline(ss, tok, '|')) parts.push_back(tok);
        if ((int)parts.size() < 3) continue;

        Account acc;
        acc.username = parts[0];
        acc.password = parts[1];
        acc.isAdmin  = (parts[2] == "1");

        // Rebuild player string from remaining parts
        if ((int)parts.size() >= 4)
        {
            string ps = parts[3];
            for (int i = 4; i < (int)parts.size(); i++) ps += "|" + parts[i];
            acc.player.fromStr(ps);
        }
        else
            acc.player.setName(acc.username);

        accounts[acc.username] = acc;
    }
    f.close();
}

void AuthSystem::save()
{
    ofstream f(filename.c_str());
    map<string, Account>::iterator it;
    for (it = accounts.begin(); it != accounts.end(); ++it)
        f << it->second.toStr() << "\n";
    f.close();
}

Account* AuthSystem::login(const string& user, const string& pass)
{
    if (accounts.find(user) == accounts.end()) return NULL;
    if (accounts[user].password != pass)       return NULL;
    return &accounts[user];
}

bool AuthSystem::signup(const string& user, const string& pass)
{
    if (user.empty() || pass.empty()) return false;
    if (exists(user))                 return false;
    accounts[user] = Account(user, pass, false);
    save();
    return true;
}

bool AuthSystem::exists(const string& user) const
{
    return accounts.find(user) != accounts.end();
}

void AuthSystem::update(const Account& acc)
{
    accounts[acc.username] = acc;
    save();
}

void AuthSystem::viewUsers() const
{
    setColor(C_CYAN); printLine('=', 45);
    cout << "  ALL REGISTERED USERS\n";
    printLine('=', 45);
    resetColor();

    map<string, Account>::const_iterator it;
    int i = 1;
    for (it = accounts.begin(); it != accounts.end(); ++it)
    {
        const Account& a = it->second;
        setColor(a.isAdmin ? C_YELLOW : C_WHITE);
        cout << "  " << i++ << ". " << a.username
             << (a.isAdmin ? " [ADMIN]" : " [Player]")
             << "  Score: " << a.player.getScore() << endl;
    }
    resetColor();
}

void AuthSystem::deleteUser(const string& user)
{
    if (user == "admin")
    {
        setColor(C_RED); cout << "  Cannot delete admin!\n"; resetColor();
        return;
    }
    if (accounts.erase(user))
    {
        save();
        setColor(C_GREEN); cout << "  User deleted.\n"; resetColor();
    }
    else
    {
        setColor(C_RED); cout << "  User not found!\n"; resetColor();
    }
}

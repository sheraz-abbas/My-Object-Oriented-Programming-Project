#include "Scoreboard.h"

// Comparator for STL sort (descending by score)
static bool playerDesc(const Player& a, const Player& b)
{
    return a > b;   // uses Player::operator>
}

Scoreboard::Scoreboard() : filename("scores.txt") { load(); }

void Scoreboard::load()
{
    players.clear();
    ifstream f(filename.c_str());
    if (!f.is_open()) return;

    string line;
    while (getline(f, line))
    {
        if (line.empty()) continue;
        Player p;
        p.fromStr(line);
        players.push_back(p);
    }
    f.close();
    sort(players.begin(), players.end(), playerDesc);
}

void Scoreboard::save()
{
    sort(players.begin(), players.end(), playerDesc);
    ofstream f(filename.c_str());
    int lim = (int)players.size() < 10 ? (int)players.size() : 10;
    for (int i = 0; i < lim; i++)
        f << players[i].toStr() << "\n";
    f.close();
}

void Scoreboard::addOrUpdate(const Player& p)
{
    for (int i = 0; i < (int)players.size(); i++)
    {
        if (players[i] == p)                      // uses Player::operator==
        {
            if (p > players[i]) players[i] = p;  // uses Player::operator>
            sort(players.begin(), players.end(), playerDesc);
            return;
        }
    }
    players.push_back(p);
    sort(players.begin(), players.end(), playerDesc);
}

void Scoreboard::display() const
{
    setColor(C_YELLOW); printLine('*', 45);
    cout << "        TOP SCOREBOARD\n";
    printLine('*', 45);
    resetColor();

    if (players.empty())
    {
        cout << "  No scores yet!\n";
        printLine('*', 45);
        return;
    }

    int lim = (int)players.size() < 5 ? (int)players.size() : 5;
    for (int i = 0; i < lim; i++)
    {
        setColor(i == 0 ? C_YELLOW : C_WHITE);
        cout << "  " << (i + 1) << ". " << players[i] << endl;
    }
    resetColor();
    printLine('*', 45);
}

string Scoreboard::topPlayer() const
{
    if (players.empty()) return "None";
    return players[0].getName();
}

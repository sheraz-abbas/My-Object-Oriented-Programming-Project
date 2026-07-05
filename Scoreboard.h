#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include "globals.h"
#include "Player.h"

// ============================================================
// SCOREBOARD
// Demonstrates: File Handling, STL sort, Operator overloading
// ============================================================
class Scoreboard
{
private:
    vector<Player> players;
    string         filename;

public:
    Scoreboard();

    void load();
    void save();
    void addOrUpdate(const Player& p);
    void display()      const;
    string topPlayer()  const;
};

#endif

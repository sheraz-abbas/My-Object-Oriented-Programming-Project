#ifndef PLAYER_H
#define PLAYER_H

#include "globals.h"
#include "IDisplayable.h"

// ============================================================
// PLAYER CLASS
// Demonstrates: Encapsulation, Operator Overloading,
//               Static Members, IDisplayable interface
// ============================================================
class Player : public IDisplayable
{
private:
    string name;
    int    score;
    int    gamesPlayed;
    int    correctAns;
    int    wrongAns;
    int    hintPoints;

    static int totalPlayers;   // static member -- shared across all objects

public:
    Player();
    Player(string n);

    // Getters / Setters  (Encapsulation)
    void   setName(string n);
    string getName()     const;
    int    getScore()    const;
    int    getGames()    const;
    int    getCorrect()  const;
    int    getWrong()    const;
    int    getHints()    const;
    double getAccuracy() const;

    void addScore(int pts);
    void addWrong();
    void newGame();
    void useHint();
    bool hasHints()      const;

    // Static method
    static int getTotalPlayers();

    // Operator Overloading
    bool    operator>(const Player& o)  const;
    bool    operator<(const Player& o)  const;
    bool    operator==(const Player& o) const;
    Player& operator+=(int pts);

    // friend << overloading
    friend ostream& operator<<(ostream& os, const Player& p);

    // IDisplayable
    void display() const;

    // File helpers
    string toStr()                   const;
    void   fromStr(const string& s);

    ~Player();
};

#endif

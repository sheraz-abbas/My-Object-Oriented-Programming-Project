#include "Player.h"

// static member definition
int Player::totalPlayers = 0;

// ============================================================
// Constructors
// ============================================================
Player::Player()
    : score(0), gamesPlayed(0), correctAns(0), wrongAns(0), hintPoints(2)
{
    totalPlayers++;
}

Player::Player(string n)
    : name(n), score(0), gamesPlayed(0), correctAns(0), wrongAns(0), hintPoints(2)
{
    totalPlayers++;
}

// ============================================================
// Getters / Setters
// ============================================================
void   Player::setName(string n)  { name = n;  }
string Player::getName()    const { return name;         }
int    Player::getScore()   const { return score;        }
int    Player::getGames()   const { return gamesPlayed;  }
int    Player::getCorrect() const { return correctAns;   }
int    Player::getWrong()   const { return wrongAns;     }
int    Player::getHints()   const { return hintPoints;   }

double Player::getAccuracy() const
{
    int total = correctAns + wrongAns;
    if (total == 0) return 0.0;
    return (correctAns * 100.0) / total;
}

void Player::addScore(int pts) { score += pts; correctAns++; }
void Player::addWrong()        { wrongAns++;                 }
void Player::newGame()         { gamesPlayed++;              }
void Player::useHint()         { if (hintPoints > 0) hintPoints--; }
bool Player::hasHints()  const { return hintPoints > 0;     }
int  Player::getTotalPlayers() { return totalPlayers;        }

// ============================================================
// Operator Overloading
// ============================================================
bool Player::operator>(const Player& o)  const { return score > o.score;  }
bool Player::operator<(const Player& o)  const { return score < o.score;  }
bool Player::operator==(const Player& o) const { return name  == o.name;  }

Player& Player::operator+=(int pts)
{
    score += pts;
    correctAns++;
    return *this;
}

ostream& operator<<(ostream& os, const Player& p)
{
    os << p.name
       << " | Score: " << p.score
       << " | Accuracy: " << (int)p.getAccuracy() << "%";
    return os;
}

// ============================================================
// IDisplayable
// ============================================================
void Player::display() const
{
    setColor(C_CYAN);  printLine('-', 42);
    setColor(C_WHITE);
    cout << "  Player   : " << name                    << endl;
    cout << "  Score    : " << score      << " pts"    << endl;
    cout << "  Accuracy : " << (int)getAccuracy() << "%" << endl;
    cout << "  Games    : " << gamesPlayed              << endl;
    cout << "  Hints    : " << hintPoints << " left"   << endl;
    setColor(C_CYAN);  printLine('-', 42);
    resetColor();
}

// ============================================================
// File helpers
// ============================================================
string Player::toStr() const
{
    ostringstream ss;
    ss << name << "|" << score << "|" << gamesPlayed
       << "|" << correctAns << "|" << wrongAns << "|" << hintPoints;
    return ss.str();
}

void Player::fromStr(const string& line)
{
    istringstream ss(line);
    string t;
    int    f = 0;
    while (getline(ss, t, '|'))
    {
        if      (f == 0) name        = t;
        else if (f == 1) score       = atoi(t.c_str());
        else if (f == 2) gamesPlayed = atoi(t.c_str());
        else if (f == 3) correctAns  = atoi(t.c_str());
        else if (f == 4) wrongAns    = atoi(t.c_str());
        else if (f == 5) hintPoints  = atoi(t.c_str());
        f++;
    }
}

Player::~Player() {}

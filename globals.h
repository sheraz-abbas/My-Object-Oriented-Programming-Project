#ifndef GLOBALS_H
#define GLOBALS_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>
#include <stdexcept>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <cctype>
#include <cstdio>
#include <windows.h>
#include <conio.h>

using namespace std;

// ============================================================
// COLORS
// ============================================================
const int C_WHITE  = 15;
const int C_RED    = 12;
const int C_GREEN  = 10;
const int C_YELLOW = 14;
const int C_CYAN   = 11;
const int C_PINK   = 13;
const int C_RESET  = 7;

inline void setColor(int c)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
inline void resetColor() { setColor(C_RESET); }

// ============================================================
// SOUND
// ============================================================
inline void soundCorrect() { Beep(1000, 300); }
inline void soundWrong()   { Beep(400,  500); }
inline void soundWin()     { Beep(1200,200); Beep(1500,200); Beep(1800,400); }
inline void soundTick()    { Beep(700,  100); }

// ============================================================
// UTILITIES
// ============================================================
inline void clrscr() { system("cls"); }

inline void printLine(char c, int n)
{
    setColor(C_CYAN);
    for (int i = 0; i < n; i++) cout << c;
    cout << endl;
    resetColor();
}

inline void pressEnter()
{
    cout << "\n  Press ENTER to continue...";
    cin.ignore();
    cin.get();
}

// ============================================================
// TIMER  (ctime based -- C++98 compatible, no threads)
// Returns true  = player pressed key in time
// Returns false = time ran out
// ============================================================
inline bool runTimer(int seconds)
{
    time_t start   = time(NULL);
    int    prevSec = -1;

    while (true)
    {
        int remaining = seconds - (int)(time(NULL) - start);

        if (remaining != prevSec)
        {
            prevSec = remaining;
            if      (remaining <= 5)  setColor(C_RED);
            else if (remaining <= 10) setColor(C_YELLOW);
            else                      setColor(C_GREEN);
            cout << "\r  Time Left: " << remaining << " sec   ";
            cout.flush();
            resetColor();
            if (remaining > 0 && remaining <= 3) soundTick();
        }

        if (remaining <= 0)
        {
            cout << "\r  TIME IS UP!              " << endl;
            return false;
        }

        if (_kbhit()) return true;
    }
}

#endif

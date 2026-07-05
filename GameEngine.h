#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "globals.h"
#include "Question.h"
#include "Lifeline.h"
#include "Player.h"
#include "Scoreboard.h"
#include "Auth.h"
#include "QuestionBank.h"
#include "DataManager.h"

// ============================================================
// ADMIN PANEL
// ============================================================
class AdminPanel
{
private:
    AuthSystem&   auth;
    QuestionBank& qBank;
    Scoreboard&   board;

    void addQuestion();
    void viewQuestions();
    void manageUsers();
    void viewStats();

public:
    AdminPanel(AuthSystem& a, QuestionBank& q, Scoreboard& s);
    void run();
};

// ============================================================
// GAME SESSION  --  one round of KBC
// ============================================================
class GameSession
{
private:
    Account*      acc;
    QuestionBank& qBank;
    Scoreboard&   board;
    int           sessionScore;

    FiftyFifty   ll1;
    AudiencePoll ll2;
    ExpertAdvice ll3;

    void showHUD(int qNum, int total);
    void showLifelines();
    void saveGame(int qNum);
    int  loadSave();
    void clearSave();
    void endGame(bool won);

public:
    GameSession(Account* a, QuestionBank& q, Scoreboard& s);
    void start();
};

// ============================================================
// GAME ENGINE  --  top-level controller
// ============================================================
class GameEngine
{
private:
    AuthSystem   auth;
    QuestionBank qBank;
    Scoreboard   board;

    Account* doLogin();
    Account* doSignup();
    Account* runLogin();
    void     showBanner();
    void     showRules();

public:
    GameEngine();
    void run();
};

#endif

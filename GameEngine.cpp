#include "GameEngine.h"

// ============================================================
// ADMIN PANEL
// ============================================================
AdminPanel::AdminPanel(AuthSystem& a, QuestionBank& q, Scoreboard& s)
    : auth(a), qBank(q), board(s) {}

void AdminPanel::addQuestion()
{
    clrscr();
    setColor(C_CYAN); cout << "\n  --- ADD QUESTION ---\n\n"; resetColor();

    string q, a, b, c, d, h;
    char   ans;
    int    diff;

    cin.ignore();
    cout << "  Question  : "; getline(cin, q);
    cout << "  Option A  : "; getline(cin, a);
    cout << "  Option B  : "; getline(cin, b);
    cout << "  Option C  : "; getline(cin, c);
    cout << "  Option D  : "; getline(cin, d);
    cout << "  Correct (A/B/C/D): "; cin >> ans;
    cout << "  Difficulty (1=Easy 2=Medium 3=Hard): "; cin >> diff;
    cin.ignore();
    cout << "  Hint      : "; getline(cin, h);

    ans = toupper(ans);

    Question* nq = NULL;
    if      (diff == 1) nq = new EasyQuestion(q,a,b,c,d,ans,h);
    else if (diff == 2) nq = new MediumQuestion(q,a,b,c,d,ans,h);
    else                nq = new HardQuestion(q,a,b,c,d,ans,h);

    qBank.getData().add(nq);

    // Save to file: E|question|a|b|c|d|ans|hint
    ofstream f("questions.txt", ios::app);
    if (f.is_open())
    {
        char dc = (diff==1) ? 'E' : (diff==2) ? 'M' : 'H';
        f << dc << "|" << q << "|" << a << "|" << b << "|"
          << c << "|" << d << "|" << ans << "|" << h << "\n";
        f.close();
    }

    setColor(C_GREEN); cout << "\n  Question added!\n"; resetColor();
    pressEnter();
}

void AdminPanel::viewQuestions()
{
    clrscr();
    setColor(C_CYAN); printLine('=', 45);
    cout << "  QUESTIONS  (" << qBank.count() << " total)\n";
    printLine('=', 45); resetColor();

    int lim = qBank.count() < 20 ? qBank.count() : 20;
    for (int i = 0; i < lim; i++)
    {
        setColor(C_YELLOW);
        cout << "  " << (i+1) << ". [" << qBank.get(i)->getDiff() << "] ";
        resetColor();
        string t = qBank.get(i)->getText();
        cout << (t.length() > 40 ? t.substr(0,40)+"..." : t) << endl;
    }
    pressEnter();
}

void AdminPanel::manageUsers()
{
    while (true)
    {
        clrscr();
        auth.viewUsers();
        setColor(C_WHITE);
        cout << "\n  1. Delete User\n  2. Back\n  Choice: ";
        resetColor();

        int ch; cin >> ch;
        if (ch == 1)
        {
            string u;
            cout << "  Username to delete: "; cin >> u;
            auth.deleteUser(u);
            pressEnter();
        }
        else break;
    }
}

void AdminPanel::viewStats()
{
    clrscr();
    setColor(C_CYAN); printLine('=', 45);
    cout << "  GAME STATISTICS\n";
    printLine('=', 45); resetColor();

    cout << "  Total Questions  : " << qBank.count()             << endl;
    cout << "  Top Player       : " << board.topPlayer()         << endl;
    cout << "  Total Players    : " << Player::getTotalPlayers() << endl;
    cout << endl;
    board.display();
    pressEnter();
}

void AdminPanel::run()
{
    while (true)
    {
        clrscr();
        setColor(C_PINK); printLine('*', 45);
        cout << "           ADMIN PANEL\n";
        printLine('*', 45); resetColor();

        setColor(C_WHITE);
        cout << "\n  1. Add Question\n"
             << "  2. View Questions\n"
             << "  3. Manage Users\n"
             << "  4. View Stats\n"
             << "  5. Back\n"
             << "\n  Choice: ";
        resetColor();

        int ch;
        try
        {
            cin >> ch;
            if (cin.fail()) throw invalid_argument("Enter a number");
            switch (ch)
            {
                case 1: addQuestion();   break;
                case 2: viewQuestions(); break;
                case 3: manageUsers();   break;
                case 4: viewStats();     break;
                case 5: return;
                default: throw invalid_argument("Enter 1-5");
            }
        }
        catch (const invalid_argument& e)
        {
            cin.clear(); cin.ignore(1000, '\n');
            setColor(C_RED); cout << "  Error: " << e.what() << "\n"; resetColor();
            pressEnter();
        }
    }
}

// ============================================================
// GAME SESSION
// ============================================================
GameSession::GameSession(Account* a, QuestionBank& q, Scoreboard& s)
    : acc(a), qBank(q), board(s), sessionScore(0) {}

void GameSession::showHUD(int qNum, int total)
{
    setColor(C_PINK);
    cout << "  " << acc->player.getName()
         << "  |  Session: " << sessionScore << " pts"
         << "  |  Total: "   << acc->player.getScore() << " pts"
         << "  |  Hints: "   << acc->player.getHints()
         << "  |  Q: " << (qNum+1) << "/" << total << "\n";
    resetColor();
}

void GameSession::showLifelines()
{
    cout << "\n  Lifelines: ";
    ll1.display(); cout << "  ";
    ll2.display(); cout << "  ";
    ll3.display(); cout << "\n";
    cout << "  Keys: F=50-50 | P=Poll | E=Expert | H=Hint | S=Save&Quit | Q=Quit\n";
}

void GameSession::saveGame(int qNum)
{
    string fname = acc->username + "_save.txt";
    ofstream f(fname.c_str());
    if (f.is_open())
    {
        f << qNum << "\n" << sessionScore << "\n";
        f.close();
        setColor(C_GREEN); cout << "\n  Game saved!\n"; resetColor();
    }
}

int GameSession::loadSave()
{
    string fname = acc->username + "_save.txt";
    ifstream f(fname.c_str());
    if (!f.is_open()) return 0;

    int qNum = 0, sc = 0;
    f >> qNum >> sc;
    f.close();

    setColor(C_YELLOW);
    cout << "\n  Saved game found at Q" << (qNum+1)
         << " with " << sc << " pts. Resume? (Y/N): ";
    resetColor();
    char ch; cin >> ch;
    if (toupper(ch) == 'Y') { sessionScore = sc; return qNum; }
    return 0;
}

void GameSession::clearSave()
{
    string fname = acc->username + "_save.txt";
    remove(fname.c_str());
}

void GameSession::endGame(bool won)
{
    clrscr();
    setColor(C_CYAN); printLine('*', 45);
    setColor(won ? C_YELLOW : C_RED);
    cout << (won ? "        YOU WON!" : "        GAME OVER") << "\n";
    setColor(C_CYAN); printLine('*', 45); resetColor();

    cout << "\n  Session Score : " << sessionScore << " pts\n";
    acc->player.display();   // IDisplayable -- runtime polymorphism

    // Data Analytics
    setColor(C_CYAN); cout << "\n  ANALYTICS:\n"; resetColor();
    cout << "  Games Played : " << acc->player.getGames()          << "\n";
    cout << "  Accuracy     : " << (int)acc->player.getAccuracy()  << "%\n";
    cout << "  Total Score  : " << acc->player.getScore()          << " pts\n";

    board.addOrUpdate(acc->player);
    board.save();
    board.display();
    pressEnter();
}

void GameSession::start()
{
    acc->player.newGame();
    int startFrom = loadSave();
    int total = qBank.count() < 9 ? qBank.count() : 9;

    for (int i = startFrom; i < total; i++)
    {
        Question* q = qBank.get(i);
        if (!q) break;

        clrscr();
        showHUD(i, total);

        // RUNTIME POLYMORPHISM -- correct display() called based on type
        q->display();

        showLifelines();
        cout << "\n  Press your answer key (no ENTER needed):\n\n";

        bool inTime = runTimer(15);
        char input;

        if (!inTime)
        {
            soundWrong();
            setColor(C_RED);
            cout << "  Time is up! Correct was: " << q->getCorrect() << "\n";
            resetColor();
            acc->player.addWrong();
            pressEnter();
            endGame(false);
            return;
        }

        input = (char)_getch();
        cout << input << "\n";
        input = toupper(input);

        // Lifelines
        if (input == 'F') { ll1.use(q); i--; pressEnter(); continue; }
        if (input == 'P') { ll2.use(q); i--; pressEnter(); continue; }
        if (input == 'E') { ll3.use(q); i--; pressEnter(); continue; }

        // Hint
        if (input == 'H')
        {
            if (acc->player.hasHints())
            {
                setColor(C_YELLOW);
                cout << "\n  HINT: " << q->getHint() << "\n";
                resetColor();
                acc->player.useHint();
            }
            else { setColor(C_RED); cout << "  No hints left!\n"; resetColor(); }
            i--; pressEnter(); continue;
        }

        // Save & quit
        if (input == 'S') { saveGame(i); endGame(false); return; }

        // Quit
        if (input == 'Q') { endGame(false); return; }

        // Validate input
        if (input < 'A' || input > 'D')
        {
            setColor(C_RED); cout << "  Invalid! Enter A-D\n"; resetColor();
            i--; pressEnter(); continue;
        }

        // Check answer
        if (q->checkAnswer(input))
        {
            soundCorrect();
            setColor(C_GREEN);
            cout << "\n  CORRECT! +" << q->getPoints() << " pts!\n";
            resetColor();
            sessionScore    += q->getPoints();
            acc->player     += q->getPoints();   // operator+= overloading
        }
        else
        {
            soundWrong();
            setColor(C_RED);
            cout << "\n  WRONG! Correct was: " << q->getCorrect() << "\n";
            resetColor();
            acc->player.addWrong();
            pressEnter();
            endGame(false);
            return;
        }
        pressEnter();
    }

    soundWin();
    setColor(C_YELLOW);
    cout << "\n  *** CONGRATULATIONS! YOU ARE A CROREPATI! ***\n";
    resetColor();
    clearSave();
    endGame(true);
}

// ============================================================
// GAME ENGINE
// ============================================================
GameEngine::GameEngine() {}

void GameEngine::showBanner()
{
    clrscr();
    setColor(C_YELLOW); printLine('*', 50);
    cout << "      KAUN BANEGA CROREPATI  v2.0\n";
    cout << "      Advanced OOP C++ Semester Project\n";
    printLine('*', 50); resetColor();
}

void GameEngine::showRules()
{
    clrscr();
    setColor(C_CYAN); printLine('=', 45);
    cout << "  HOW TO PLAY\n";
    printLine('=', 45); resetColor();
    cout << "  - Answer A/B/C/D within 15 seconds\n";
    cout << "  - Easy=10pts | Medium=20pts | Hard=50pts\n";
    cout << "  - F=50-50  P=Poll  E=Expert (lifelines)\n";
    cout << "  - H=Hint   S=Save&Quit   Q=Quit\n";
    cout << "  - Admin login: admin / admin123\n";
    pressEnter();
}

Account* GameEngine::doLogin()
{
    string user, pass;
    setColor(C_CYAN); cout << "\n  --- LOGIN ---\n"; resetColor();
    cout << "  Username: "; cin >> user;
    cout << "  Password: "; cin >> pass;

    Account* acc = auth.login(user, pass);
    if (acc)
    {
        setColor(C_GREEN);
        cout << "\n  Welcome, " << user << "!\n";
        resetColor();
        pressEnter();
        return acc;
    }
    setColor(C_RED); cout << "\n  Wrong username or password!\n"; resetColor();
    pressEnter();
    return NULL;
}

Account* GameEngine::doSignup()
{
    string user, pass, confirm;
    setColor(C_CYAN); cout << "\n  --- SIGN UP ---\n"; resetColor();
    cout << "  Choose Username: "; cin >> user;

    if (auth.exists(user))
    {
        setColor(C_RED); cout << "\n  Username already taken!\n"; resetColor();
        pressEnter(); return NULL;
    }

    cout << "  Choose Password: "; cin >> pass;
    cout << "  Confirm Password: "; cin >> confirm;

    if (pass != confirm)
    {
        setColor(C_RED); cout << "\n  Passwords do not match!\n"; resetColor();
        pressEnter(); return NULL;
    }

    if (auth.signup(user, pass))
    {
        setColor(C_GREEN); cout << "\n  Account created! Logging in...\n"; resetColor();
        pressEnter();
        return auth.login(user, pass);
    }
    return NULL;
}

Account* GameEngine::runLogin()
{
    while (true)
    {
        showBanner();
        setColor(C_WHITE);
        cout << "\n  1. Login\n  2. Sign Up\n  3. Exit\n\n  Choice: ";
        resetColor();

        int ch;
        try
        {
            cin >> ch;
            if (cin.fail()) throw invalid_argument("Enter a number");

            if      (ch == 1) { Account* a = doLogin();  if (a) return a; }
            else if (ch == 2) { Account* a = doSignup(); if (a) return a; }
            else if (ch == 3) { exit(0); }
            else throw invalid_argument("Enter 1, 2 or 3");
        }
        catch (const invalid_argument& e)
        {
            cin.clear(); cin.ignore(1000, '\n');
            setColor(C_RED); cout << "  Error: " << e.what() << "\n"; resetColor();
            pressEnter();
        }
    }
}

void GameEngine::run()
{
    Account* acc = runLogin();

    while (true)
    {
        showBanner();
        // operator<< overloading for Player
        cout << "  " << acc->player << "\n";
        printLine('-', 45);

        setColor(C_WHITE);
        cout << "\n  1. Play Game\n"
             << "  2. Scoreboard\n"
             << "  3. My Profile\n"
             << "  4. Rules\n";
        if (acc->isAdmin)
        { setColor(C_PINK); cout << "  5. Admin Panel\n"; }
        setColor(C_WHITE);
        cout << "  6. Logout\n"
             << "\n  Choice: ";
        resetColor();

        int ch;
        try
        {
            cin >> ch;
            if (cin.fail()) throw invalid_argument("Enter a number");

            switch (ch)
            {
                case 1:
                {
                    qBank.shuffle();
                    GameSession gs(acc, qBank, board);
                    gs.start();
                    auth.update(*acc);
                    break;
                }
                case 2:
                    clrscr(); board.display(); pressEnter();
                    break;
                case 3:
                    clrscr(); acc->player.display(); pressEnter();
                    break;
                case 4:
                    showRules();
                    break;
                case 5:
                    if (acc->isAdmin)
                    {
                        AdminPanel ap(auth, qBank, board);
                        ap.run();
                    }
                    else
                    {
                        setColor(C_RED); cout << "  Access denied!\n"; resetColor();
                        pressEnter();
                    }
                    break;
                case 6:
                    acc = runLogin();
                    break;
                default:
                    throw invalid_argument("Invalid choice");
            }
        }
        catch (const invalid_argument& e)
        {
            cin.clear(); cin.ignore(1000, '\n');
            setColor(C_RED); cout << "  Error: " << e.what() << "\n"; resetColor();
            pressEnter();
        }
    }
}

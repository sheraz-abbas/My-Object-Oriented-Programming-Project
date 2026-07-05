// ================================================================
//   KAUN BANEGA CROREPATI  --  Advanced OOP C++ Semester Project
//   Compiler : Dev-C++ 5.11  |  TDM-GCC 4.9  |  C++98
// ================================================================
//   Rubric Requirements Met:
//   [1]  5+ Classes          -- Question, Player, Lifeline, Auth,
//                               GameEngine, Scoreboard, QuestionBank
//   [2]  Abstraction         -- IDisplayable (pure abstract interface)
//                               abstract Question & Lifeline base classes
//   [3]  Encapsulation       -- All data private, public methods only
//   [4]  Inheritance         -- Easy/Medium/HardQuestion from Question
//                               FiftyFifty/AudiencePoll/Expert from Lifeline
//   [5]  Polymorphism        -- Runtime: virtual display(), virtual use()
//                               Compile-time: getType() function overloading
//   [6]  Templates           -- DataManager<T> class, findMax<T>() function
//   [7]  Operator Overloading-- +=, <<, >, <, ==, []
//   [8]  File Handling       -- users.txt, scores.txt, questions.txt, saves
//   [9]  Exception Handling  -- try/catch in GameEngine and AdminPanel
//  [10]  Static Members      -- Player::totalPlayers
//
//   Files:
//   globals.h       -- Colors, Sound, Timer, common includes
//   IDisplayable.h  -- Pure abstract interface
//   DataManager.h   -- Template class + template function
//   Question.h/.cpp -- Abstract Question + EasyQuestion + MediumQuestion
//                      + HardQuestion
//   Player.h/.cpp   -- Player with operator overloading + file I/O
//   Lifeline.h/.cpp -- Abstract Lifeline + FiftyFifty + AudiencePoll
//                      + ExpertAdvice
//   Scoreboard.h/.cpp -- STL sort + file handling
//   Auth.h/.cpp     -- Login/Signup/Admin using STL map
//   QuestionBank.h/.cpp -- DataManager<Question*> (template usage)
//   GameEngine.h/.cpp -- AdminPanel + GameSession + GameEngine
//   main.cpp        -- Entry point
// ================================================================

#include "GameEngine.h"

int main()
{
    srand((unsigned int)time(NULL));

    try
    {
        GameEngine engine;
        engine.run();
    }
    catch (const exception& e)
    {
        setColor(C_RED);
        cout << "\n  Fatal Error: " << e.what() << endl;
        resetColor();
        pressEnter();
    }

    return 0;
}

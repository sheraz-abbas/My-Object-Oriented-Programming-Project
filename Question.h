#ifndef QUESTION_H
#define QUESTION_H

#include "globals.h"
#include "IDisplayable.h"
#include "DataManager.h"

// ============================================================
// ABSTRACT BASE CLASS  --  Question
// Cannot be instantiated directly (has pure virtual getType)
// Demonstrates: Abstraction, Inheritance base
// ============================================================
class Question : public IDisplayable
{
protected:
    string questionText;
    string options[4];
    char   correctAnswer;
    int    points;
    string difficulty;
    string hint;

public:
    Question();
    Question(string q, string a, string b, string c, string d,
             char ans, int pts, string diff, string h);

    // Pure virtual  -->  makes Question abstract
    virtual string getType() const = 0;

    // Virtual  -->  Runtime Polymorphism (overridden in each derived)
    virtual void display() const;

    // Non-virtual helpers
    bool   checkAnswer(char ans) const;
    int    getPoints()           const;
    char   getCorrect()          const;
    string getDiff()             const;
    string getHint()             const;
    string getText()             const;

    // Operator overloading  -->  compare by points
    bool operator>(const Question& o) const;
    bool operator<(const Question& o) const;
    bool operator==(const Question& o) const;

    virtual ~Question();
};

// ============================================================
// DERIVED  --  EasyQuestion   (10 points)
// ============================================================
class EasyQuestion : public Question
{
public:
    EasyQuestion(string q, string a, string b,
                 string c, string d, char ans, string h);

    string getType() const;   // compile-time resolved (no virtual here)
    void   display() const;   // runtime polymorphism override
};

// ============================================================
// DERIVED  --  MediumQuestion  (20 points)
// ============================================================
class MediumQuestion : public Question
{
public:
    MediumQuestion(string q, string a, string b,
                   string c, string d, char ans, string h);

    string getType() const;
    void   display() const;
};

// ============================================================
// DERIVED  --  HardQuestion    (50 points)
// ============================================================
class HardQuestion : public Question
{
public:
    HardQuestion(string q, string a, string b,
                 string c, string d, char ans, string h);

    string getType() const;
    void   display() const;
};

#endif

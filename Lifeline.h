#ifndef LIFELINE_H
#define LIFELINE_H

#include "globals.h"
#include "IDisplayable.h"
#include "Question.h"

// ============================================================
// ABSTRACT BASE CLASS  --  Lifeline
// Demonstrates: Abstraction, Inheritance
// ============================================================
class Lifeline : public IDisplayable
{
protected:
    bool   used;
    string name;

public:
    Lifeline(string n);

    virtual void use(Question* q) = 0;   // pure virtual
    virtual void display() const;

    bool   isUsed()  const;
    string getName() const;

    virtual ~Lifeline();
};

// ============================================================
// DERIVED  --  FiftyFifty
// ============================================================
class FiftyFifty : public Lifeline
{
public:
    FiftyFifty();
    void use(Question* q);    // runtime polymorphism
    void display() const;
};

// ============================================================
// DERIVED  --  AudiencePoll
// ============================================================
class AudiencePoll : public Lifeline
{
public:
    AudiencePoll();
    void use(Question* q);
    void display() const;
};

// ============================================================
// DERIVED  --  ExpertAdvice
// ============================================================
class ExpertAdvice : public Lifeline
{
public:
    ExpertAdvice();
    void use(Question* q);
    void display() const;
};

#endif

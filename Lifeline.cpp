#include "Lifeline.h"

// ============================================================
// Lifeline  --  Base
// ============================================================
Lifeline::Lifeline(string n) : used(false), name(n) {}

bool   Lifeline::isUsed()  const { return used; }
string Lifeline::getName() const { return name; }

void Lifeline::display() const
{
    setColor(used ? C_RED : C_GREEN);
    cout << "  [" << name << "] " << (used ? "USED" : "OK");
    resetColor();
}

Lifeline::~Lifeline() {}

// ============================================================
// FiftyFifty
// ============================================================
FiftyFifty::FiftyFifty() : Lifeline("50-50") {}

void FiftyFifty::use(Question* q)
{
    if (used)
    {
        setColor(C_RED); cout << "\n  50-50 already used!\n"; resetColor();
        return;
    }
    setColor(C_YELLOW);
    cout << "\n  >> 50-50: Two wrong answers removed!" << endl;
    cout << "     Focus on the remaining two options." << endl;
    resetColor();
    used = true;
}

void FiftyFifty::display() const
{
    setColor(used ? C_RED : C_GREEN);
    cout << "  F=50-50(" << (used ? "X" : "OK") << ")";
    resetColor();
}

// ============================================================
// AudiencePoll
// ============================================================
AudiencePoll::AudiencePoll() : Lifeline("Poll") {}

void AudiencePoll::use(Question* q)
{
    if (used)
    {
        setColor(C_RED); cout << "\n  Poll already used!\n"; resetColor();
        return;
    }
    int v[4];
    v[0] = rand() % 15 + 5;
    v[1] = rand() % 15 + 5;
    v[2] = rand() % 15 + 5;
    v[3] = 100 - v[0] - v[1] - v[2];
    // Bias toward correct answer
    v[q->getCorrect() - 'A'] += 30;

    setColor(C_YELLOW);
    cout << "\n  >> Audience Poll Results:" << endl;
    resetColor();
    for (int i = 0; i < 4; i++)
    {
        cout << "     " << (char)('A' + i) << " : ";
        setColor(C_GREEN);
        int bars = v[i] / 4;
        for (int j = 0; j < bars; j++) cout << "|";
        cout << " " << v[i] << "%" << endl;
        resetColor();
    }
    used = true;
}

void AudiencePoll::display() const
{
    setColor(used ? C_RED : C_GREEN);
    cout << "  P=Poll(" << (used ? "X" : "OK") << ")";
    resetColor();
}

// ============================================================
// ExpertAdvice
// ============================================================
ExpertAdvice::ExpertAdvice() : Lifeline("Expert") {}

void ExpertAdvice::use(Question* q)
{
    if (used)
    {
        setColor(C_RED); cout << "\n  Expert already used!\n"; resetColor();
        return;
    }
    setColor(C_YELLOW);
    cout << "\n  >> Expert says: Answer is '"
         << q->getCorrect() << "'" << endl;
    resetColor();
    used = true;
}

void ExpertAdvice::display() const
{
    setColor(used ? C_RED : C_GREEN);
    cout << "  E=Expert(" << (used ? "X" : "OK") << ")";
    resetColor();
}

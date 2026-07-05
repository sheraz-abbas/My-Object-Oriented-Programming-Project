#ifndef QUESTIONBANK_H
#define QUESTIONBANK_H

#include "globals.h"
#include "Question.h"
#include "DataManager.h"

// ============================================================
// QUESTION BANK
// Uses DataManager<Question*> (template class)
// Demonstrates: File Handling, Template usage
// ============================================================
class QuestionBank
{
private:
    DataManager<Question*> qList;

    void addDefaults();
    void loadFromFile();

public:
    QuestionBank();

    Question* get(int i);
    int       count()   const;
    void      shuffle();

    DataManager<Question*>& getData();

    void addQuestion(Question* q, char diff);

    ~QuestionBank();
};

#endif

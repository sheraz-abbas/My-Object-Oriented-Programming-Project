#include "QuestionBank.h"

void QuestionBank::addDefaults()
{
    // --- EASY (10 pts) ---
    qList.add(new EasyQuestion(
        "Capital of Pakistan?",
        "Karachi","Lahore","Islamabad","Quetta", 'C',
        "It is in Punjab province"));

    qList.add(new EasyQuestion(
        "How many days are in a week?",
        "5","6","7","8", 'C',
        "Basic general knowledge"));

    qList.add(new EasyQuestion(
        "Which planet is closest to the Sun?",
        "Earth","Venus","Mercury","Mars", 'C',
        "Smallest planet in solar system"));

    qList.add(new EasyQuestion(
        "2 + 2 = ?",
        "3","4","5","6", 'B',
        "Very basic math"));

    qList.add(new EasyQuestion(
        "What does CPU stand for?",
        "Central Process Unit","Central Processing Unit",
        "Computer Personal Unit","Core Processing Unit", 'B',
        "Brain of the computer"));

    // --- MEDIUM (20 pts) ---
    qList.add(new MediumQuestion(
        "Who developed C++?",
        "Dennis Ritchie","James Gosling",
        "Bjarne Stroustrup","Guido van Rossum", 'C',
        "Danish computer scientist"));

    qList.add(new MediumQuestion(
        "What does OOP stand for?",
        "Only One Program","Object Oriented Programming",
        "Output Oriented Process","Open Object Program", 'B',
        "Programming paradigm with classes"));

    qList.add(new MediumQuestion(
        "Which data structure uses LIFO?",
        "Queue","Array","Tree","Stack", 'D',
        "Like a stack of plates"));

    qList.add(new MediumQuestion(
        "FIFA World Cup 2022 winner?",
        "France","Brazil","Portugal","Argentina", 'D',
        "Messi won his first World Cup here"));

    qList.add(new MediumQuestion(
        "Value of Pi (first 2 decimals)?",
        "3.12","3.16","3.14","3.18", 'C',
        "22 divided by 7 approximately"));

    // --- HARD (50 pts) ---
    qList.add(new HardQuestion(
        "Time complexity of Binary Search?",
        "O(n)","O(n^2)","O(1)","O(log n)", 'D',
        "Divides search space in half each step"));

    qList.add(new HardQuestion(
        "Which makes a function pure virtual in C++?",
        "abstract keyword","pure keyword","= 0 suffix","virtual only", 'C',
        "Syntax: virtual func() = 0"));

    qList.add(new HardQuestion(
        "Powerhouse of the cell?",
        "Nucleus","Ribosome","Golgi body","Mitochondria", 'D',
        "Produces ATP energy"));

    qList.add(new HardQuestion(
        "One interface, many implementations is called?",
        "Encapsulation","Inheritance","Abstraction","Polymorphism", 'D',
        "Poly = many, morph = forms"));

    qList.add(new HardQuestion(
        "Which sort has best average O(n log n)?",
        "Bubble Sort","Insertion Sort","Merge Sort","Selection Sort", 'C',
        "Divide and conquer strategy"));
}

void QuestionBank::loadFromFile()
{
    ifstream f("questions.txt");
    if (!f.is_open()) return;

    string line;
    while (getline(f, line))
    {
        if (line.empty()) continue;

        istringstream ss(line);
        string tok;
        vector<string> p;
        while (getline(ss, tok, '|')) p.push_back(tok);
        if ((int)p.size() < 8) continue;

        // Format: diff|question|A|B|C|D|ans|hint
        string diff = p[0];
        string q = p[1], a = p[2], b = p[3], c = p[4], d = p[5];
        char   ans  = p[6][0];
        string h    = p[7];

        if      (diff == "E") qList.add(new EasyQuestion(q,a,b,c,d,ans,h));
        else if (diff == "M") qList.add(new MediumQuestion(q,a,b,c,d,ans,h));
        else                  qList.add(new HardQuestion(q,a,b,c,d,ans,h));
    }
    f.close();
}

QuestionBank::QuestionBank()
{
    addDefaults();
    loadFromFile();
    qList.shuffle();
}

Question* QuestionBank::get(int i)   { return qList[i];      }
int       QuestionBank::count() const { return qList.count(); }
void      QuestionBank::shuffle()     { qList.shuffle();      }

DataManager<Question*>& QuestionBank::getData() { return qList; }

void QuestionBank::addQuestion(Question* q, char diff)
{
    qList.add(q);

    // Persist to file
    ofstream f("questions.txt", ios::app);
    if (!f.is_open()) return;

    char dc = (diff == 'E') ? 'E' : (diff == 'M') ? 'M' : 'H';
    f << dc << "|" << q->getText()
      << "|A_opt|B_opt|C_opt|D_opt|"    // placeholder (full opts not stored here)
      << q->getCorrect() << "|" << q->getHint() << "\n";
    f.close();
}

QuestionBank::~QuestionBank()
{
    for (int i = 0; i < qList.count(); i++)
        delete qList[i];
    qList.clear();
}

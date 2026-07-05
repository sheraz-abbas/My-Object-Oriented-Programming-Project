#include "Question.h"

// ============================================================
// Question  --  Base Implementation
// ============================================================
Question::Question()
    : correctAnswer('A'), points(0), difficulty("EASY"), hint("No hint") {}

Question::Question(string q, string a, string b, string c, string d,
                   char ans, int pts, string diff, string h)
{
    questionText    = q;
    options[0]      = a;
    options[1]      = b;
    options[2]      = c;
    options[3]      = d;
    correctAnswer   = ans;
    points          = pts;
    difficulty      = diff;
    hint            = h;
}

void Question::display() const
{
    setColor(C_CYAN);  printLine('=', 52);
    setColor(C_YELLOW);
    cout << "  [" << difficulty << "]   Points: " << points << endl;
    setColor(C_CYAN);  printLine('-', 52);
    setColor(C_WHITE);
    cout << "  " << questionText << endl;
    setColor(C_CYAN);  printLine('-', 52);
    setColor(C_GREEN);
    cout << "  A. " << options[0] << endl;
    cout << "  B. " << options[1] << endl;
    cout << "  C. " << options[2] << endl;
    cout << "  D. " << options[3] << endl;
    setColor(C_CYAN);  printLine('=', 52);
    resetColor();
}

bool   Question::checkAnswer(char ans) const { return toupper(ans) == correctAnswer; }
int    Question::getPoints()           const { return points;        }
char   Question::getCorrect()          const { return correctAnswer; }
string Question::getDiff()             const { return difficulty;    }
string Question::getHint()             const { return hint;          }
string Question::getText()             const { return questionText;  }

bool Question::operator>(const Question& o)  const { return points > o.points;        }
bool Question::operator<(const Question& o)  const { return points < o.points;        }
bool Question::operator==(const Question& o) const { return questionText == o.questionText; }

Question::~Question() {}

// ============================================================
// EasyQuestion
// ============================================================
EasyQuestion::EasyQuestion(string q, string a, string b,
                           string c, string d, char ans, string h)
    : Question(q, a, b, c, d, ans, 10, "EASY", h) {}

string EasyQuestion::getType() const { return "Easy"; }

void EasyQuestion::display() const
{
    setColor(C_GREEN);
    cout << "\n  >>> EASY QUESTION  [10 Points] <<<" << endl;
    resetColor();
    Question::display();
}

// ============================================================
// MediumQuestion
// ============================================================
MediumQuestion::MediumQuestion(string q, string a, string b,
                               string c, string d, char ans, string h)
    : Question(q, a, b, c, d, ans, 20, "MEDIUM", h) {}

string MediumQuestion::getType() const { return "Medium"; }

void MediumQuestion::display() const
{
    setColor(C_YELLOW);
    cout << "\n  >>> MEDIUM QUESTION  [20 Points] <<<" << endl;
    resetColor();
    Question::display();
}

// ============================================================
// HardQuestion
// ============================================================
HardQuestion::HardQuestion(string q, string a, string b,
                           string c, string d, char ans, string h)
    : Question(q, a, b, c, d, ans, 50, "HARD", h) {}

string HardQuestion::getType() const { return "Hard"; }

void HardQuestion::display() const
{
    setColor(C_RED);
    cout << "\n  >>> HARD QUESTION  [50 Points]  THINK CAREFULLY! <<<" << endl;
    resetColor();
    Question::display();
}

#ifndef IDISPLAYABLE_H
#define IDISPLAYABLE_H

// ============================================================
// INTERFACE  --  IDisplayable
// Pure abstract base class (acts as interface in C++)
// Any class that "is displayable" must implement display()
// ============================================================
class IDisplayable
{
public:
    virtual void display() const = 0;   // pure virtual
    virtual ~IDisplayable() {}
};

#endif

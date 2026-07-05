#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include "globals.h"

// ============================================================
// TEMPLATE CLASS  --  DataManager<T>
// Generic container for any type of game data
// Rubric: Templates usage (5 marks)
// ============================================================
template <class T>
class DataManager
{
private:
    vector<T> items;

public:
    // Add item
    void add(const T& item) { items.push_back(item); }

    // Get by index
    T get(int i) const
    {
        if (i < 0 || i >= (int)items.size())
            throw out_of_range("Index out of range!");
        return items[i];
    }

    // Operator [] overloading
    T& operator[](int i)
    {
        if (i < 0 || i >= (int)items.size())
            throw out_of_range("Index out of range!");
        return items[i];
    }

    int  count()  const { return (int)items.size(); }
    bool isEmpty() const { return items.empty(); }

    void clear() { items.clear(); }

    vector<T>& getAll() { return items; }

    // Shuffle items randomly
    void shuffle()
    {
        srand((unsigned int)time(NULL));
        for (int i = count() - 1; i > 0; i--)
        {
            int j      = rand() % (i + 1);
            T   tmp    = items[i];
            items[i]   = items[j];
            items[j]   = tmp;
        }
    }
};

// ============================================================
// TEMPLATE FUNCTION  --  findMax<T>
// Finds highest scored player/item from a vector
// ============================================================
template <class T>
T findMax(vector<T>& v)
{
    if (v.empty()) throw runtime_error("List is empty!");
    T mx = v[0];
    for (int i = 1; i < (int)v.size(); i++)
        if (v[i] > mx) mx = v[i];
    return mx;
}

#endif

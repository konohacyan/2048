#ifndef BASE_CLASS_H
#define BASE_CLASS_H

#include <vector>
using namespace std;

class Observer
{
public:
    Observer();
    virtual void notify() = 0;
};

class Subject
{
public:
    Subject();
    void notifyObservers();
    void registerObserver(Observer* observer);

private:
    vector<Observer*> observers;
};

class Tile
{
public:
    Tile() { value = 2; upgratedThisMove = false; }
    Tile(const Tile& other) { this->value = other.value; }
    Tile(int value) { this->value = value; }
    int& getValue() { return value; }
    void upgrade() { value *= UP_FACTOR; }
    void setUpgratedThisMove(bool updated) { this->upgratedThisMove = updated; }
    bool getUpgratedThisMove() const { return this->upgratedThisMove; }
    void operator=(const int& num){value = num;}
    bool operator==(const Tile& othe){return this->value == othe.value;}
private:
    const int UP_FACTOR = 2;
    int value;
    bool upgratedThisMove;
};

#endif// BASE_CLASS_H

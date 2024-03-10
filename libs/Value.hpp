#include <iostream>
using namespace std;

// Derived class for all values
class Value
{
protected:
  int value;

public:
  Value(int val) : value(val) {}
  void setValue(int val) { value = val; }
  int getValue() const { return value; }
};

// Derived class for experience points
class XP : public Value
{
public:
  XP(int val) : Value(val) {}
  void gainXP(int amount) { value += amount; }
  void loseXP(int amount) { value -= amount; }
};

// Derived class for hit points
class HP : public Value
{
public:
  HP(int val) : Value(val) {}
  void takeDamage(int damage) { value -= damage; }
  void heal(int amount) { value += amount; }
};

// Derived class for mana points
class Mana : public Value
{
public:
  Mana(int val) : Value(val) {}
  void spendMana(int amount) { value -= amount; }
  void restoreMana(int amount) { value += amount; }
};

#include <iostream>
using namespace std;

// Derived class for all values
class Value
{
protected:
  int value;

public:
  Value(int value);
  void setValue(int val);
  int getValue() const;
};

// Derived class for experience points
class XP : public Value
{
public:
  XP(int val);
  void gainXP(int amount);
  void loseXP(int amount);
};

// Derived class for hit points
class HP : public Value
{
private:
  static const int MAX_VALUE = 100;
  static const int MIN_VALUE = 0;

public:
  HP(int val);
  void takeDamage(int damage);
  void heal(int amount);
};
// Derived class for mana points
class Mana : public Value
{
public:
  Mana(int val);
  void spendMana(int amount);
  void restoreMana(int amount);
};
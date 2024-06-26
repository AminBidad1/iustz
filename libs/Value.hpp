#pragma once
#include <iostream>
using namespace std;

// Derived class for all values
class Value
{
protected:
  int value;

public:
  Value() = default;
  Value(int value);
  void setValue(int val);
  int getValue() const;
};

// Derived class for experience points
class XP : public Value
{
public:
  XP() = default;
  XP(int val);
  void gainXP(int amount);
  void loseXP(int amount);
};

// Derived class for hit points
class HP : public Value
{
public:
  int MAX_VALUE;
  int MIN_VALUE;
  HP() = default;
  HP(int val);
  void takeDamage(double damage);
  void heal(int amount);
};
// Derived class for mana points
class Mana : public Value
{
public:
  Mana() = default;
  Mana(int val);
  void spendMana(int amount);
  void restoreMana(int amount);
};

// Derived class for stamina points
class Stamina : public Value
{
public:
  int MAX_VALUE;
  int MIN_VALUE;
  Stamina() = default;
  Stamina(int val);
  void useStamina(int amount);
  void regenerateStamina(int amount);
};

// Derived class for monies
class Money : public Value
{
public:
  Money() = default;
  Money(int val);
  bool spend(int cost);
  void append(int amount);
};

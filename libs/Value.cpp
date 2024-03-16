#include "Value.hpp"

Value::Value(int value) { this->value = value; }

void Value::setValue(int val) { value = val; }
int Value::getValue() const { return value; }

XP::XP(int val) : Value(val) {}

void XP::gainXP(int amount) { value += amount; }
void XP::loseXP(int amount) { value -= amount; }

HP::HP(int val) : Value(val) {}

void HP::takeDamage(int damage) { value -= damage; }
void HP::heal(int amount) { value += amount; }

const int HP::MAX_VALUE;
const int HP::MIN_VALUE;

Mana::Mana(int val) : Value(val) {}

void Mana::spendMana(int amount) { value -= amount; }
void Mana::restoreMana(int amount) { value += amount; }

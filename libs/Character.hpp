#include "bits/stdc++.h"
#include "Value.hpp"
#include "Skill.hpp"
#include "Item.hpp"

using namespace std;

class Character
{
protected:
    string name;
    int age;
    string gender;
    HP* hp;
    Money* money;
public:
    Character() = default;
    Character(string name, int age, string gender, HP* hp, Money* money);
    string get_name();
    void set_name(string name);
    bool take_damage(int damage);
};

class Human : public Character
{
protected:
    Mana* mana;
    XP* xp;
    vector<Skill*> skills;
    vector<Item*> items;
public:
    Human() = default;
    Human(string name, int age, string gender, HP* hp, Money* money,
          Mana* mana, XP* xp, vector<Skill*> skills, vector<Item*> items);
    void addSkill(Skill* skill);
    void AddItem(Item* item);
};

class Zombie : public Character
{
private:
    int damage;
public:
    Zombie() = default;
    Zombie(string name, int age, string gender, HP* hp, Money* money, int damage);
    bool attack(Character* character);
};

enum class State
{
    Start, LowHP, LowMana, Attack
};

class EnemyHuman : public Human
{
public:
    State getNextState(State currentState);
    bool checkState(State currentState);
};

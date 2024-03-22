#pragma once
#include "bits/stdc++.h"
#include "Value.hpp"
#include "Skill.hpp"
#include "Item.hpp"
// #include "ConsumableItem.hpp"
#include "utils.hpp"

using namespace std;


class Character
{
private:
    string name;
    int age;
    string gender;
    int default_damage;
public:
    HP* hp;
    Money* money;
    Character() = default;
    Character(string name, int age, string gender, HP* hp, Money* money);
    string get_name();
    void set_name(string name);
    int getAge();
    void setAge(int age);
    string getGender();
    void setGender(string gender);
    int getDefault_damage();
    void setDefault_damage(int default_damage);
    bool take_damage(int damage);
    bool attack(Character* character, int damage);
};

class Human : public Character
{
protected:
    XP* xp;
    vector<Skill*> skills;
    vector<InventoryItem> items;
public:
    Stamina* stamina;
    Human() = default;
    Human(string name, int age, string gender, HP* hp, Money* money,
          Stamina* stamina, XP* xp, vector<Skill*> skills, vector<InventoryItem> items);
    void addSkill(Skill* skill);
    void addItem(Item* item, string type, int count);
    // TODO: functions to use items
    bool buyItem(Item* item, string type, int count, int price);
};

class Zombie : public Character
{
public:
    Zombie() = default;
    Zombie(string name, int age, string gender, HP* hp, Money* money, int damage);
};


class EnemyHuman : public Human
{
public:
    State getNextState(State currentState);
    bool checkState(State currentState, Character* character);
};

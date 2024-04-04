#pragma once
#include "bits/stdc++.h"
#include "Value.hpp"
#include "Skill.hpp"
#include "Item.hpp"
#include "utils.hpp"

using namespace std;


class Character
{
private:
    string name;
    int age;
    string gender;
    int damage;
public:
    HP* hp;
    Money* money;
    Character() = default;
    Character(string name, int age, string gender, HP* hp, Money* money, int damage);
    string get_name();
    void set_name(string name);
    int getAge();
    void setAge(int age);
    string getGender();
    void setGender(string gender);
    int getDamage();
    void setDamage(int damage);
    bool take_damage(int damage);
    bool attack(Character* character, int damage);
};

class Human : public Character
{
protected:
    XP* xp;
    vector<Skill*> skills;
public:
    vector<InventoryItem> items;
    Stamina* stamina;
    Human() = default;
    Human(string name, int age, string gender, HP* hp, Money* money,
          Stamina* stamina, XP* xp, vector<Skill*> skills,
          vector<InventoryItem> items, int damage);
    XP* getXp();
    void setXp(XP* xp);
    void addSkill(Skill* skill);
    void addItem(InventoryItem& inventoryItem);
    void useItem(int item_index);
    bool buyItem(InventoryItem& inventoryItem, int price);
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

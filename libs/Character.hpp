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
    double damage;
public:
    HP* hp;
    Money* money;
    Character() = default;
    Character(string name, int age, string gender, HP* hp, Money* money, double damage);
    string get_name();
    void set_name(string name);
    int getAge();
    void setAge(int age);
    string getGender();
    void setGender(string gender);
    double getDamage();
    void setDamage(double damage);
    bool take_damage(double damage);
    bool attack(Character* character, double damage);
};

class Human : public Character
{
protected:
    XP* xp;
public:
    vector<Skill*> skills;
    vector<InventoryItem*> items;
    Stamina* stamina;
    Human() = default;
    Human(string name, int age, string gender, HP* hp, Money* money,
          Stamina* stamina, XP* xp, vector<Skill*> skills,
          vector<InventoryItem*> items, double damage);
    XP* getXp();
    void setXp(XP* xp);
    void addSkill(Skill* skill);
    void addItem(InventoryItem* inventoryItem);
    void useItem(int item_index);
    bool buyItem(InventoryItem* inventoryItem, int price);
    void removeItem(int item_index, int count);
    InventoryItem* getItem(int item_index);
};

class Zombie : public Character
{
public:
    Zombie() = default;
    Zombie(string name, int age, string gender, HP* hp, Money* money, double damage);
};

class HumanEnemy : public Human
{
public:
    int defaultHp;
    int defaultStamina;
    HumanEnemy(string name, int age, string gender, HP* hp, Money* money,
               Stamina* stamina, XP* xp, vector<Skill*> skills,
               vector<InventoryItem*> items, double damage);
    HumanEnemy(string name, int age, string gender, HP* hp, Money* money,
               Stamina* stamina, XP* xp, double damage);
    bool haveItem(ItemType type);
    void addItem(InventoryItem* inventoryItem, int level);
};

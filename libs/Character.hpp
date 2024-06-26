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
    static constexpr double DEFAULT_DAMAGE = 10;
    static const int DEFAULT_HP = 100;
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
    static constexpr double DEFAULT_DAMAGE = 10.0;
    static const int DEFAULT_HP = 100;
    int MAX_INVENTORY_SIZE;
    int occupied_volume;
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
    bool addItem(InventoryItem* inventoryItem, int skill_level);
    void useItem(int item_index);
    bool buyItem(InventoryItem* inventoryItem, int price, int skill_level);
    void removeItem(int item_index, int count);
    InventoryItem* getItem(int item_index);
};

class Hero : public Human
{
public:
    Hero() = default;
};

class Attacker : public Hero
{
public:
    static constexpr double DEFAULT_DAMAGE = 20.0;
    static const int DEFAULT_HP = 80;
    Attacker() = default;
    Attacker(string name, int age, string gender, HP* hp, Money* money,
            Stamina* stamina, XP* xp, vector<Skill*> skills,
            vector<InventoryItem*> items, double damage);
};

class Tank : public Hero
{
public:
    static constexpr double DEFAULT_DAMAGE = 10.0;
    static const int DEFAULT_HP = 250;
    Tank() = default;
    Tank(string name, int age, string gender, HP* hp, Money* money,
         Stamina* stamina, XP* xp, vector<Skill*> skills,
         vector<InventoryItem*> items, double damage);
};

class Healer : public Hero
{
public:
    static constexpr double DEFAULT_DAMAGE = 5.0;
    static const int DEFAULT_HP = 100;
    Healer() = default;
    Healer(string name, int age, string gender, HP* hp, Money* money,
           Stamina* stamina, XP* xp, vector<Skill*> skills,
           vector<InventoryItem*> items, double damage);
};

class Zombie : public Character
{
public:
    Zombie() = default;
    Zombie(string name, int age, string gender, HP* hp, Money* money, double damage);
};

class VampireZombie : public Zombie
{
public:
    VampireZombie() = default;
    VampireZombie(string name, int age, string gender, HP* hp, Money* money, double damage);
};

class UltraZombie : public Zombie
{
public:
    UltraZombie() = default;
    UltraZombie(string name, int age, string gender, HP* hp, Money* money, double damage);
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
    void addItem(InventoryItem* inventoryItem, int skill_level);
};

class UltraVampireZombie : public HumanEnemy
{
public:
    UltraVampireZombie() = default;
    UltraVampireZombie(string name, int age, string gender, HP* hp, Money* money,
                       Stamina* stamina, XP* xp, double damage);
};

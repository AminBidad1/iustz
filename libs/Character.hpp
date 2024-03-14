#include <iostream>
#include "Value.hpp"

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
private:
    Mana* mana;
    XP* xp;
public:
    Human() = default;
    Human(string name, int age, string gender, HP* hp, Money* money, Mana* mana, XP* xp);

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

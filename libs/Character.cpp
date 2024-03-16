#include "Character.hpp"

Character::Character(string name, int age, string gender, HP* hp, Money* money)
{
    this->name = name;
    this->age = age;
    this->gender = gender;
    this->hp = hp;
    this->money = money;
}

string Character::get_name()
{
    return this->name;
}

void Character::set_name(string name)
{
    this->name = name;
}

bool Character::take_damage(int damage)
{
    if (this->hp->getValue() - damage <= 0)
    {
        return true;
    }
    this->hp->takeDamage(damage);
    return false;
}

Human::Human(string name, int age, string gender, HP* hp, Money* money, Mana* mana, XP* xp, vector<Skill*> skills) :
    Character(name, age, gender, hp, money)
{
    this->mana = mana;
    this->xp = xp;
    this->skills = skills;
}

void Human::addSkill(Skill* skill)
{
    this->skills.push_back(skill);
}

Zombie::Zombie(string name, int age, string gender, HP* hp, Money* money, int damage) :
    Character(name, age, gender, hp, money)
{
    this->damage = damage;
}

bool Zombie::attack(Character* character)
{
    if (character->take_damage(this->damage))
    {
        return true;
    }
    return false;
}

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

int Character::getAge() {
	return this->age;
}
void Character::setAge(int age) {
	this->age = age;
}

string Character::getGender() {
	return this->gender;
}
void Character::setGender(string gender) {
	this->gender = gender;
}

int Character::getDefault_damage() {
	return this->default_damage;
}
void Character::setDefault_damage(int default_damage) {
	this->default_damage = default_damage;
}

bool Character::attack(Character* character, int damage)
{
    if (character->take_damage(damage))
    {
        return true;
    }
    return false;
}

Human::Human(string name, int age, string gender, HP* hp, Money* money,
             Mana* mana, XP* xp, vector<Skill*> skills, vector<Item*> items) :
    Character(name, age, gender, hp, money)
{
    this->mana = mana;
    this->xp = xp;
    this->skills = skills;
    this->items = items;
}

void Human::addSkill(Skill* skill)
{
    this->skills.push_back(skill);
}

void Human::AddItem(Item* item)
{
    this->items.push_back(item);
}

Zombie::Zombie(string name, int age, string gender, HP* hp, Money* money, int damage) :
    Character(name, age, gender, hp, money)
{
    this->setDefault_damage(damage);
}

State EnemyHuman::getNextState(State currentState)
{
    if (this->hp->getValue() < 50)
    {
        return State::LowHP;
    }
    else if (this->mana->getValue() < 50)
    {
        return State::LowMana;
    }
    else
    {
        return State::Attack;
    }
}

bool EnemyHuman::checkState(State currentState)
{
    switch (currentState)
    {
    case State::LowHP:
        // TODO: Use HP booster
        break;
    case State::LowMana:
        // TODO: USe Mana booster
        break;
    case State::Attack:
        return true;
    default:
        break;
    }
    return false;
}
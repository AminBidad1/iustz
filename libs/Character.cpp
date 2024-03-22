#include "Character.hpp"
#include "Item.hpp"
#include "ConsumableItem.hpp"

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
             Stamina* stamina, XP* xp, vector<Skill*> skills, vector<InventoryItem> items) :
    Character(name, age, gender, hp, money)
{
    this->stamina = stamina;
    this->xp = xp;
    this->skills = skills;
    this->items = items;
}

void Human::addSkill(Skill* skill)
{
    this->skills.push_back(skill);
}

void Human::addItem(Item* item, string type, int count)
{
    for (int i=0; i < this->items.size(); i++)
    {
        if (this->items[i].type == type)
        {
            this->items[i].count += count;
            return;
        }
    }
    InventoryItem inventoryItem;
    inventoryItem.item = item;
    inventoryItem.type = type;
    inventoryItem.count = count;
    this->items.push_back(inventoryItem);
}

bool Human::buyItem(Item* item, string type, int count, int price)
{
    if (this->money->spend(count * price))
    {
        this->addItem(item, type, count);
        return true;
    }
    return false;
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
    else if (this->stamina->getValue() < 50)
    {
        return State::LowStamina;
    }
    else
    {
        return State::Attack;
    }
}

bool EnemyHuman::checkState(State currentState, Character* character)
{
    switch (currentState)
    {
    case State::LowHP:
        // TODO: Use HP booster
        Food* food;
        for (int i=0; i < this->items.size(); i++)
        {
            if (this->items[i].type == "Food")
            {
                food = (Food*)this->items[i].item;
            }
        }
        if (food != nullptr)
            food->consume(this);
        else 
            return false;
        break;
    case State::LowStamina:
        // TODO: Use Stamina booster
        StaminaBooster* staminaBooster;
        for (int i=0; i < this->items.size(); i++)
        {
            if (this->items[i].type == "StaminaBooster")
            {
                staminaBooster = (StaminaBooster*)this->items[i].item;
            }
        }
        if (staminaBooster != nullptr)
            staminaBooster->consume(this);
        else
            return false;
        break;
    case State::Attack:
        // TODO: Use attacking items to attack
        this->attack(character, this->getDefault_damage());
    default:
        break;
    }
    return true;
}
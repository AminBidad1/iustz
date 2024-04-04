#include "Character.hpp"
#include "Item.hpp"
#include "ConsumableItem.hpp"

Character::Character(string name, int age, string gender, HP* hp, Money* money, int damage)
{
    this->name = name;
    this->age = age;
    this->gender = gender;
    this->hp = hp;
    this->money = money;
    this->damage = damage;
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

int Character::getDamage() {
	return this->damage;
}
void Character::setDamage(int _damage) {
	this->damage = _damage;
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
             Stamina* stamina, XP* xp,
             vector<Skill*> skills, vector<InventoryItem> items, int damage) :
    Character(name, age, gender, hp, money, damage)
{
    this->stamina = stamina;
    this->xp = xp;
    this->skills = skills;
    this->items = items;
}

XP* Human::getXp() 
{
	return this->xp;
}

void Human::setXp(XP* xp) 
{
	this->xp = xp;
}

void Human::addSkill(Skill* skill)
{
    this->skills.push_back(skill);
}

void Human::addItem(InventoryItem& inventoryItem)
{
    for (int i=0; i < this->items.size(); i++)
    {
        if (this->items[i].type == inventoryItem.type)
        {
            this->items[i].count += inventoryItem.count;
            return;
        }
    }
    this->items.push_back(inventoryItem);
}

void Human::useItem(int item_index)
{
    InventoryItem inventoryItem = items[item_index];
    if (inventoryItem.fatherType == ItemType::ConsumableItem)
    {
        ConsumableItem* consumableItem = (ConsumableItem*)inventoryItem.item;
        consumableItem->consume(this);
        inventoryItem.remove(1);
    }
    else if (inventoryItem.fatherType == ItemType::ThrowableItem)
    {
        ThrowableItem* throwableItem = (ThrowableItem*)inventoryItem.item;
        int attackingDamage = throwableItem->attack();
        this->setDamage(attackingDamage);
        inventoryItem.remove(1);
    }
}

bool Human::buyItem(InventoryItem& inventoryItem, int price)
{
    if (this->money->spend(inventoryItem.count * price))
    {
        this->addItem(inventoryItem);
        return true;
    }
    return false;
}

Zombie::Zombie(string name, int age, string gender, HP* hp, Money* money, int damage) :
    Character(name, age, gender, hp, money, damage)
{}

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

/*
int ConsumableItem::getValue() const { return value->getValue(); }

//Food
void Food::consume(Character* target)
{
    // increasing the target's hp by the value of item
    target->hp->heal(this->getValue());
}

//StaminaBooster
void StaminaBooster::consume(Human* target)
{
    // increasing the target's stamina by the value of item
    target->stamina->regenerateStamina(this->getValue());
}
*/

bool EnemyHuman::checkState(State currentState, Character* character)
{
    switch (currentState)
    {
    case State::LowHP:
        // TODO: Use HP booster
        Food* food;
        for (int i=0; i < this->items.size(); i++)
        {
            if (this->items[i].type == ItemType::Food)
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
            if (this->items[i].type == ItemType::StaminaBooster)
            {
                staminaBooster = (StaminaBooster*)this->items[i].item;
            }
        }
        if (staminaBooster != nullptr)
            staminaBooster->consume((Character*)this);
        else
            return false;
        break;
    case State::Attack:
        // TODO: Use attacking items to attack
        this->attack(character, this->getDamage());
    default:
        break;
    }
    return true;
}
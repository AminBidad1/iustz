#include "Character.hpp"
#include "Item.hpp"
#include "ConsumableItem.hpp"

Character::Character(string name, int age, string gender, HP* hp, Money* money, double damage)
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

bool Character::take_damage(double damage)
{
    if (this->hp->getValue() - (int)damage <= 0)
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

double Character::getDamage() {
	return this->damage;
}
void Character::setDamage(double damage) {
	this->damage = damage;
}

bool Character::attack(Character* character, double damage)
{
    if (character->take_damage(damage))
    {
        return true;
    }
    return false;
}

Human::Human(string name, int age, string gender, HP* hp, Money* money,
             Stamina* stamina, XP* xp,
             vector<Skill*> skills, vector<InventoryItem*> items, double damage) :
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

void Human::addItem(InventoryItem* inventoryItem)
{
    for (int i=0; i < this->items.size(); i++)
    {
        if (this->items[i]->type == inventoryItem->type)
        {
            this->items[i]->count += inventoryItem->count;
            return;
        }
    }
    this->items.push_back(inventoryItem);
    Skill* skill = new Skill(inventoryItem, 0);
    addSkill(skill);
}

void Human::useItem(int item_index)
{
    InventoryItem* inventoryItem = items[item_index];
    if (inventoryItem->fatherType == ItemType::ConsumableItem)
    {
        ConsumableItem* consumableItem = (ConsumableItem*)inventoryItem->item;
        consumableItem->consume(this);
        removeItem(item_index, 1);
    }
    else if (inventoryItem->fatherType == ItemType::ThrowableItem)
    {
        ThrowableItem* throwableItem = (ThrowableItem*)inventoryItem->item;
        int attackingDamage = throwableItem->attack();
        this->setDamage(attackingDamage);
        removeItem(item_index, 1);
    }
}

bool Human::buyItem(InventoryItem* inventoryItem, int price)
{
    if (this->money->spend(inventoryItem->count * price))
    {
        this->addItem(inventoryItem);
        return true;
    }
    return false;
}

void Human::removeItem(int item_index, int count)
{
    this->items[item_index]->count -= 1;
}

InventoryItem* Human::getItem(int item_index)
{
    InventoryItem* inventoryItem = this->items[item_index];
    return inventoryItem;
}

Attacker::Attacker(string name, int age, string gender, HP* hp, Money* money,
            Stamina* stamina, XP* xp, vector<Skill*> skills,
            vector<InventoryItem*> items, double damage)
{
    set_name(name);
    setAge(age);
    setGender(gender);
    this->hp = hp;
    this->money = money;
    this->stamina = stamina;
    setXp(xp);
    setDamage(damage);
}

Tank::Tank(string name, int age, string gender, HP* hp, Money* money,
            Stamina* stamina, XP* xp, vector<Skill*> skills,
            vector<InventoryItem*> items, double damage)
{
    set_name(name);
    setAge(age);
    setGender(gender);
    this->hp = hp;
    this->money = money;
    this->stamina = stamina;
    setXp(xp);
    setDamage(damage);
}

Healer::Healer(string name, int age, string gender, HP* hp, Money* money,
            Stamina* stamina, XP* xp, vector<Skill*> skills,
            vector<InventoryItem*> items, double damage)
{
    set_name(name);
    setAge(age);
    setGender(gender);
    this->hp = hp;
    this->money = money;
    this->stamina = stamina;
    setXp(xp);
    setDamage(damage);
}

Zombie::Zombie(string name, int age, string gender, HP* hp, Money* money, double damage) :
    Character(name, age, gender, hp, money, damage)
{}

HumanEnemy::HumanEnemy(string name, int age, string gender, HP* hp, Money* money,
                        Stamina* stamina, XP* xp, vector<Skill*> skills,
                        vector<InventoryItem*> items, double damage) : 
            Human(name, age, gender, hp, money, stamina, xp, skills, items, damage)
{}

HumanEnemy::HumanEnemy(string name, int age, string gender, HP* hp, Money* money,
               Stamina* stamina, XP* xp, double damage)
{
    set_name(name);
    setAge(age);
    setGender(gender);
    this->hp = hp;
    this->money = money;
    this->stamina = stamina;
    setXp(xp);
    setDamage(damage);
}

bool HumanEnemy::haveItem(ItemType type)
{
    for (int i=0; i < items.size(); i++)
    {
        if (items[i]->type == type)
        {
            if (items[i]->count > 0)
                return true;
            else
                return false;
        }
    }
    return false;
}

void HumanEnemy::addItem(InventoryItem* inventoryItem, int level)
{
    for (int i=0; i < this->items.size(); i++)
    {
        if (this->items[i]->type == inventoryItem->type)
        {
            this->items[i]->count += inventoryItem->count;
            return;
        }
    }
    this->items.push_back(inventoryItem);
    Skill* skill = new Skill(inventoryItem, level);
    addSkill(skill);
}

VampireZombie::VampireZombie(string name, int age, string gender,
                             HP* hp, Money* money, double damage) :
                Zombie(name, age, gender, hp, money, damage)
{}

UltraZombie::UltraZombie(string name, int age, string gender,
                             HP* hp, Money* money, double damage) :
                Zombie(name, age, gender, hp, money, damage)
{}

UltraVampireZombie::UltraVampireZombie(string name, int age, string gender,
                    HP* hp, Money* money,
                    Stamina* stamina, XP* xp, double damage)
        : HumanEnemy(name, age, gender, hp, money, stamina, xp, damage)
{}

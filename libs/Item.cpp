#include "Item.hpp"
#include "Character.hpp"

// Item
Item::Item(string name, int price)
{
    this->name = name;
    this->price = price;
}

void Item::setName(string name) { this->name = name; }
string Item::getName() const { return name; }

void Item::setPrice(int price) { this->price = price; }
int Item::getPrice() const { return price; }

void Item::display_message()
{
    cout << "test for message in Item";
}

int Item::getSize()
{
    return this->size;
}

void Item::setSize(int size)
{
    this->size = size;
}

// ThrowableItem
ThrowableItem::ThrowableItem(string name, int price, double damage)
{
    setName(name);
    setPrice(price);
    this->damage = damage;
}

void AttackingItem::setDamage(double damage) { this->damage = damage; }
int AttackingItem::getDamage() const { return damage; }

int AttackingItem::getMiss_percent()
{
    return this->miss_percent;
}

void AttackingItem::setMiss_percent(double miss_percent)
{
    this->miss_percent = miss_percent;
}

int AttackingItem::getLevel()
{
    return this->level;
}

void AttackingItem::setLevel(int level)
{
    this->level = level;
    double _damage = getDamage();
    setDamage(pow(1.08, level)*_damage);
}

void AttackingItem::levelup(int count)
{
    this->level += count;
    double _damage = getDamage();
    setDamage(pow(1.08, count)*_damage);
}

double KitchenKnife::attack()
{
    int random_number = rand() % 100;
    if (random_number >= miss_percent)
    {
        return damage;
    }
    else
    {
        return 0;
    }
}

double Bomb::attack()
{
    int random_number = rand() % 100;
    return damage * random_number / (miss_percent * 100);
}

double Molotov::attack()
{
    int random_number = rand() % 100;
    return damage * random_number / (miss_percent * 50);
}

double Bristle::attack()
{
    int random_number = rand() % 100;
    if (random_number >= miss_percent)
    {
        return damage;
    }
    else
    {
        return 0;
    }
}

// PassiveItem
void PassiveItem::setUpgradeable(bool Upgradeable) { this->Upgradeable = Upgradeable; }
bool PassiveItem::getUpgradeable() const { return Upgradeable; }

// Firearms
void Firearms::setDamage(double damage_per_ammo) { this->damage_per_ammo = damage_per_ammo; }
int Firearms::getDamage() { return damage_per_ammo; }

void Firearms::setMagazineSize(int magazine_size) { this->magazine_size = magazine_size; }
int Firearms::getMagazineSize() { return this->magazine_size; }

double Colt::attack()
{
    double damage = 0;
    int random_number;
    for (int i = 0; i < getMagazineSize(); i++)
    {
        random_number = rand() % 100;
        if (random_number >= getMiss_percent())
        {
            damage += getDamage();
        }
    }
    return damage;
}

double Kelash::attack()
{
    double damage = 0;
    int random_number;
    for (int i = 0; i < getMagazineSize(); i++)
    {
        random_number = rand() % 100;
        if (random_number >= getMiss_percent())
        {
            damage += getDamage();
        }
    }
    return damage;
}

double FlatLine::attack()
{
    double damage = 0;
    int random_number;
    for (int i = 0; i < getMagazineSize(); i++)
    {
        random_number = rand() % 100;
        if (random_number >= getMiss_percent())
        {
            damage += getDamage();
        }
    }
    return damage;
}

// ColdWeapon
double Sword::attack()
{
    return damage;
}
double Stick::attack()
{
    return damage;
}
double Knuckles::attack()
{
    return damage;
}

// InventoryItem
void InventoryItem::add(int count)
{
    this->count += count;
}

bool InventoryItem::remove(int count)
{
    if (count > this->count)
    {
        return false;
    }
    this->count -= count;
    return true;
}

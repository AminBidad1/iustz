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
int Firearms::getMagazineSize() { return magazine_size; }

void Firearms::setMisspercent(double miss_percent) { this->miss_percent = miss_percent; }
double Firearms::getMisspercent() { return miss_percent; }

double Colt::attack()
{
    double damage = 0;
    for (int i = 0; i < getMagazineSize(); i++)
    {
        int random_number = rand() % 100;
        if (random_number >= getMisspercent())
        {
            damage += getDamage();
        }
    }
}

double AK47::attack()
{
    double damage = 0;
    for (int i = 0; i < getMagazineSize(); i++)
    {
        int random_number = rand() % 100;
        if (random_number >= getMisspercent())
        {
            damage += getDamage();
        }
    }
}

double FlatLine::attack()
{
    double damage = 0;
    for (int i = 0; i < getMagazineSize(); i++)
    {
        int random_number = rand() % 100;
        if (random_number >= getMisspercent())
        {
            damage += getDamage();
        }
    }
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

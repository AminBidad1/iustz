#include "ThrowableItem.hpp"
ThrowableItem::ThrowableItem(string name, int damage, int price)
{
    this->name = name;
    this->damage = damage;
    this->price = price;
}

void ThrowableItem::setName(string name) { this->name = name; }
string ThrowableItem::getName() const { return name; }

void ThrowableItem::setDamage(int damage) { this->damage = damage; }
int ThrowableItem::getNameDamage() const { return damage; }

void ThrowableItem::setPrice(int price) { this->price = price; }
int ThrowableItem::getPrice() const { return price; }

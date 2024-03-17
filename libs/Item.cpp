#include "Item.hpp"
#include "Character.hpp"

//Item
Item::Item(string name , int price)
{
    this->name=name;
    this->price=price;
}

void Item::setName(string name){this->name=name;}
string Item::getName() const {return name;}

void Item::setPrice(int price){this->price=price;}
int Item::getPrice() const {return price;}

void Item::display_message(){
    cout<<"test for message in Item";
}

//ThrowableItem
ThrowableItem::ThrowableItem(string name, int damage, int price) :Item(name , price) {this->damage=damage;}

void ThrowableItem::setName(string name) {Item::setName(name);}
string ThrowableItem::getName() const {Item::getName();}

void ThrowableItem::setPrice(int price){Item::setPrice(price);}
int ThrowableItem::getPrice() const {Item::getPrice();}

void ThrowableItem::setDamage(int damage){this->damage=damage;}
int ThrowableItem::getDamage() const {return damage;}

//PassiveItem
void PassiveItem::setUpgradeable(bool Upgradeable){this->Upgradeable=Upgradeable;}
bool PassiveItem::getUpgradeable() const {return Upgradeable;}

//Firearms
void Firearms::setDamage(int damage_per_ammo){this->damage_per_ammo=damage_per_ammo;}
int Firearms::getDamage(){return damage_per_ammo;}

void Firearms::setAmmo(int ammo){this->ammo=ammo;}
int Firearms::getAmmo(){return ammo;}

void Firearms::setMagazine(int magazine){this->magazine=magazine;}
int Firearms::getMagazine(){return magazine;}

void Firearms::setFirerate(int fire_rate){this->fire_rate=fire_rate;}
int Firearms::getFirerate(){return fire_rate;}

void Firearms::setMisspercent(int miss_percet){this->miss_percent=miss_percent;}
int Firearms::getMisspercent(){return miss_percent;}

//ConsumableItem
ConsumableItem::ConsumableItem() = default;
ConsumableItem::ConsumableItem(string name, int price) : Item(name, price) {};

void ConsumableItem::setValue(int value) { this->value->setValue(value); }
int ConsumableItem::getValue() const { return value->getValue(); }

void ConsumableItem::consume() {}

//ManaBooster
void ManaBooster::consume(Human* target)
{
    // increasing the target's mana by the value of item
    target->mana->restoreMana(this->getValue());
}

//Food
void Food::consume(Character* target)
{
    // increasing the target's hp by the value of item
    target->hp->heal(this->getValue());
}

//Beverage
void Beverage::consume(Character* target)
{
    // increasing the target's damage by the value of item
    target->target->setDamage(target->getDamage() + this->getValue());
}
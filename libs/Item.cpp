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

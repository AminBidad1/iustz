#pragma once
#include "Value.hpp"
#include <vector>

enum class ItemType;

//Item
class Item {
private:
    string name;
    int price;
public:
    Item() = default;
    Item(string name , int price);

    void setName(string name);
    string getName() const;

    void setPrice(int price);
    int getPrice() const;

    virtual void display_message();
};

//ThrowableItem
class ThrowableItem :public Item {
private:
    int damage;
public:
    ThrowableItem() = default;
    ThrowableItem(string name, int damage, int price);

    void setDamage(int damage);
    int getDamage() const;
};

class KitchenKnife : public ThrowableItem
{

};

class Grande : public ThrowableItem
{

};

class Molotov : public ThrowableItem
{

};

class Bristle : public ThrowableItem
{

};

//PassiveItem
class PassiveItem :public Item
{
private:
    bool Upgradeable;
public:
    void setUpgradeable(bool Upgradable);
    bool getUpgradeable() const ;

};

//Firearms
class Firearms :public PassiveItem
{
private:
    int damage_per_ammo;
    int ammo;
    int magazine;
    int fire_rate;
    int miss_percent;
public:
    void setDamage(int damage_per_ammo);
    int getDamage();

    void setAmmo(int ammo);
    int getAmmo();

    void setMagazine(int magazine);
    int getMagazine();

    void setFirerate(int fire_rate);
    int getFirerate();

    void setMisspercent(int miss_percent);
    int getMisspercent();

};

class InventoryItem 
{
public:
    InventoryItem() = default;
    Item* item;
    ItemType type;
    int count = 0;
    void add(int count);
    bool remove(int count);
};

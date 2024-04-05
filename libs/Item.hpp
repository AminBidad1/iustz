#pragma once
#include "Value.hpp"
#include <vector>

enum class ItemType;

// Item
class Item
{
private:
    string name;
    int price;

public:
    Item() = default;
    Item(string name, int price);

    void setName(string name);
    string getName() const;

    void setPrice(int price);
    int getPrice() const;

    virtual void display_message();
};

class AttackingItem : public Item
{
protected:
    double damage;
    double miss_percent;

public:
    AttackingItem() = default;
    void setDamage(double damage);
    int getDamage() const;
    int getMiss_percent();
    void setMiss_percent(double miss_percent);
    virtual int attack() = 0;
};

// ThrowableItem
class ThrowableItem : public AttackingItem
{
public:
    ThrowableItem() = default;
    ThrowableItem(string name, int price, double damage);
};

class KitchenKnife : public ThrowableItem
{
public:
    KitchenKnife() = default;
    virtual int attack() override;
};

class Bomb : public ThrowableItem
{
public:
    Bomb() = default;
    virtual int attack() override;
};

class Molotov : public ThrowableItem
{
public:
    Molotov() = default;
    virtual int attack() override;
};

class Bristle : public ThrowableItem
{
public:
    Bristle() = default;
    virtual int attack() override;
};

// PassiveItem
class PassiveItem : public AttackingItem
{
private:
    bool Upgradeable;

public:
    void setUpgradeable(bool Upgradable);
    bool getUpgradeable() const;
};

// Firearms
class Firearms : public PassiveItem
{
private:
    double damage_per_ammo;
    int ammo;
    int magazine;
    int fire_rate;
    double miss_percent;

public:
    void setDamage(double damage_per_ammo);
    int getDamage();

    void setAmmo(int ammo);
    int getAmmo();

    void setMagazine(int magazine);
    int getMagazine();

    void setFirerate(int fire_rate);
    int getFirerate();

    void setMisspercent(double miss_percent);
    double getMisspercent();
};

// ColdWeapon
class ColdWeapon : public PassiveItem
{
public:
    ColdWeapon() = default;
};

class Sword : public ColdWeapon
{
    Sword() = default;
    virtual int attack() override;
};

class Stick : public ColdWeapon
{
    Stick() = default;
    virtual int attack() override;
};

class Knuckles : public ColdWeapon
{
    Knuckles() = default;
    virtual int attack() override;
};

class InventoryItem
{
public:
    InventoryItem() = default;
    Item *item;
    ItemType type;
    ItemType fatherType;
    int count = 0;
    void add(int count);
    bool remove(int count);
};

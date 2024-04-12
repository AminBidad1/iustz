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
    int size;
public:
    Item() = default;
    Item(string name, int price);

    void setName(string name);
    string getName() const;

    void setPrice(int price);
    int getPrice() const;

    virtual void display_message();
    int getSize();
    void setSize(int size);
};

class AttackingItem : public Item
{
protected:
    double damage;
    double miss_percent;
    int level;
public:
    AttackingItem() = default;
    void setDamage(double damage);
    int getDamage() const;
    int getMiss_percent();
    void setMiss_percent(double miss_percent);
    virtual double attack() = 0;
    int getLevel();
    void setLevel(int level);
    void levelup(int count);
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
    virtual double attack() override;
};

class Bomb : public ThrowableItem
{
public:
    Bomb() = default;
    virtual double attack() override;
};

class Molotov : public ThrowableItem
{
public:
    Molotov() = default;
    virtual double attack() override;
};

class Bristle : public ThrowableItem
{
public:
    Bristle() = default;
    virtual double attack() override;
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
    int magazine_size;
    double miss_percent;

public:
    void setDamage(double damage_per_ammo);
    int getDamage();

    void setMagazineSize(int magazine_size);
    int getMagazineSize();
};

class Colt : public Firearms
{
public:
    Colt() = default;
    virtual double attack() override;
};

class Kelash : public Firearms
{
public:
    Kelash() = default;
    virtual double attack() override;
};

class FlatLine : public Firearms
{
public:
    FlatLine() = default;
    virtual double attack() override;
};

// ColdWeapon
class ColdWeapon : public PassiveItem
{
public:
    ColdWeapon() = default;
};

class Sword : public ColdWeapon
{
public:
    Sword() = default;
    virtual double attack() override;
};

class Stick : public ColdWeapon
{
public:
    Stick() = default;
    virtual double attack() override;
};

class Knuckles : public ColdWeapon
{
public:
    Knuckles() = default;
    virtual double attack() override;
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

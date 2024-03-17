#include "Value.hpp"
#include <vector>

//Item
class Item {
private:
    string name;
    int price;
public:
    Item();
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
    ThrowableItem();
    ThrowableItem(string name, int damage, int price);

    void setName(string name);
    string getName() const;

    void setDamage(int damage);
    int getDamage() const;

    void setPrice(int price);
    int getPrice() const;

    ~ThrowableItem();
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

// ConsumableItem
class ConsumableItem : public Item
{
private:
    Value* value;

public:
    ConsumableItem();
    ConsumableItem(string name, int price);

    void setValue(int value);
    int getValue() const;

    virtual void consume();
};

class ManaBooster : public ConsumableItem
{
public:
    void consume(Human* target);
};

class Food : public ConsumableItem
{
public:
    void consume(Character* target);
};

class Beverage : public ConsumableItem
{
public:
    void consume(Character* target);
};
#include <iostream>
using namespace std;
class ThrowableItem
{
private:
    string name;
    int damage;
    int price;

public:
    ThrowableItem();
    ThrowableItem(string name, int damage, int price);

    void setName(string name);
    string getName() const;

    void setDamage(int damage);
    int getNameDamage() const;

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
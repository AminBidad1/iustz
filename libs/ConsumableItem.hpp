#include "Item.hpp"
#include "Value.hpp"
#include "Character.hpp"

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
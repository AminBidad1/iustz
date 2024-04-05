#pragma once
#include "Item.hpp"
#include "Value.hpp"
#include "Character.hpp"

class ConsumableItem : public Item
{
protected:
    Value* value;

public:
    ConsumableItem();
    ConsumableItem(string name, int price);

    void setValue(int value);
    int getValue() const;

    virtual void consume(Character* target) = 0;
};

class StaminaBooster : public ConsumableItem
{
public:
    StaminaBooster() = default;
    virtual void consume(Character* target) override;
};

class Food : public ConsumableItem
{
public:
    Food() = default;
    virtual void consume(Character* target) override;
};

class Beverage : public ConsumableItem
{
public:
    Beverage() = default;
    virtual void consume(Character* target) override;
};
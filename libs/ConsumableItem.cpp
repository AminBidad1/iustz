#include "ConsumableItem.hpp"

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
    target->setDefault_damage(target->getDefault_damage() + this->getValue());
}
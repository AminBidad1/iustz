#include "ConsumableItem.hpp"

ConsumableItem::ConsumableItem()
{
    value = new Value();
}
ConsumableItem::ConsumableItem(string name, int price) : Item(name, price) {};

void ConsumableItem::setValue(int value) { this->value->setValue(value); }
int ConsumableItem::getValue() const { return value->getValue(); }

//StaminaBooster
void StaminaBooster::consume(Character* target)
{
    // increasing the target's stamina by the value of item
    Human* human = (Human*)target;
    human->stamina->regenerateStamina(this->getValue());
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
    target->setDamage(target->getDamage() + this->getValue());
}
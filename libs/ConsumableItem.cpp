//ConsumableItem
#include "ConsumableItem.hpp"
ConsumableItem::ConsumableItem() = default;
ConsumableItem::ConsumableItem(string name, int price)
{
    this->name = name;
    this->price = price;
}

void ConsumableItem::setName(string name) { this->name = name; }
string ConsumableItem::getName() const { return name; }

void ConsumableItem::setValue(int value) { this->value = value; }
int ConsumableItem::getValue() const { return value; }

void ConsumableItem::setPrice(int price) { this->price = price; }
int ConsumableItem::getPrice() const { return price; }

void ConsumableItem::consume() {}

//ManaBooster
void ManaBooster::consume()
{

}

//Food
void Food::consume()
{

}

//Beverage
void Beverage::consume()
{

}
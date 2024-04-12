#include "utils.hpp"

double Store::KitchenKnifePrice = 10;
double Store::BombPrice = 10;
double Store::MolotovPrice = 10;
double Store::BristlePrice = 10;
double Store::StaminaBoosterPrice = 10;
double Store::FoodPrice = 10;
double Store::BeveragePrice = 10; 
double Store::ColtPrice = 10;
double Store::KelashPrice = 10;
double Store::FlatLinePrice = 10;
double Store::SwordPrice = 8;
double Store::StickPrice = 5;
double Store::KnucklesPrice = 4;


std::string itemTypeMap(ItemType type)
{
    switch (type)
    {
    case ItemType::KitchenKnife:
        return "Kitchen Knife";
    case ItemType::Bomb:
        return "Bomb";
    case ItemType::Molotov:
        return "Molotov";
    case ItemType::Bristle:
        return "Bristle";
    case ItemType::StaminaBooster:
        return "Stamina Booster";
    case ItemType::Food:
        return "Food";
    case ItemType::Beverage:
        return "Beverage";
    case ItemType::Colt:
        return "Colt";
    case ItemType::Kelash:
        return "Kelash";
    case ItemType::FlatLine:
        return "Flat Line";
    case ItemType::Sword:
        return "Sword";
    case ItemType::Stick:
        return "Stick";
    case ItemType::Knuckles:
        return "Knuckles";
    default:
        return "";
    }
}

int itemPriceMap(ItemType type)
{
    switch (type)
    {
    case ItemType::KitchenKnife:
        return Store::KitchenKnifePrice;
    case ItemType::Bomb:
        return Store::BombPrice;
    case ItemType::Molotov:
        return Store::MolotovPrice;
    case ItemType::Bristle:
        return Store::BristlePrice;
    case ItemType::StaminaBooster:
        return Store::StaminaBoosterPrice;
    case ItemType::Food:
        return Store::FoodPrice;
    case ItemType::Beverage:
        return Store::BeveragePrice;
    case ItemType::Colt:
        return Store::ColtPrice;
    case ItemType::Kelash:
        return Store::KelashPrice;
    case ItemType::FlatLine:
        return Store::FlatLinePrice;
    case ItemType::Sword:
        return Store::SwordPrice;
    case ItemType::Stick:
        return Store::StickPrice;
    case ItemType::Knuckles:
        return Store::KnucklesPrice;
    default:
        return 0;
    }
}

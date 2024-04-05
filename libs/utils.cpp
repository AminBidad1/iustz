#include "utils.hpp"

std::string itemTypeMap(ItemType type)
{
    switch (type)
    {
    case ItemType::KitchenKnife:
        return "Kitchen Knife";
    case ItemType::Bomb:
        return "Bomb";
    case ItemType::Molotov:
        return "Molotove";
    case ItemType::Bristle:
        return "Bristle";
    case ItemType::StaminaBooster:
        return "Stamina Booster";
    case ItemType::Food:
        return "Food";
    case ItemType::Beverage:
        return "Beverage";
    default:
        return "";
    }
}

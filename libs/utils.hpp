#pragma once
#include "string"

enum class State
{
    Start,
    LowHP,
    LowStamina,
    Attack
};

enum class ValueType
{
    HP,
    Stamina,
    XP,
    Money
};

enum class ItemType
{
    ConsumableItem,
    ThrowableItem,
    PassiveItem, // Father types
    KitchenKnife,
    Bomb,
    Molotov,
    Bristle, // Throwable Items
    StaminaBooster,
    Food,
    Beverage, // Consumable Items
};

const int MIN_ITEM_INDEX = 3;
const int MAX_ITEM_INDEX = 9;
const int MIN_THROWABLE_ITEM_INDEX = 3;
const int MAX_THROWABLE_ITEM_INDEX = 6;
const int MIN_CONSUMABLE_ITEM_INDEX = 7;
const int MAX_CONSUMABLE_ITEM_INDEX = 9;

enum class CharacterType
{
    Zombie,
    Human,
    EnemyHuman
};

enum class PlayerState
{
    Shop,
    Attack
};

std::string itemTypeMap(ItemType type);

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


static int KitchenKnifePrice = 10;
static int BombPrice = 10;
static int MolotovPrice = 10;
static int BristlePrice = 10;
static int StaminaBoosterPrice = 10;
static int FoodPrice = 10;
static int BeveragePrice = 10; 

enum class CharacterType
{
    Zombie, Human, HumanEnemy
};

enum class EnemyType
{
    Zombie, HumanEnemy
};

const int ENEMY_COUNT = 2;

enum class PlayerState
{
    Shop,
    Attack
};

std::string itemTypeMap(ItemType type);

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
    ConsumableItem, // Father types
    ThrowableItem,
    PassiveItem,
    KitchenKnife, // Throwable Items
    Bomb,
    Molotov,
    Bristle,
    StaminaBooster, // Consumable Items
    Food,
    Beverage,
    Colt,  // Passive Items
    Kelash,
    FlatLine,
    Sword,
    Stick,
    Knuckles,
};

const int MIN_ITEM_INDEX = 3;
const int MAX_ITEM_INDEX = 15;
const int MIN_THROWABLE_ITEM_INDEX = 3;
const int MAX_THROWABLE_ITEM_INDEX = 6;
const int MIN_CONSUMABLE_ITEM_INDEX = 7;
const int MAX_CONSUMABLE_ITEM_INDEX = 9;
const int MIN_PASSIVE_ITEM_INDEX = 10;
const int MAX_PASSIVE_ITEM_INDEX = 15;


class Store
{
public:
    static double KitchenKnifePrice;
    static double BombPrice;
    static double MolotovPrice;
    static double BristlePrice;
    static double StaminaBoosterPrice;
    static double FoodPrice;
    static double BeveragePrice;
    static double ColtPrice;
    static double KelashPrice;
    static double FlatLinePrice;
    static double SwordPrice;
    static double StickPrice;
    static double KnucklesPrice;
};

enum class PlayerType
{
    Human, Attacker, Tank, Healer
};

enum class EnemyType
{
    Zombie, HumanEnemy, UltraZombie, VampireZombie, UltraVampireZombie
};

const int ENEMY_COUNT = 4;

enum class PlayerState
{
    Shop,
    Attack
};

std::string itemTypeMap(ItemType type);
enum class ShopSection
{
    Buy , Sell , Leave
};
int itemPriceMap(ItemType type);

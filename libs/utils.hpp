#pragma once

enum class State
{
    Start, LowHP, LowStamina, Attack
};

enum class ValueType
{
    HP, Stamina, XP, Money
};

enum class ItemType
{
    ThrowableItem, KitchenKnife, Grande, Molotov,
    Bristle, PassiveItem, Firearms, ConsumableItem,
    StaminaBooster, Food, Beverage
};

enum class CharacterType
{
    Zombie, Human, EnemyHuman
};

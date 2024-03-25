#include "GameManager.hpp"

Value* ValueController::createValue(ValueType type)
{
    if (type == ValueType::HP)
    {
        HP hp = HP(100);
        return &hp;
    }
    else if (type == ValueType::Stamina)
    {
        Stamina stamina = Stamina(100);
        return &stamina;
    }
    else if (type == ValueType::XP)
    {
        XP xp = XP(1);
        return &xp;
    }
    else if (type == ValueType::Money)
    {
        Money money = Money(100);
        return &money;
    }
    return nullptr;
}

Item* ItemController::createItem(ItemType type)
{
    if (type == ItemType::Food)
    {
        Food food = Food();
        food.setName("Pizza");
        food.setPrice(10); // TODO: Move it to shop class
        food.setValue(5);
        return &food;
    }
    else if (type == ItemType::StaminaBooster)
    {
        StaminaBooster staminaBooster = StaminaBooster();
        staminaBooster.setName("Stamina Booster");
        staminaBooster.setPrice(10);
        staminaBooster.setValue(5);
        return &staminaBooster;
    }
    else if (type == ItemType::Beverage)
    {
        Beverage beverage = Beverage();
        beverage.setName("PEPSI");
        beverage.setPrice(10);
        beverage.setValue(5);
        return &beverage;
    }
    else if (type == ItemType::KitchenKnife)
    {
        KitchenKnife kitchenKnife = KitchenKnife();
        kitchenKnife.setName("Kitchen Kife");
        kitchenKnife.setPrice(10);
        kitchenKnife.setDamage(10);
        return &kitchenKnife;
    }
    else if (type == ItemType::Grande)
    {
        Grande grande = Grande();
        grande.setName("Grande");
        grande.setPrice(10);
        grande.setDamage(8);
        return &grande;
    }
    else if (type == ItemType::Molotov)
    {
        Molotov molotov = Molotov();
        molotov.setName("molotov");
        molotov.setPrice(10);
        molotov.setDamage(8);
        return &molotov;
    }
    else if (type == ItemType::Bristle)
    {
        Bristle bristle = Bristle();
        bristle.setName("molotov");
        bristle.setPrice(10);
        bristle.setDamage(8);
        return &bristle;
    }
    else if (type == ItemType::Firearms)
    {
        Firearms firearms = Firearms();
        firearms.setName("firearm");
        firearms.setPrice(10);
        firearms.setDamage(15);
        firearms.setAmmo(100);
        firearms.setFirerate(5);
        return &firearms;
    }
    return nullptr;
}

Character* CharacterController::createCharacter(CharacterType type)
{
    if (type == CharacterType::Human)
    {
        vector<InventoryItem> items;
        vector<Skill*> skills;
        Human human = Human(
            "player", 18, "man", (HP*)ValueController::createValue(ValueType::HP),
            (Money*)ValueController::createValue(ValueType::Money), 
            (Stamina*)ValueController::createValue(ValueType::Stamina),
            (XP*)ValueController::createValue(ValueType::XP), skills, items
        );
        return &human;
    }
}

Zombie* CharacterController::createZombie(int level)
{
    int damage = pow(1.2, level) * DEFAULT_DAMAGE;
    Zombie zombie = Zombie(
        "zombie", 150, "man", 
        (HP*)ValueController::createValue(ValueType::HP),
        (Money*)ValueController::createValue(ValueType::Money), damage
    );
    return &zombie;
}

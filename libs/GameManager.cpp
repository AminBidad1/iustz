#include "GameManager.hpp"

Value* ValueController::createValue(ValueType type)
{
    Value* value;
    if (type == ValueType::HP)
    {
        HP* hp = new HP(100);
        value = hp;
    }
    else if (type == ValueType::Stamina)
    {
        Stamina* stamina = new Stamina(100);
        value = stamina;
    }
    else if (type == ValueType::XP)
    {
        XP* xp = new XP(1);
        value = xp;
    }
    else if (type == ValueType::Money)
    {
        Money* money = new Money(100);
        value = money;
    }
    return value;
}

Item* ItemController::createItem(ItemType type)
{
    Item* item;
    if (type == ItemType::Food)
    {
        Food* food = new Food();
        food->setName("Pizza");
        food->setPrice(10); // TODO: Move it to shop class
        food->setValue(5);
        item = food;
    }
    else if (type == ItemType::StaminaBooster)
    {
        StaminaBooster* staminaBooster = new StaminaBooster();
        staminaBooster->setName("Stamina Booster");
        staminaBooster->setPrice(10);
        staminaBooster->setValue(5);
        item = staminaBooster;
    }
    else if (type == ItemType::Beverage)
    {
        Beverage* beverage = new Beverage();
        beverage->setName("PEPSI");
        beverage->setPrice(10);
        beverage->setValue(5);
        item = beverage;
    }
    else if (type == ItemType::KitchenKnife)
    {
        KitchenKnife* kitchenKnife = new KitchenKnife();
        kitchenKnife->setName("Kitchen Kife");
        kitchenKnife->setPrice(10);
        kitchenKnife->setDamage(10);
        item = kitchenKnife;
    }
    else if (type == ItemType::Grande)
    {
        Grande* grande = new Grande();
        grande->setName("Grande");
        grande->setPrice(10);
        grande->setDamage(8);
        item = grande;
    }
    else if (type == ItemType::Molotov)
    {
        Molotov* molotov = new Molotov();
        molotov->setName("molotov");
        molotov->setPrice(10);
        molotov->setDamage(8);
        item = molotov;
    }
    else if (type == ItemType::Bristle)
    {
        Bristle* bristle = new Bristle();
        bristle->setName("molotov");
        bristle->setPrice(10);
        bristle->setDamage(8);
        item = bristle;
    }
    else if (type == ItemType::Firearms)
    {
        Firearms* firearms = new Firearms();
        firearms->setName("firearm");
        firearms->setPrice(10);
        firearms->setDamage(15);
        firearms->setAmmo(100);
        firearms->setFirerate(5);
        item = firearms;
    }
    return item;
}

Character* CharacterController::createCharacter(CharacterType type)
{
    Character* character;
    if (type == CharacterType::Human)
    {
        vector<InventoryItem> items;
        vector<Skill*> skills;
        Human* human = new Human(
            "player", 18, "man", (HP*)ValueController::createValue(ValueType::HP),
            (Money*)ValueController::createValue(ValueType::Money), 
            (Stamina*)ValueController::createValue(ValueType::Stamina),
            (XP*)ValueController::createValue(ValueType::XP), skills, items
        );
        human->setDefault_damage(5);
        character = human;
    }
    return character;
}

Zombie* CharacterController::createZombie(int level)
{
    int damage = pow(1.2, level) * DEFAULT_DAMAGE;
    Zombie* zombie = new Zombie(
        "zombie", 150, "man", 
        (HP*)ValueController::createValue(ValueType::HP),
        (Money*)ValueController::createValue(ValueType::Money), damage
    );
    return zombie;
}

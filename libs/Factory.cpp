#include "Factory.hpp"

int CharacterFactory::player_index = 1;

Value* ValueFactory::createValue(ValueType type)
{
    Value* value;
    if (type == ValueType::HP)
    {
        value = ValueFactory::createCustomValue(type, 100);
    }
    else if (type == ValueType::Stamina)
    {
        value = ValueFactory::createCustomValue(type, 100);
    }
    else if (type == ValueType::XP)
    {
        value = ValueFactory::createCustomValue(type, 1);
    }
    else if (type == ValueType::Money)
    {
        value = ValueFactory::createCustomValue(type, 100);
    }
    return value;
}

Value* ValueFactory::createCustomValue(ValueType type, int valueAmount)
{
    Value* value;
    if (type == ValueType::HP)
    {
        HP* hp = new HP(valueAmount);
        hp->MIN_VALUE = 0;
        hp->MAX_VALUE = valueAmount;
        value = hp;
    }
    else if (type == ValueType::Stamina)
    {
        Stamina* stamina = new Stamina(valueAmount);
        stamina->MIN_VALUE = 0;
        stamina->MAX_VALUE = valueAmount;
        value = stamina;
    }
    else if (type == ValueType::XP)
    {
        XP* xp = new XP(valueAmount);
        value = xp;
    }
    else if (type == ValueType::Money)
    {
        Money* money = new Money(valueAmount);
        value = money;
    }
    return value;
}

Item* ItemFactory::createItem(ItemType type, int level)
{
    Item* item;
    if (type == ItemType::Food)
    {
        Food* food = new Food();
        food->setName("Pizza");
        food->setPrice(Store::FoodPrice);
        food->setValue(15);
        food->setSize(5);
        item = food;
    }
    else if (type == ItemType::StaminaBooster)
    {
        StaminaBooster* staminaBooster = new StaminaBooster();
        staminaBooster->setName("Stamina Booster");
        staminaBooster->setPrice(Store::StaminaBoosterPrice);
        staminaBooster->setValue(15);
        staminaBooster->setSize(5);
        item = staminaBooster;
    }
    else if (type == ItemType::Beverage)
    {
        Beverage* beverage = new Beverage();
        beverage->setName("PEPSI");
        beverage->setPrice(Store::BeveragePrice);
        beverage->setValue(15);
        beverage->setSize(5);
        item = beverage;
    }
    else if (type == ItemType::KitchenKnife)
    {
        KitchenKnife* kitchenKnife = new KitchenKnife();
        kitchenKnife->setName("Kitchen Knife");
        kitchenKnife->setPrice(Store::KitchenKnifePrice);
        kitchenKnife->setDamage(60);
        kitchenKnife->setMiss_percent(80);
        kitchenKnife->setLevel(level);
        kitchenKnife->setSize(4);
        item = kitchenKnife;
    }
    else if (type == ItemType::Bomb)
    {
        Bomb* bomb = new Bomb();
        bomb->setName("Bomb");
        bomb->setPrice(Store::BombPrice);
        bomb->setDamage(500);
        bomb->setMiss_percent(60);
        bomb->setLevel(level);
        bomb->setSize(8);
        item = bomb;
    }
    else if (type == ItemType::Molotov)
    {
        Molotov* molotov = new Molotov();
        molotov->setName("molotov");
        molotov->setPrice(Store::MolotovPrice);
        molotov->setDamage(300);
        molotov->setMiss_percent(25);
        molotov->setLevel(level);
        molotov->setSize(6);
        item = molotov;
    }
    else if (type == ItemType::Bristle)
    {
        Bristle* bristle = new Bristle();
        bristle->setName("Bristle");
        bristle->setPrice(Store::BristlePrice);
        bristle->setDamage(120);
        bristle->setMiss_percent(90);
        bristle->setLevel(level);
        bristle->setSize(3);
        item = bristle;
    }
    else if (type == ItemType::Colt)
    {
        Colt* colt = new Colt();
        colt->setName("Colt");
        colt->setPrice(Store::ColtPrice);
        colt->setDamage(15);
        colt->setMiss_percent(30);
        colt->setMagazineSize(5);
        colt->setLevel(level);
        colt->setSize(5);
        item = colt;
    }
    else if (type == ItemType::Kelash)
    {
        Kelash* gun = new Kelash();
        gun->setName("Kelash");
        gun->setPrice(Store::KelashPrice);
        gun->setDamage(10);
        gun->setMiss_percent(40);
        gun->setMagazineSize(8);
        gun->setLevel(level);
        gun->setSize(7);
        item = gun;
    }
    else if (type == ItemType::FlatLine)
    {
        FlatLine* gun = new FlatLine();
        gun->setName("Flat Line");
        gun->setPrice(Store::FlatLinePrice);
        gun->setDamage(10);
        gun->setMiss_percent(50);
        gun->setMagazineSize(10);
        gun->setLevel(level);
        gun->setSize(11);
        item = gun;
    }
    else if (type == ItemType::Sword)
    {
        Sword* sword = new Sword();
        sword->setName("Sword");
        sword->setPrice(Store::SwordPrice);
        sword->setDamage(50);
        sword->setMiss_percent(0);
        sword->setLevel(level);
        sword->setSize(8);
        item = sword;
    }
    else if (type == ItemType::Stick)
    {
        Stick* stick = new Stick();
        stick->setName("stick");
        stick->setPrice(Store::StickPrice);
        stick->setDamage(30);
        stick->setMiss_percent(0);
        stick->setLevel(level);
        stick->setSize(5);
        item = stick;
    }
    else if (type == ItemType::Knuckles)
    {
        Knuckles* knuckles = new Knuckles();
        knuckles->setName("Knuckles");
        knuckles->setPrice(Store::KnucklesPrice);
        knuckles->setDamage(20);
        knuckles->setMiss_percent(0);
        knuckles->setLevel(level);
        knuckles->setSize(3);
        item = knuckles;
    }
    return item;
}

Character* CharacterFactory::createCharacter(PlayerType type)
{
    Character* character;
    if (type == PlayerType::Human)
    {
        vector<InventoryItem*> items;
        vector<Skill*> skills;
        string name = "Player" + to_string(player_index);
        Human* human = new Human(
            name, 18, "man", (HP*)ValueFactory::createCustomValue(ValueType::HP, Human::DEFAULT_HP),
            (Money*)ValueFactory::createValue(ValueType::Money), 
            (Stamina*)ValueFactory::createValue(ValueType::Stamina),
            (XP*)ValueFactory::createValue(ValueType::XP), skills, items, Human::DEFAULT_DAMAGE
        );
        human->MAX_INVENTORY_SIZE = 100;
        human->occupied_volume = 0;
        character = human;
    }
    else if (type == PlayerType::Attacker)
    {
        vector<InventoryItem*> items;
        vector<Skill*> skills;
        string name = "Player Attacker " + to_string(player_index);
        Attacker* attacker = new Attacker(
            name, 18, "man", 
            (HP*)ValueFactory::createCustomValue(ValueType::HP, Attacker::DEFAULT_HP),
            (Money*)ValueFactory::createValue(ValueType::Money), 
            (Stamina*)ValueFactory::createValue(ValueType::Stamina),
            (XP*)ValueFactory::createValue(ValueType::XP), skills, items, 
            Attacker::DEFAULT_DAMAGE
        );
        attacker->MAX_INVENTORY_SIZE = 150;
        attacker->occupied_volume = 0;
        character = attacker;
    }
    else if (type == PlayerType::Tank)
    {
        vector<InventoryItem*> items;
        vector<Skill*> skills;
        string name = "Player Tank " + to_string(player_index);
        Tank* tank = new Tank(
            name, 18, "man", 
            (HP*)ValueFactory::createCustomValue(ValueType::HP, Tank::DEFAULT_HP),
            (Money*)ValueFactory::createValue(ValueType::Money), 
            (Stamina*)ValueFactory::createValue(ValueType::Stamina),
            (XP*)ValueFactory::createValue(ValueType::XP), skills, items, 
            Tank::DEFAULT_DAMAGE
        );
        tank->MAX_INVENTORY_SIZE = 100;
        tank->occupied_volume = 0;
        character = tank;
    }
    else if (type == PlayerType::Healer)
    {
        vector<InventoryItem*> items;
        vector<Skill*> skills;
        string name = "Player Healer " + to_string(player_index);
        Healer* healer = new Healer(
            name, 18, "man", 
            (HP*)ValueFactory::createCustomValue(ValueType::HP, Healer::DEFAULT_HP),
            (Money*)ValueFactory::createValue(ValueType::Money), 
            (Stamina*)ValueFactory::createValue(ValueType::Stamina),
            (XP*)ValueFactory::createValue(ValueType::XP), skills, items, 
            Healer::DEFAULT_DAMAGE
        );
        healer->MAX_INVENTORY_SIZE = 100;
        healer->occupied_volume = 0;
        character = healer;
    }

    player_index++;
    return character;
}

Human* CharacterFactory::createCustomHuman(string name, int age, string gender,
                                              vector<Skill*> skills, Money* money, double damage)
{
    vector<InventoryItem*> items;
    Human* human = new Human(
        name, age, gender, 
        (HP*)ValueFactory::createValue(ValueType::HP), money, 
        (Stamina*)ValueFactory::createValue(ValueType::Stamina),
        (XP*)ValueFactory::createValue(ValueType::XP), skills, items, damage
    );
    return human;
}

Zombie* CharacterFactory::createZombie(int level)
{
    double damage = pow(1.2, level) * DEFAULT_DAMAGE;
    string name = "Zombie " + to_string(level+1);
    Zombie* zombie = new Zombie(
        name, 150, "man", 
        (HP*)ValueFactory::createCustomValue(ValueType::HP, (level + 1) * 50),
        (Money*)ValueFactory::createCustomValue(ValueType::Money, level*20),
        damage
    );
    return zombie;
}

HumanEnemy* CharacterFactory::createHumanEnemy(int level)
{
    double damage = pow(1.2, level) * DEFAULT_DAMAGE;
    string name = "Human Enemy " + to_string(level+1);
    HumanEnemy* enemy = new HumanEnemy(
        name, 20, "Man",
        (HP*)ValueFactory::createCustomValue(ValueType::HP, (level + 1) * 40),
        (Money*)ValueFactory::createCustomValue(ValueType::Money, level*40),
        (Stamina*)ValueFactory::createCustomValue(ValueType::Stamina, 50 + 5 * level),
        (XP*)ValueFactory::createCustomValue(ValueType::XP, level+1), damage
    );
    enemy->defaultHp = (level + 1) * 40;
    enemy->defaultStamina = 50 + 5 * level;
    int random_number;
    Item* item;
    InventoryItem* inventoryItem;

    for (int i=0; i < 1 + level; i++)
    {
        inventoryItem = new InventoryItem();
        random_number = ((rand() % (MAX_ITEM_INDEX - MIN_ITEM_INDEX + 1)) + MIN_ITEM_INDEX);
        inventoryItem->count = 1;
        inventoryItem->type = ItemType(random_number);
        item = ItemFactory::createItem(inventoryItem->type, level);
        if (MIN_THROWABLE_ITEM_INDEX <= random_number && random_number <= MAX_THROWABLE_ITEM_INDEX)
        {
            inventoryItem->fatherType = ItemType::ThrowableItem;
            ThrowableItem* throwableItem = (ThrowableItem*)item;
            throwableItem->setLevel(level);
            inventoryItem->item = throwableItem;
        }
        else if (MIN_CONSUMABLE_ITEM_INDEX <= random_number && random_number <= MAX_CONSUMABLE_ITEM_INDEX)
        {
            inventoryItem->fatherType = ItemType::ConsumableItem;
            ConsumableItem* consumableItem = (ConsumableItem*)item;
            inventoryItem->item = consumableItem;
        }
        else if (MIN_PASSIVE_ITEM_INDEX <= random_number && random_number <= MAX_PASSIVE_ITEM_INDEX)
        {
            inventoryItem->fatherType = ItemType::PassiveItem;
            PassiveItem* passiveItem = (PassiveItem*)item;
            passiveItem->setLevel(level);
            inventoryItem->item = passiveItem;
        }
        
        enemy->addItem(inventoryItem, 1 + level * 2);
    }

    return enemy;
}

VampireZombie* CharacterFactory::createVampireZombie(int level)
{
    double damage = pow(1.1, level) * DEFAULT_DAMAGE;
    string name = "Vampire Zombie " + to_string(level+1);
    VampireZombie* vampireZombie = new VampireZombie(
        name, 150, "man", 
        (HP*)ValueFactory::createCustomValue(ValueType::HP, (level + 1) * 45),
        (Money*)ValueFactory::createCustomValue(ValueType::Money, level*20),
        damage
    );
    return vampireZombie;
}

UltraZombie* CharacterFactory::createUltraZombie(int level)
{
    double damage = pow(1.2, level) * DEFAULT_DAMAGE;
    string name = "Ultra Zombie " + to_string(level+1);
    UltraZombie* ultraZombie = new UltraZombie(
        name, 150, "man", 
        (HP*)ValueFactory::createCustomValue(ValueType::HP, (level + 1) * 60),
        (Money*)ValueFactory::createCustomValue(ValueType::Money, level*20),
        damage
    );
    return ultraZombie;
}

UltraVampireZombie* CharacterFactory::createUltraVampireZombie(int level)
{
    double damage = pow(1.2, level) * DEFAULT_DAMAGE;
    string name = "Ultra Vampire Zombie " + to_string(level+1);
    UltraVampireZombie* enemy = new UltraVampireZombie(
        name, 20, "Man",
        (HP*)ValueFactory::createCustomValue(ValueType::HP, (level + 1) * 50),
        (Money*)ValueFactory::createCustomValue(ValueType::Money, level*40),
        (Stamina*)ValueFactory::createCustomValue(ValueType::Stamina, 50 + 5 * level),
        (XP*)ValueFactory::createCustomValue(ValueType::XP, level+1), damage
    );
    enemy->defaultHp = (level + 1) * 50;
    enemy->defaultStamina = 50 + 5 * level;
    int random_number;
    Item* item;
    InventoryItem* inventoryItem;

    for (int i=0; i < 1 + level; i++)
    {
        inventoryItem = new InventoryItem();
        random_number = ((rand() % (MAX_ITEM_INDEX - MIN_ITEM_INDEX + 1)) + MIN_ITEM_INDEX);
        inventoryItem->count = 1;
        inventoryItem->type = ItemType(random_number);
        if (MIN_THROWABLE_ITEM_INDEX <= random_number && random_number <= MAX_THROWABLE_ITEM_INDEX)
        {
            inventoryItem->fatherType = ItemType::ThrowableItem;
        }
        else if (MIN_CONSUMABLE_ITEM_INDEX <= random_number && random_number <= MAX_CONSUMABLE_ITEM_INDEX)
        {
            inventoryItem->fatherType = ItemType::ConsumableItem;
        }
        item = ItemFactory::createItem(inventoryItem->type, level);
        inventoryItem->item = item;
        enemy->addItem(inventoryItem, 1 + level * 2);
    }

    return enemy;
}

#include "GameManager.hpp"

Value* ValueController::createValue(ValueType type)
{
    Value* value;
    if (type == ValueType::HP)
    {
        value = ValueController::createCustomValue(type, 100);
    }
    else if (type == ValueType::Stamina)
    {
        value = ValueController::createCustomValue(type, 100);
    }
    else if (type == ValueType::XP)
    {
        value = ValueController::createCustomValue(type, 1);
    }
    else if (type == ValueType::Money)
    {
        value = ValueController::createCustomValue(type, 100);
    }
    return value;
}

Value* ValueController::createCustomValue(ValueType type, int valueAmount)
{
    Value* value;
    if (type == ValueType::HP)
    {
        HP* hp = new HP(valueAmount);
        value = hp;
    }
    else if (type == ValueType::Stamina)
    {
        Stamina* stamina = new Stamina(valueAmount);
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

Human* CharacterController::createCustomHuman(string name, int age, string gender,
                                              vector<Skill*> skills, Money* money, int damage)
{
    vector<InventoryItem> items;
    Human* human = new Human(
        name, age, gender, 
        (HP*)ValueController::createValue(ValueType::HP), money, 
        (Stamina*)ValueController::createValue(ValueType::Stamina),
        (XP*)ValueController::createValue(ValueType::XP), skills, items
    );
    human->setDefault_damage(damage);
    return human;
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


GameManager::GameManager(vector<Human*> players, Character* enemy, int round_index, int level, PlayerState state)
{
    this->players = players;
    this->enemy = enemy;
    this->round_index = round_index;
    this->level = level;
    this->state = state;
}

PlayerState GameManager::getNextState()
{
    int random_number = rand() % 100;
    if (random_number >= 70)
    {
        return PlayerState::Attack;
    }
    return PlayerState::Shop;
}

void GameManager::attack()
{
    // TODO: Handle Enemy Human
    Zombie* zombie = (Zombie*)enemy;
    while (zombie->hp->getValue() !=0 || players[round_index % players.size()]->hp->getValue()!=0)
    {
        if (zombie->attack(players[round_index % players.size()], zombie->getDefault_damage()))
        {
            ZombieView::showAttack(players[round_index % players.size()], zombie);
            CharacterView::showWasKilled(players[round_index % players.size()]);
            players.erase(next(players.begin(), (round_index + 1) % players.size()));
            if (players.size() == 0)
            {
                cout << "YOU LOST!" << endl;
                exit(0);
            }
        }
        else 
        {
            ZombieView::showAttack(players[round_index % players.size()] , zombie);
            HumanView::showTakeDamage(players[round_index % players.size()]);
        }

        // TODO: use items to attack

        if (players[round_index % players.size()]->attack(zombie, players[round_index % players.size()]->getDefault_damage()))
        {
            ZombieView::showWasKilled(zombie);
            level++;
            return;
        }
        round_index++;
    }
}

void GameManager::goShop()
{
    Human* player = players[round_index % players.size()];
    HumanView::showStatus(player);
    InventoryItem inventoryItem;
    Item* item;
    do {
        inventoryItem = HumanView::selecetItem();
        item = ItemController::createItem(inventoryItem.type);
        // TODO: Handle price
        if (player->buyItem(item, inventoryItem.type, inventoryItem.count, 10))
        {
            HumanView::successBuy();
        }
        else 
        {
            HumanView::failedBuy();
        }
        if (!ShopView::stay())
            break;
    } while (true);
}

void GameManager::startRound()
{
    while (true)
    {
        if (state == PlayerState::Shop)
        {
            goShop();
        }
        else if (state == PlayerState::Attack)
        {
            attack();
        }
        state = getNextState();
        enemy = CharacterController::createZombie(level);
    }
}

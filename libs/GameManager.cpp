#include "GameManager.hpp"

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

Item* ItemFactory::createItem(ItemType type)
{
    Item* item;
    if (type == ItemType::Food)
    {
        Food* food = new Food();
        food->setName("Pizza");
        food->setPrice(FoodPrice); // TODO: Move it to shop class
        food->setValue(15);
        item = food;
    }
    else if (type == ItemType::StaminaBooster)
    {
        StaminaBooster* staminaBooster = new StaminaBooster();
        staminaBooster->setName("Stamina Booster");
        staminaBooster->setPrice(StaminaBoosterPrice);
        staminaBooster->setValue(15);
        item = staminaBooster;
    }
    else if (type == ItemType::Beverage)
    {
        Beverage* beverage = new Beverage();
        beverage->setName("PEPSI");
        beverage->setPrice(BeveragePrice);
        beverage->setValue(15);
        item = beverage;
    }
    else if (type == ItemType::KitchenKnife)
    {
        KitchenKnife* kitchenKnife = new KitchenKnife();
        kitchenKnife->setName("Kitchen Knife");
        kitchenKnife->setPrice(KitchenKnifePrice);
        kitchenKnife->setDamage(50);
        kitchenKnife->setMiss_percent(50);
        item = kitchenKnife;
    }
    else if (type == ItemType::Bomb)
    {
        Bomb* bomb = new Bomb();
        bomb->setName("Bomb");
        bomb->setPrice(BombPrice);
        bomb->setDamage(300);
        bomb->setMiss_percent(30);
        item = bomb;
    }
    else if (type == ItemType::Molotov)
    {
        Molotov* molotov = new Molotov();
        molotov->setName("molotov");
        molotov->setPrice(MolotovPrice);
        molotov->setDamage(100);
        molotov->setMiss_percent(10);
        item = molotov;
    }
    else if (type == ItemType::Bristle)
    {
        Bristle* bristle = new Bristle();
        bristle->setName("Bristle");
        bristle->setPrice(BristlePrice);
        bristle->setDamage(70);
        bristle->setMiss_percent(60);
        item = bristle;
    }
    return item;
}

Character* CharacterFactory::createCharacter(CharacterType type)
{
    Character* character;
    if (type == CharacterType::Human)
    {
        vector<InventoryItem*> items;
        vector<Skill*> skills;
        string name = "Player" + to_string(player_index);
        Human* human = new Human(
            name, 18, "man", (HP*)ValueFactory::createValue(ValueType::HP),
            (Money*)ValueFactory::createValue(ValueType::Money), 
            (Stamina*)ValueFactory::createValue(ValueType::Stamina),
            (XP*)ValueFactory::createValue(ValueType::XP), skills, items, DEFAULT_DAMAGE
        );
        player_index++;
        character = human;
    }
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

    for (int i=0; i < 1 + 2*level; i++)
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
        item = ItemFactory::createItem(inventoryItem->type);
        inventoryItem->item = item;
        enemy->addItem(inventoryItem, level);
    }

    return enemy;
}


GameManager::GameManager(vector<Human*> players, EnemyController* enemyController, int round_index, int level, PlayerState state)
{
    this->players = players;
    this->enemyController = enemyController;
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

    Character* enemy = enemyController->getModel();


    Human* player = players[round_index % players.size()];
    int choice;
    int selected_index = -1;
    int players_size = players.size();
    while (true)
    {
        HumanView::showStatus(player);
        CharacterView::showStatus(enemy, enemyController->type);
        // Check stamina
        if (player->stamina->getValue() <= 5) 
        {
            HumanView::showLowStamina(player->get_name());
            player->stamina->regenerateStamina(3);
        }
        else
        {
            // Use item from inventory
            choice = HumanView::selectInventoryItem(player->items);
            if (choice == player->items.size())
            {}
            else
            {
                if (player->items[choice]->count > 0)
                {
                    player->useItem(choice);
                    HumanView::showUseItem(player->getItem(choice)->item);
                    selected_index = choice;
                }
                else
                {
                    HumanView::failedUseItem(player->getItem(choice)->item);
                }
            }
            
            player->setDamage(player->stamina->getValue() * player->getDamage() / 50);

            // Attack from player
            if (player->attack(enemy, player->getDamage())) // kill enemy
            {
                HumanView::showAttack(player, enemy);
                CharacterView::showWasKilled(enemy);
                HumanView::congratulations(enemy->get_name());
                level++;
                player->getXp()->gainXP(level);
                player->money->append(enemy->money->getValue());
                // Levelup Skill
                if (selected_index != -1)
                {
                    player->skills[selected_index]->levelup(1);
                    HumanView::levelupSkill(player->items[selected_index]);
                }
                player->setDamage(CharacterFactory::DEFAULT_DAMAGE);
                return;
            }
            else
            {
                HumanView::showAttack(player, enemy);
                CharacterView::showTakeDamage(enemy);
                player->stamina->useStamina(5);
            }
        }

        // Attack from enemy
        while (enemyController->getNextState() != State::Attack)
        {
            enemyController->work(player);
        }

        if (enemyController->work(player)) // Kill player
        {
            CharacterView::showAttack(player, enemy);
            CharacterView::showWasKilled(player);
            players_size = players.size();
            players.erase(players.begin() + ((round_index) % players_size));
            if (players.size() == 0)
            {
                cout << "YOU LOST!" << endl;
                exit(0);
            }
            player = players[round_index % players.size()];
        }
        else 
        {
            CharacterView::showAttack(enemy, player);
            HumanView::showTakeDamage(player);
        }

        // Restore
        player->setDamage(CharacterFactory::DEFAULT_DAMAGE);
        selected_index = -1;
        enemyController->getModel()->setDamage(pow(1.2, level) * CharacterFactory::DEFAULT_DAMAGE);

        // Turn round
        round_index++;
        player = players[round_index % players.size()];
    }
}

void GameManager::goShop()
{
    Human* player = players[round_index % players.size()];
    InventoryItem* inventoryItem;
    Item* item;
    while(true)
    {
        HumanView::showStatus(player);
        if(ShopView::buySection())
        {
            inventoryItem = HumanView::selecetItem();
            item = ItemFactory::createItem(inventoryItem->type);
            inventoryItem->item = item;
            if (player->buyItem(inventoryItem, item->getPrice()))
            {
                HumanView::successBuy();
                GameManager::increasePrice(inventoryItem->type, inventoryItem->count);
            }
            else 
            {
                HumanView::failedBuy();
            }
        }
        else
        {
            int index = ShopView::sellItems(player);
            if (index != -1)
            {
                // Selling price is 10% less than real price
                player->money->setValue(player->money->getValue() + (player->items[index]->item->getPrice()) - (player->items[index]->item->getPrice())/10);
                player->removeItem(index, 1);
            }
        }
        if (!ShopView::stay())
            break;
    }
}

void GameManager::startRound()
{
    while (true)
    {
        if (state == PlayerState::Shop)
        {
            for (int i=0; i < players.size(); i++)
            {
                goShop();
                round_index++;
            }
            attack();
        }
        else if (state == PlayerState::Attack)
        {
            attack();
        }
        state = getNextState();
        _changeEnemyController();
    }
}

void GameManager::_changeEnemyController()
{
    delete enemyController->getModel();
    delete enemyController;
    int random_number = rand() % ENEMY_COUNT;
    switch (EnemyType(random_number))
    {
    case EnemyType::Zombie:
        enemyController = new ZombieController();
        enemyController->setModel(CharacterFactory::createZombie(level));
        enemyController->type = EnemyType::Zombie;
        break;
    case EnemyType::HumanEnemy:
        enemyController = new HumanEnemyController();
        enemyController->setModel(CharacterFactory::createHumanEnemy(level));
        enemyController->type = EnemyType::HumanEnemy;
        break;
    default:
        break;
    }
}

void GameManager::increasePrice(ItemType type, int count)
{
    if (type == ItemType::Food)
    {
        for (int i = 0; i < count; i++)
        {
            FoodPrice += FoodPrice/10;
        }
    }
    else if (type == ItemType::StaminaBooster)
    {
        for (int i = 0; i < count; i++)
        {
            StaminaBoosterPrice += StaminaBoosterPrice/10;
        }
    }
    else if (type == ItemType::Beverage)
    {
        for (int i = 0; i < count; i++)
        {
            BeveragePrice += BeveragePrice/10;
        }
    }
    else if (type == ItemType::KitchenKnife)
    {
        for (int i = 0; i < count; i++)
        {
            KitchenKnifePrice += KitchenKnifePrice/10;
        }
    }
    else if (type == ItemType::Bomb)
    {
        for (int i = 0; i < count; i++)
        {
            BombPrice += BombPrice/10;
        }
    }
    else if (type == ItemType::Molotov)
    {
        for (int i = 0; i < count; i++)
        {
            MolotovPrice += MolotovPrice/10;
        }
    }
    else if (type == ItemType::Bristle)
    {
        for (int i = 0; i < count; i++)
        {
            BristlePrice += BristlePrice/10;
        }
    }
}

Character* EnemyController::getModel()
{
    return this->model;
}

void EnemyController::setModel(Character* model)
{
    this->model = model;
}

State EnemyController::getCurrentState()
{
    return this->currentState;
}

State ZombieController::getNextState()
{
    this->currentState = State::Attack;
    return this->currentState;
}

bool ZombieController::work(Character* character)
{
    Zombie* _model = (Zombie*)getModel();
    if (getCurrentState() == State::Attack)
    {
        if (_model->attack(character, _model->getDamage()))
        {
            return true;
        }
        return false;
    }
    return false;
}

State HumanEnemyController::getNextState()
{
    HumanEnemy* _model = (HumanEnemy*)getModel();
    if (_model->hp->getValue() < _model->defaultHp/2 && _model->haveItem(ItemType::Food))
    {
        currentState = State::LowHP;
        return State::LowHP;
    }
    else if (_model->stamina->getValue() < _model->defaultStamina/2 && _model->haveItem(ItemType::StaminaBooster))
    {
        currentState = State::LowStamina;
        return State::LowStamina;
    }
    else
    {
        currentState = State::Attack;
        return State::Attack;
    }
}

bool HumanEnemyController::work(Character* character)
{
    HumanEnemy* _model = (HumanEnemy*)getModel();
    switch (getCurrentState())
    {
    case State::LowHP:
        for (int i=0; i < _model->items.size(); i++)
        {
            if (_model->items[i]->type == ItemType::Food)
            {
                if (_model->items[i]->count > 0)
                    _model->useItem(i);
            }
        }
        break;
    case State::LowStamina:
        for (int i=0; i < _model->items.size(); i++)
        {
            if (_model->items[i]->type == ItemType::StaminaBooster)
            {
                if (_model->items[i]->count > 0)
                    _model->useItem(i);
            }
        }
        break;
    case State::Attack:
        if (_model->stamina->getValue() > 5)
        {   
            // TODO: levelup skill
            for (int i=0; i < _model->items.size(); i++)
            {
                if (_model->items[i]->fatherType == ItemType::ThrowableItem)
                {
                    if (_model->items[i]->count > 0)
                    {
                        _model->useItem(i);
                        break;
                    }
                }
            }
            _model->setDamage(_model->stamina->getValue() * _model->getDamage() / 50);
            _model->stamina->useStamina(5);
            if (_model->attack(character, _model->getDamage()))
            {
                return true;
            }
        }
        else
        {
            _model->stamina->regenerateStamina(3);
        }
        break;
    default:
        break;
    }
    return false;
}

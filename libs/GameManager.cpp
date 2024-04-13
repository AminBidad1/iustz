#include "GameManager.hpp"

GameManager::GameManager(vector<PlayerController *> players, EnemyController *enemyController, int round_index, int level, PlayerState state)
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
    Character *enemy = enemyController->getModel();
    PlayerController *playerController = players[round_index % players.size()];
    Human *player = playerController->getModel();
    int choice;
    int players_size = players.size();
    bool endGame = false;
    while (true)
    {
        HumanView::showStatus(player);
        CharacterView::showStatus(enemy, enemyController->type);

        // Attack from player
        if (playerController->work(enemy, players)) // Kill enemy
        {
            level++;
            player->getXp()->gainXP(level);
            return;
        }

        // Attack from enemy
        while (enemyController->getNextState() != State::Attack)
        {
            enemyController->work(player, players);
        }

        if (enemyController->work(player, players)) // Kill player
        {
            CharacterView::showAttack(player, enemy);
            CharacterView::showWasKilled(player);
            players_size = players.size();
            playerController->isAlive = false;

            // Check end game
            endGame = true;
            for (int i = 0; i < players.size(); i++)
            {
                if (players[i]->isAlive)
                {
                    endGame = false;
                    break;
                }
            }
            if (endGame)
            {
                cout << "YOU LOST!" << endl;
                exit(0);
            }
        }
        else
        {
            CharacterView::showAttack(enemy, player);
            HumanView::showTakeDamage(player);
        }

        // Restore
        player->setDamage(player->DEFAULT_DAMAGE);
        enemyController->getModel()->setDamage(enemyController->DEFAULT_DAMAGE);

        // Turn round
        while (true)
        {
            round_index++;
            playerController = players[round_index % players.size()];
            if (playerController->isAlive)
            {
                break;
            }
        }
        player = playerController->getModel();
    }
}

void GameManager::goShop()
{
    Human *player = players[round_index % players.size()]->getModel();
    InventoryItem *inventoryItem;
    Item *item;
    ShopSection shopSection;
    while (true)
    {
        HumanView::showStatus(player);
        shopSection = ShopView::buySection();
        if (shopSection == ShopSection::Buy)
        {
            inventoryItem = HumanView::selecetItem();
            item = ItemFactory::createItem(inventoryItem->type, level);
            inventoryItem->item = item;
            if (player->buyItem(inventoryItem, item->getPrice(), 0))
            {
                HumanView::successBuy();
                GameManager::increasePrice(inventoryItem->type, inventoryItem->count);
            }
            else
            {
                HumanView::failedBuy();
            }
        }
        else if (shopSection == ShopSection::Sell)
        {
            int index = ShopView::sellItems(player);
            if (index != -1)
            {
                // Selling price is 10% less than real price
                player->money->setValue(player->money->getValue() + (player->items[index]->item->getPrice()) - (player->items[index]->item->getPrice()) / 10);
                player->removeItem(index, 1);
            }
        }
        else
        {
            break;
        }
        if (!ShopView::stay())
            break;
    }
}

void GameManager::startRound()
{
    PlayerController *playerController = players[round_index % players.size()];
    while (true)
    {
        state = getNextState();
        if (state == PlayerState::Shop)
        {
            for (int i = 0; i < players.size(); i++)
            {
                playerController = players[round_index % players.size()];
                if (playerController->isAlive)
                {
                    goShop();
                }
                round_index++;
            }
            while (true)
            {
                playerController = players[round_index % players.size()];
                if (playerController->isAlive)
                {
                    break;
                }
                round_index++;
            }
            attack();
        }
        else if (state == PlayerState::Attack)
        {
            while (true)
            {
                playerController = players[round_index % players.size()];
                if (playerController->isAlive)
                {
                    break;
                }
                round_index++;
            }
            attack();
        }
        _changeEnemyController();
    }
}

void GameManager::_changeEnemyController()
{
    delete enemyController->getModel();
    delete enemyController;
    int random_number = rand() % ENEMY_COUNT;
    if ((level + 1) % 5 == 0)
    {
        UltraVampireZombie *enemy = CharacterFactory::createUltraVampireZombie(level);
        enemyController = new UltraVampireZombieController();
        enemyController->setModel(enemy);
        enemyController->type = EnemyType::Zombie;
        enemyController->DEFAULT_DAMAGE = enemy->getDamage();
    }
    else
    {
        if (EnemyType(random_number) == EnemyType::Zombie)
        {
            Zombie *enemy = CharacterFactory::createZombie(level);
            enemyController = new ZombieController();
            enemyController->setModel(enemy);
            enemyController->type = EnemyType::Zombie;
            enemyController->DEFAULT_DAMAGE = enemy->getDamage();
        }
        else if (EnemyType(random_number) == EnemyType::HumanEnemy)
        {
            HumanEnemy *enemy = CharacterFactory::createHumanEnemy(level);
            enemyController = new HumanEnemyController();
            enemyController->setModel(enemy);
            enemyController->type = EnemyType::HumanEnemy;
            enemyController->DEFAULT_DAMAGE = enemy->getDamage();
        }
        else if (EnemyType(random_number) == EnemyType::VampireZombie)
        {
            VampireZombie *enemy = CharacterFactory::createVampireZombie(level);
            enemyController = new VampireZombieController();
            enemyController->setModel(enemy);
            enemyController->type = EnemyType::VampireZombie;
            enemyController->DEFAULT_DAMAGE = enemy->getDamage();
        }
        else if (EnemyType(random_number) == EnemyType::UltraZombie)
        {
            UltraZombie *enemy = CharacterFactory::createUltraZombie(level);
            enemyController = new UltraZombieController();
            enemyController->setModel(enemy);
            enemyController->type = EnemyType::UltraZombie;
            enemyController->DEFAULT_DAMAGE = enemy->getDamage();
        }
    }
}

void GameManager::increasePrice(ItemType type, int count)
{
    if (type == ItemType::Food)
    {
        for (int i = 0; i < count; i++)
        {
            Store::FoodPrice += Store::FoodPrice / 10;
        }
    }
    else if (type == ItemType::StaminaBooster)
    {
        for (int i = 0; i < count; i++)
        {
            Store::StaminaBoosterPrice += Store::StaminaBoosterPrice / 10;
        }
    }
    else if (type == ItemType::Beverage)
    {
        for (int i = 0; i < count; i++)
        {
            Store::BeveragePrice += Store::BeveragePrice / 10;
        }
    }
    else if (type == ItemType::KitchenKnife)
    {
        for (int i = 0; i < count; i++)
        {
            Store::KitchenKnifePrice += Store::KitchenKnifePrice / 10;
        }
    }
    else if (type == ItemType::Bomb)
    {
        for (int i = 0; i < count; i++)
        {
            Store::BombPrice += Store::BombPrice / 10;
        }
    }
    else if (type == ItemType::Molotov)
    {
        for (int i = 0; i < count; i++)
        {
            Store::MolotovPrice += Store::MolotovPrice / 10;
        }
    }
    else if (type == ItemType::Bristle)
    {
        for (int i = 0; i < count; i++)
        {
            Store::BristlePrice += Store::BristlePrice / 10;
        }
    }
    else if (type == ItemType::Colt)
    {
        for (int i = 0; i < count; i++)
        {
            Store::ColtPrice += Store::ColtPrice / 10;
        }
    }
    else if (type == ItemType::Kelash)
    {
        for (int i = 0; i < count; i++)
        {
            Store::KelashPrice += Store::KelashPrice / 10;
        }
    }
    else if (type == ItemType::FlatLine)
    {
        for (int i = 0; i < count; i++)
        {
            Store::FlatLinePrice += Store::FlatLinePrice / 10;
        }
    }
    else if (type == ItemType::Sword)
    {
        for (int i = 0; i < count; i++)
        {
            Store::SwordPrice += Store::SwordPrice / 10;
        }
    }
    else if (type == ItemType::Stick)
    {
        for (int i = 0; i < count; i++)
        {
            Store::StickPrice += Store::StickPrice / 10;
        }
    }
    else if (type == ItemType::Knuckles)
    {
        for (int i = 0; i < count; i++)
        {
            Store::KnucklesPrice += Store::KnucklesPrice / 10;
        }
    }
}

int GameManager::getRoundIndex() { return round_index; }

void GameManager::setRoundIndex(int round_index) { this->round_index = round_index; }

int GameManager::getLevel() { return level; }

void GameManager::setLevel(int level) { this->level = level; }

PlayerState GameManager::getState() { return state; }

void GameManager::setState(PlayerState playerstate) { state = playerstate; }

void GameManager::saveGame(const string &filename)
{
    ofstream file(filename);
    if (file.is_open())
    {
        int PlayerController_size = players.size();
        file << getRoundIndex() << "\n";
        file << getLevel() << "\n";
        file << static_cast<int>(getState()) << "\n";
        file << PlayerController_size << "\n";
        for (int i = 0; i < PlayerController_size; i++)
        {
            file << players[i]->isAlive << "\n";
            file << static_cast<int>(players[i]->type);
            file << players[i]->getModel()->getXp()->getValue() << "\n";
            file << players[i]->getModel()->stamina->MAX_VALUE << "\n";
            file << players[i]->getModel()->stamina->MIN_VALUE << "\n";
            file << players[i]->getModel()->stamina->getValue() << "\n";
            file << players[i]->getModel()->get_name() << "\n";
            file << players[i]->getModel()->getAge() << "\n";
            file << players[i]->getModel()->getGender() << "\n";
            file << players[i]->getModel()->getDamage() << "\n";
            file << players[i]->getModel()->hp->MAX_VALUE << "\n";
            file << players[i]->getModel()->hp->MIN_VALUE << "\n";
            file << players[i]->getModel()->hp->getValue() << "\n";
            file << players[i]->getModel()->money->getValue() << "\n";
            int inventory_size = players[i]->getModel()->items.size();
            file << inventory_size << "\n";
            for (int j = 0; j < inventory_size; j++)
            {
                file << players[i]->getModel()->items[j]->item->getName() << "\n";
                file << players[i]->getModel()->items[j]->item->getPrice() << "\n";
                file << players[i]->getModel()->items[j]->item->getSize() << "\n";
                file << static_cast<int>(players[i]->getModel()->items[j]->type) << "\n";
                file << static_cast<int>(players[i]->getModel()->items[j]->fatherType) << "\n";
                file << players[i]->getModel()->items[j]->count << "\n";
                file << players[i]->getModel()->skills[j]->getLevel() << "\n";
            }
        }
        // enemyController
        file << static_cast<int>(enemyController->getCurrentState()) << "\n";
        file << enemyController->DEFAULT_DAMAGE << "\n";
        file << static_cast<int>(enemyController->type) << "\n";
        file << enemyController->getModel()->get_name() << "\n";
        file << enemyController->getModel()->getAge() << "\n";
        file << enemyController->getModel()->getGender() << "\n";
        file << enemyController->getModel()->getDamage() << "\n";
        file << enemyController->getModel()->hp->MAX_VALUE << "\n";
        file << enemyController->getModel()->hp->MIN_VALUE << "\n";
        file << enemyController->getModel()->hp->getValue() << "\n";
        file << enemyController->getModel()->money->getValue() << "\n";
        file.close();
    }
    else
    {
        cerr << "Error opening " << filename << " for writing." << endl;
    }
}

void GameManager::loadGame(const string &filename)
{
    ifstream file(filename);
    if (file.is_open())
    {
        // Clear existing data
        players.clear();

        int roundIndex, _level, playerControllerSize;
        int stateInt;
        PlayerState state;
        State currentState;

        // Read round index, level, and player state
        file >> roundIndex >> _level >> stateInt >> playerControllerSize;

        // Convert integer value to enum for player state
        state = PlayerState(stateInt);
        setState(state);
        setRoundIndex(roundIndex);
        setLevel(_level);
        // Load player controllers
        for (int i = 0; i < playerControllerSize; i++)
        {
            bool isAlive;
            int typeInt;
            PlayerType type;

            file >> isAlive >> typeInt;

            // Convert integer value to enum for player type
            type = PlayerType(typeInt);

            // Depending on the type, create the appropriate player
            Human *model;
            if (type == PlayerType::Human)
                model = new Human();
            else if (type == PlayerType::Attacker)
                model = new Attacker();
            else if (type == PlayerType::Healer)
                model = new Healer();
            else if (type == PlayerType::Tank)
                model = new Tank();

            // Read and set player data
            int XPValue, StaminaValue;
            file >> XPValue >> model->stamina->MAX_VALUE >> model->stamina->MIN_VALUE >> StaminaValue;
            model->getXp()->setValue(XPValue);
            model->stamina->setValue(StaminaValue);
            string name, gender;
            int age;
            double damage;
            file >> name >> age >> gender >> damage;
            model->set_name(name);
            model->setAge(age);
            model->setGender(gender);
            model->setDamage(damage);
            int HPValue, MoneyValue;
            file >> model->hp->MAX_VALUE >> model->hp->MIN_VALUE >> HPValue >> MoneyValue;
            model->hp->setValue(HPValue);
            model->money->setValue(MoneyValue);
            // Read and add inventory items
            int inventorySize;
            file >> inventorySize;
            for (int j = 0; j < inventorySize; j++)
            {
                string itemName;
                int itemPrice, typeInt, fatherTypeInt, _count, _level, _size;
                ItemType itemType, fatherType;

                file >> itemName >> itemPrice >> _size >> typeInt >> fatherTypeInt >> _count >> _level;

                // Convert integer values to enums for item types
                itemType = ItemType(typeInt);
                fatherType = ItemType(fatherTypeInt);

                // Create and add inventory item
                InventoryItem *item = new InventoryItem();
                Skill *skill;
                skill->setLevel(_level);
                item->item = ItemFactory::createItem(itemType, level);
                item->item->setPrice(itemPrice);
                item->item->setSize(_size);
                item->type = itemType;
                item->fatherType = fatherType;
                item->count = _count;
                model->items.push_back(item);
                model->addSkill(skill);
            }

            // Create player controller and add to players vector
            PlayerController *playerController;
            if (type == PlayerType::Human)
                playerController = new HumanController();
            else if (type == PlayerType::Attacker)
                playerController = new AttackerController();
            else if (type == PlayerType::Healer)
                playerController = new HealerController();
            else if (type == PlayerType::Tank)
                playerController = new TankController();
            // Add cases for other player types if needed

            playerController->setModel(model);
            playerController->isAlive = isAlive;
            playerController->type = type;

            players.push_back(playerController);
        }

        // Load enemy controller
        int currentStateInt;
        file >> currentStateInt;
        currentState = static_cast<State>(currentStateInt);
        enemyController->setCurrentState(currentState);

        file >> enemyController->DEFAULT_DAMAGE;
        int typeInt;
        file >> typeInt;
        enemyController->type = static_cast<EnemyType>(typeInt);

        // Read and set enemy data
        string name, gender;
        int age;
        double damage;
        file >> name >> age >> gender >> damage;
        enemyController->getModel()->set_name(name);
        enemyController->getModel()->setAge(age);
        enemyController->getModel()->setGender(gender);
        enemyController->getModel()->setDamage(damage);
        int EnemyHpValue, EnemyMoneyValue;
        file >> enemyController->getModel()->hp->MAX_VALUE >> enemyController->getModel()->hp->MIN_VALUE >> EnemyHpValue >> EnemyMoneyValue;
        enemyController->getModel()->hp->setValue(EnemyHpValue);
        enemyController->getModel()->money->setValue(EnemyMoneyValue);

        file.close();
    }
    else
    {
        cerr << "Error opening " << filename << " for reading." << endl;
    }
}
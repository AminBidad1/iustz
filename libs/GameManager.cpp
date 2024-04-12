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
    while (true)
    {
        HumanView::showStatus(player);
        if (ShopView::buySection())
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
                // TODO: increase price with count
                player->money->setValue(player->money->getValue() + (player->items[index]->item->getPrice()) - (player->items[index]->item->getPrice()) / 10);
                player->removeItem(index, 1);
            }
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
            FoodPrice += FoodPrice / 10;
        }
    }
    else if (type == ItemType::StaminaBooster)
    {
        for (int i = 0; i < count; i++)
        {
            StaminaBoosterPrice += StaminaBoosterPrice / 10;
        }
    }
    else if (type == ItemType::Beverage)
    {
        for (int i = 0; i < count; i++)
        {
            BeveragePrice += BeveragePrice / 10;
        }
    }
    else if (type == ItemType::KitchenKnife)
    {
        for (int i = 0; i < count; i++)
        {
            KitchenKnifePrice += KitchenKnifePrice / 10;
        }
    }
    else if (type == ItemType::Bomb)
    {
        for (int i = 0; i < count; i++)
        {
            BombPrice += BombPrice / 10;
        }
    }
    else if (type == ItemType::Molotov)
    {
        for (int i = 0; i < count; i++)
        {
            MolotovPrice += MolotovPrice / 10;
        }
    }
    else if (type == ItemType::Bristle)
    {
        for (int i = 0; i < count; i++)
        {
            BristlePrice += BristlePrice / 10;
        }
    }
}

int GameManager::getRoundIndex() { return round_index; }

int GameManager::getLevel() { return level; }

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
            file << static_cast<int>(players[i]->type) << "\n";
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
            for (int i = 0; i < inventory_size; i++)
            {
                file << players[i]->getModel()->items[i]->item->getName() << "\n";
                file << players[i]->getModel()->items[i]->item->getPrice() << "\n";
                file << static_cast<int>(players[i]->getModel()->items[i]->type) << "\n";
                file << static_cast<int>(players[i]->getModel()->items[i]->fatherType) << "\n";
                file << players[i]->getModel()->items[i]->count << "\n";
                file << players[i]->getModel()->skills[i]->getLevel() << "\n";
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

        int roundIndex, level, playerControllerSize;
        int stateInt;
        PlayerState state;
        int currentStateInt;
        State currentState;

        // Read round index, level, and player state
        file >> roundIndex >> level >> stateInt >> playerControllerSize;

        // Convert integer value to enum for player state
        state = static_cast<PlayerState>(stateInt);
        setState(state);

        // Load player controllers
        for (int i = 0; i < playerControllerSize; i++)
        {
            bool isAlive;
            int typeInt;
            PlayerType type;

            file >> isAlive >> typeInt;

            // Convert integer value to enum for player type
            type = static_cast<PlayerType>(typeInt);

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
            file >> model->DEFAULT_DAMAGE >> model->DEFAULT_HP;
            file >> model->getXp()->getValue() >> model->stamina->MAX_VALUE >> model->stamina->MIN_VALUE >> model->stamina->getValue();
            string name, gender;
            int age;
            double damage;
            file >> name >> age >> gender >> damage;
            model->set_name(name);
            model->setAge(age);
            model->setGender(gender);
            model->setDamage(damage);
            file >> model->hp->MAX_VALUE >> model->hp->MIN_VALUE >> model->hp->getValue() >> model->money->getValue();

            // Read and add inventory items
            int inventorySize;
            file >> inventorySize;
            for (int j = 0; j < inventorySize; j++)
            {
                string itemName;
                int itemPrice, typeInt, fatherTypeInt, count, level;
                ItemType itemType, fatherType;

                file >> itemName >> itemPrice >> typeInt >> fatherTypeInt >> count >> level;

                // Convert integer values to enums for item types
                itemType = static_cast<ItemType>(typeInt);
                fatherType = static_cast<ItemType>(fatherTypeInt);

                // Create and add inventory item
                InventoryItem *item = new InventoryItem();
                item->item = new Item(itemName, itemPrice);
                item->type = itemType;
                item->fatherType = fatherType;
                item->count = count;
                model->items.push_back(item);
            }

            // Create player controller and add to players vector
            PlayerController *playerController;
            if (type == PlayerType::Human)
                playerController = new HumanController();
            else if (type == PlayerType::Attacker)
                playerController = new AttackerController();
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
        enemyController->currentState = currentState;

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

        file >> enemyController->getModel()->DEFAULT_DAMAGE >> enemyController->getModel()->DEFAULT_HP;
        file >> enemyController->getModel()->hp->MAX_VALUE >> enemyController->getModel()->hp->MIN_VALUE >> enemyController->getModel()->hp->getValue() >> enemyController->getModel()->money->getValue();

        file.close();
    }
    else
    {
        cerr << "Error opening " << filename << " for reading." << endl;
    }
}
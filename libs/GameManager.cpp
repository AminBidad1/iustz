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
            file << players[i]->getModel()->DEFAULT_DAMAGE << "\n";
            file << players[i]->getModel()->DEFAULT_HP << "\n";
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
        file << enemyController->getModel()->DEFAULT_DAMAGE << "\n";
        file << enemyController->getModel()->DEFAULT_HP << "\n";
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
        int L_round_index, L_level, L_player_state, L_player_controller_vector_size;
        string line;
        getline(file, line);
        L_round_index = stoi(line);
        getline(file, line);
        L_level = stoi(line);
        getline(file, line);
        L_player_state = stoi(line);
        getline(file, line);
        L_player_controller_vector_size = stoi(line);
        for (int i = 0; i < L_player_controller_vector_size; i++)
        {
        }

        vector<int>
            Is_Alive, player_type, default_damage, default_hp, xp, stamina_max_value, stamina_min_value, stamina, age, damage, hp_max_value, hp_min_value, hp, money;
        file.close();
    }
    else
    {
        cerr << "Error opening " << filename << " for reading." << endl;
    }
}
#include "GameManager.hpp"

int CharacterController::player_index = 1;

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

Character* CharacterController::createCharacter(CharacterType type)
{
    Character* character;
    if (type == CharacterType::Human)
    {
        vector<InventoryItem*> items;
        vector<Skill*> skills;
        string name = "Player" + to_string(player_index);
        Human* human = new Human(
            name, 18, "man", (HP*)ValueController::createValue(ValueType::HP),
            (Money*)ValueController::createValue(ValueType::Money), 
            (Stamina*)ValueController::createValue(ValueType::Stamina),
            (XP*)ValueController::createValue(ValueType::XP), skills, items, DEFAULT_DAMAGE
        );
        player_index++;
        character = human;
    }
    return character;
}

Human* CharacterController::createCustomHuman(string name, int age, string gender,
                                              vector<Skill*> skills, Money* money, double damage)
{
    vector<InventoryItem*> items;
    Human* human = new Human(
        name, age, gender, 
        (HP*)ValueController::createValue(ValueType::HP), money, 
        (Stamina*)ValueController::createValue(ValueType::Stamina),
        (XP*)ValueController::createValue(ValueType::XP), skills, items, damage
    );
    return human;
}

Zombie* CharacterController::createZombie(int level)
{
    double damage = pow(1.2, level) * DEFAULT_DAMAGE;
    string name = "zombie" + to_string(level+1);
    Zombie* zombie = new Zombie(
        name, 150, "man", 
        (HP*)ValueController::createCustomValue(ValueType::HP, (level + 1) * 50),
        (Money*)ValueController::createCustomValue(ValueType::Money, level*50),
        damage
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
    Human* player = players[round_index % players.size()];
    int choice;
    int selected_index = -1;
    while (true)
    {
        HumanView::showStatus(player);
        ZombieView::showStatus(zombie);
        // Check stamina
        if (player->stamina->getValue() <= 5) 
        {
            HumanView::showLowStamina(player->get_name());
            player->stamina->regenerateStamina(3);
        }
        else
        {
            // Use item from inventory
            while (true)
            {
                choice = HumanView::selectInventoryItem(player->items);
                if (choice == player->items.size())
                {
                    break;
                }
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
            }
            // Attack from player
            if (player->attack(zombie, player->getDamage())) // kill zombie
            {
                HumanView::showAttack(player, zombie);
                ZombieView::showWasKilled(zombie);
                HumanView::congratulations(zombie->get_name());
                level++;
                player->getXp()->gainXP(level);
                player->money->append(zombie->money->getValue());
                // Levelup Skill
                if (selected_index != -1)
                {
                    player->skills[selected_index]->levelup(1);
                    HumanView::levelupSkill(player->items[selected_index]);
                }
                else
                {
                    cout << selected_index << endl;
                }
                return;
            }
            else
            {
                HumanView::showAttack(player, zombie);
                ZombieView::showTakeDamage(zombie);
                player->stamina->useStamina(5);
            }
        }
        // Attack from zombie
        if (zombie->attack(player, zombie->getDamage())) // kill player
        {
            ZombieView::showAttack(player, zombie);
            CharacterView::showWasKilled(player);
            players.erase(players.begin() + ((round_index - 1) % players.size()));
            if (players.size() == 0)
            {
                cout << "YOU LOST!" << endl;
                exit(0);
            }
            player = players[round_index % players.size()];
        }
        else 
        {
            ZombieView::showAttack(player , zombie);
            HumanView::showTakeDamage(player);
        }

        // Restore
        player->setDamage(CharacterController::DEFAULT_DAMAGE);
        selected_index = -1;

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
            item = ItemController::createItem(inventoryItem->type);
            inventoryItem->item = item;
            // TODO: Handle price
            if (player->buyItem(inventoryItem, item->getPrice()))
            {
                HumanView::successBuy();
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
                //selling price is 10% less than real price
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
        delete enemy;
        enemy = CharacterController::createZombie(level);
    }
}

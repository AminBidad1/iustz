#include "views.hpp"


#if defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
/* reads from keypress, doesn't echo */
int getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr(STDIN_FILENO, &oldattr);
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
    return ch;
}
#endif

int itemSizeMap(ItemType type)
{
    Item* item;
    int size;
    item = ItemFactory::createItem(type, 0);
    size = item->getSize();
    delete item;
    return size;
}


void CharacterView::showAttack(Character* character , Character* enemy)
{
    cout << character->get_name() << " : I damaged to " << enemy->get_name() << endl;
}

void CharacterView::showTakeDamage(Character* character)
{
    cout << character->get_name() << " : AAKH! This hurts me" << endl;
}

void CharacterView::showWasKilled(Character* character)
{
    cout << character->get_name() << " Was Killed" << endl;
}

void CharacterView::showStatus(Character* character, EnemyType type)
{
    cout << character->get_name() << " ::  " << character->hp->getValue() << "hp  " 
    << character->getDamage() << "dg" << endl;
    if (type == EnemyType::HumanEnemy)
    {
        HumanEnemy* human = (HumanEnemy*)character;
        cout << "Enemy Inventory :  ";
        for (int i=0; i < human->items.size(); i++)
        {
            cout << human->items[i]->count << " * " << human->items[i]->item->getName() << ",  ";
        }
        cout << endl;
    }
}

void HumanView::showUseItem(Item* item)
{
    cout << "You successfully used " << item->getName() << " item" << endl;
}

void HumanView::failedUseItem(Item* item)
{
    cout << "You can't use " << item->getName() << ". because you don't have it" << endl;
}

void HumanView::showAppendHP(int value , Human* human)
{
    cout << human->get_name() << " : YOOHO! I got " << value << " HP" << endl;
}

void HumanView::showAppendStamina(int value , Human* human)
{
    cout << human->get_name() << " : Eyval! I got " << value << " Stamina" << endl;
}

void HumanView::showStatus(Human* human)
{
    cout << human->get_name() << " : " << endl;
    cout << "    Your HP: " << human->hp->getValue() << endl
    << "    Your Stamina: " << human->stamina->getValue() << endl
    << "    Your Money: " << human->money->getValue() << endl
    << "    Your XP: " << human->getXp()->getValue() << endl;
}

InventoryItem* HumanView::selecetItem()
{
    cout << "Items: " << endl;
    for (int i = MIN_ITEM_INDEX; i <= MAX_ITEM_INDEX; i++)
    {
        cout << "    " << i - MIN_ITEM_INDEX + 1 << ". " <<
        itemTypeMap(ItemType(i)) << " :: " << itemPriceMap(ItemType(i)) 
        << " :: " << itemSizeMap(ItemType(i)) <<  endl;
    }
    cout << "Please choose a item: ";
    int choice;
    cin >> choice;
    int count;
    cout << "How many? ";
    cin >> count;
    InventoryItem* inventoryItem = new InventoryItem();
    inventoryItem->count = count;
    int index = choice + MIN_ITEM_INDEX - 1;
    inventoryItem->type = ItemType(index);
    if (MIN_THROWABLE_ITEM_INDEX <= index && index <= MAX_THROWABLE_ITEM_INDEX)
    {
        inventoryItem->fatherType = ItemType::ThrowableItem;
    }
    else if (MIN_CONSUMABLE_ITEM_INDEX <= index && index <= MAX_CONSUMABLE_ITEM_INDEX)
    {
        inventoryItem->fatherType = ItemType::ConsumableItem;
    }
    else if (MIN_PASSIVE_ITEM_INDEX <= index && index <= MAX_PASSIVE_ITEM_INDEX)
    {
        inventoryItem->fatherType = ItemType::PassiveItem;
    }

    return inventoryItem;
}

void HumanView::successBuy()
{
    cout << "Successful transaction. The item added to inventory" << endl;
}

void HumanView::failedBuy()
{
    cout << "Unsuccessful transaction. You can't buy this item." << endl;
}

void HumanView::showInventory(vector<InventoryItem*> items)
{
    cout << "Inventory items: " << endl;
    for (int i=0; i < items.size(); i++)
    {
        if (items[i]->count > 0)
            cout << i + 1 << " - " << items[i]->item->getName()  << " : " << items[i]->count << endl;
    }
    cout << items.size() + 1 << " - " << "leave" << endl;
}

int HumanView::selectInventoryItem(vector<InventoryItem*> items)
{
    cout << "Please Choose a item to use or select last option to leave" << endl;
    showInventory(items);
    int input;
    cout << "Your Choice: ";
    cin >> input;
    input--;
    return input;
}

void HumanView::showLowStamina(string name)
{
    cout << name << "! Your Stamina is very low and you can't damage to your enemy" << endl;
}

void HumanView::congratulations(string enemy_name)
{
    cout << "Congratulations! you Kill " << enemy_name << ". A stronger enemy is coming" << endl;
}

void HumanView::levelupSkill(InventoryItem* inventoryItem)
{
    AttackingItem* item = (AttackingItem*)inventoryItem->item;
    cout << "Your  " << item->getName() << " skill has improved. " <<
    "miss percent of " << item->getName() << " : " << item->getMiss_percent() << endl;
}

void ZombieView::showAttack(Character* character , Zombie* zombie)
{
    cout << zombie->get_name() << " : HaHa! I damaged to you! you can't beat me " <<
    character->get_name() << "!" << endl;
}

void ZombieView::showStatus(Zombie* zombie)
{
    cout << zombie->get_name() << " ::  " << zombie->hp->getValue() << "hp  " 
    << zombie->getDamage() << "dg" << endl;
}

bool ShopView::stay()
{
    cout << "if you want to stay in shop please press Enter. else press Escape" << endl;
    getch();
    int input = getch();
    if (input == ESCAPE_KEY)
        return false;
    else if (input == ENTER_KEY)
        return true;
    return false;
}

bool ShopView::buySection()
{
    while(true)
    {
        cout << "Shop sections:" << endl
         << "1. Buy new items" << endl
         << "2. Sell your stuff" << endl
         << "Choose a section: ";
        int input;
        cin >> input;
        if (input == 1) return true;
        if (input == 2) return false;
        cout << endl << "Enter a valid input!" << endl;
    }
}

int ShopView::sellItems(Human* player)
{
    int input;
    while (true)
    {
        HumanView::showInventory(player->items);
        cout << "Choose items to sell or enter (" << player->items.size()+1 << ") to leave: ";
        cin >> input;
        if (input > 0 && input <= player->items.size()+1)
        {
            break;
        }
        cout << endl << "Enter a valid input!" << endl;
    }
    input--;
    if (input == player->items.size()) return -1;
    else
    {
        return input;
    }
}
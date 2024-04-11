#include "views.hpp"
void gotoxy(int x, int y)
{
    cout << "\033[" << y << ";" << x << "H";
}
void ClearTerminal()
{
    for (int j = 20; j < 50; j++)
    {
        gotoxy(0, j);
        cout << operator_space(" ", 87);
    }

    gotoxy(0, 20);
}

string operator_space(string str, int count)
{
    string result = "";
    for (int i = 0; i < count; i++)
    {
        result += str;
    }
    return result;
}

void ClearEnemyStatus()
{
    gotoxy(88, 2);
    cout << operator_space(" ", 28);
    for (int i = 4; i < 9; i++)
    {
        gotoxy(71, i);
        cout << operator_space(" ", 49);
    }
    for (int i = 10; i <= 17; i++)
    {
        gotoxy(71, i);
        cout << operator_space(" ", 49);
    }
}
void TableSection()
{
    gotoxy(2, 7);
    cout << "XP";
    gotoxy(2, 8);
    cout << "Att Dmg";
    gotoxy(2, 5);
    cout << "Stamina";
    gotoxy(2, 6);
    cout << "Money";
    gotoxy(2, 4);
    cout << "HP";
    gotoxy(2, 10);
    cout << "List of";
    gotoxy(2, 11);
    cout << "items";
    gotoxy(18, 6);
    cout << '-';
    gotoxy(18, 7);
    cout << '-';
    gotoxy(18, 8);
    cout << '-';
    for (int i = 0; i < 140; i++)
    {
        gotoxy(i, 0);
        cout << "-";
        gotoxy(i, 9);
        cout << "-";
    }
    for (int i = 2; i < 19; i++)
    {
        gotoxy(70, i);
        cout << "|";
        gotoxy(0, i);
        cout << "|";
        gotoxy(140, i);
        cout << "|";
    }
    for (int i = 0; i < 140; i++)
    {
        gotoxy(i, 18);
        cout << "-";
        gotoxy(i, 3);
        cout << "-";
    }
    gotoxy(0, 3);
    cout << "|";
    gotoxy(70, 3);
    cout << "|";
    gotoxy(140, 3);
    cout << "|";
    for (int i = 4; i < 18; i++)
    {
        gotoxy(10, i);
        cout << "|";
    }
}
void ShowValueCharacter(int value, int row, int column, bool flag_1, int defaultValue)
{
    //default-value
    //compare=10      value /compare 
    bool flag_2 = false;
    if (value < 10)
    {
        gotoxy(row, column);
        cout << operator_space(" ", 25);
        gotoxy(row, column);
        cout << "[!.........]";
        flag_2 = true;
    }
    if (!flag_2)
    {
        int compare = value / 10;
        gotoxy(row, column);
        cout << operator_space(" ", 25);
        gotoxy(row, column);
        cout << "[";
        for (int i = 0; i <= compare; i++)
        {
            gotoxy(row + 1 + i, column);
            cout << "#";
        }
        int counter = 0;
        for (int i = 0; i < 10 - compare; i++)
        {
            counter++;
            gotoxy(row + 1 + compare + i, column);
            cout << ".";
        }
        gotoxy(row + 2 + compare + counter, column);
        cout << "]";
        if (flag_1)
        {
            gotoxy((row * 2) + 1, column);
            cout << operator_space(" ", 23);
            gotoxy((row * 2) + 1, column);
            cout << operator_space(" ", 13) << value << " %";
        }
    }
    if (!flag_1)
    {
        gotoxy(78, 6);
        cout << '-';
        gotoxy(78, 7);
        cout << '-';
        gotoxy(78, 8);
        cout << '-';
        gotoxy(96, 6);
        cout << '-';
        gotoxy(96, 7);
        cout << '-';
    }
}
void ClearPlayerItems()
{
    for (int i = 10; i < 18; i++)
    {
        gotoxy(12, i);
        cout << operator_space(" ", 57);
    }
}
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

void CharacterView::showAttack(Character *character, Character *enemy)
{
    // cout << character->get_name() << " : I damaged to " << enemy->get_name() << endl;
}

void CharacterView::showTakeDamage(Character *character)
{
    // cout << character->get_name() << " : AAKH! This hurts me" << endl;
}

void CharacterView::showWasKilled(Character *character)
{
    ClearEnemyStatus();
    // cout << character->get_name() << " Was Killed" << endl;
}

void CharacterView::showStatus(Character *character, EnemyType type)
{
    gotoxy(88, 2);
    cout << "Enemy :" << character->get_name();
    gotoxy(96, 4);
    cout << operator_space(" ", 11);
    ShowValueCharacter(character->hp->getValue(), 72, 4, false, character->DEFAULT_HP);
    gotoxy(96, 4);
    cout << character->hp->getValue();
    gotoxy(96, 5);
    cout << operator_space(" ", 12);
    gotoxy(96, 8);
    cout << character->getDamage();
    if (type == EnemyType::HumanEnemy)
    {
        HumanEnemy *human = (HumanEnemy *)character;
        gotoxy(96, 5);
        cout << human->stamina->getValue();
        bool flag = false;
        static int increase = 0;
        ShowValueCharacter(human->stamina->getValue(), 72, 5, false, human->defaultStamina);
        string str = "";
        for (int i = 0; i < human->items.size(); i++)
        {
            str += to_string(human->items[i]->count) + " * " + human->items[i]->item->getName() + ",";
            for (int j = 0; j < str.size(); j++)
            {
                if (j < 48)
                {
                    gotoxy(72 + j, 10 + increase);
                    cout << str[j];
                }
                else
                {
                    str.erase(0, 47);
                    increase++;
                }
                if (i == human->items.size() - 1)
                {
                    gotoxy(72 + j, 10 + increase);
                    cout << str[j];
                }
            }
        }
        increase = 0;
        cout << endl;
    }
    else
    {
        gotoxy(96, 13);
        cout << "-";
    }
}

void HumanView::showUseItem(Item *item)
{
    // cout << "You successfully used " << item->getName() << " item" << endl;
}

void HumanView::failedUseItem(Item *item)
{
    // cout << "You can't use " << item->getName() << ". because you don't have it" << endl;
}

void HumanView::showAppendHP(int value, Human *human)
{
    // cout << human->get_name() << " : YOOHO! I got " << value << " HP" << endl;
}

void HumanView::showAppendStamina(int value, Human *human)
{
    // cout << human->get_name() << " : Eyval! I got " << value << " Stamina" << endl;
}

void HumanView::showStatus(Human *human)
{
    HumanView::showInventory(human->items);
    // gotoxy(12,10);
    // cout<<"h";
    // gotoxy(68,10);
    // cout<<"h";
    gotoxy(32, 2);
    cout << operator_space(" ", 20);
    gotoxy(32, 2);
    cout << human->get_name() << " : ";
    ShowValueCharacter(human->hp->getValue(), 12, 4, true, human->DEFAULT_HP);
    ShowValueCharacter(human->stamina->getValue(), 12, 5, true, 100);
    gotoxy(38, 6);
    cout << operator_space(" ", 11);
    gotoxy(38, 6);
    cout << human->money->getValue();
    gotoxy(38, 7);
    cout << operator_space(" ", 11);
    gotoxy(38, 7);
    cout << human->getXp()->getValue();
    gotoxy(38, 8);
    cout << human->getDamage();
    gotoxy(0, 20);
}

InventoryItem *HumanView::selecetItem()
{
    ClearTerminal();
    cout << "Items: " << endl;
    for (int i = MIN_ITEM_INDEX; i <= MAX_ITEM_INDEX; i++)
    {
        cout << operator_space(" ", 5) << i - MIN_ITEM_INDEX + 1 << ". " << itemTypeMap(ItemType(i)) << endl;
    }
    cout << "Please choose a item: ";
    int choice;
    cin >> choice;
    int count;
    cout << "How many? ";
    cin >> count;
    InventoryItem *inventoryItem = new InventoryItem();
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

    return inventoryItem;
}

void HumanView::successBuy()
{
    ClearTerminal();
    cout << "Successful transaction. The item added to inventory" << endl;
}

void HumanView::failedBuy()
{
    ClearTerminal();
    cout << "Unsuccessful transaction. You can't buy this item." << endl;
}

void HumanView::showInventory(vector<InventoryItem *> items)
{
    ClearPlayerItems();
    ClearTerminal();
    // cout << "Inventory items: " << endl;
    string str = "";
    int counter = 0;
    int increase = 0;
    for (int i = 0; i < items.size(); i++)
    {
        if (items[i]->count > 0)
            str += to_string(i + 1) + " - " + items[i]->item->getName() + " : " + to_string(items[i]->count) + ", ";
        for (int j = 0; j < str.size(); j++)
        {
            if (j <= 56)
            {
                gotoxy(12 + j, 10 + increase);
                cout << str[j];
            }
            if (str.size() != 0 && i != 0 && i == items.size() - 1 && j > 56)
            {
                gotoxy(12 + counter, 11 + increase);
                cout << str[j];
                counter++;
            }
            if (j > 56)
            {
                str.erase(0, 56);
                increase++;
            }
        }
    }
    increase = 0;
    gotoxy(0, 20);
    cout << items.size() + 1 << " - "
         << "Punch" << endl;
}

int HumanView::selectInventoryItem(vector<InventoryItem *> items)
{
    ClearTerminal();
    cout << "Please Choose a item to use or select last option to leave" << endl;
    showInventory(items);
    int input;
    // cout << "Your Choice: ";
    cin >> input;
    input--;
    ClearTerminal();
    return input;
}

void HumanView::showLowStamina(string name)
{
    gotoxy(0,23);
    cout << name << "! Your Stamina is very low and you can't damage to your enemy" << endl;
}

void HumanView::congratulations(string enemy_name)
{
    // cout << "Congratulations! you Kill " << enemy_name << ". A stronger enemy is coming" << endl;
}

void HumanView::levelupSkill(InventoryItem *inventoryItem)
{
    AttackingItem *item = (AttackingItem *)inventoryItem->item;
    // cout << "Your  " << item->getName() << " skill has improved. "
    //  << "miss percent of " << item->getName() << " : " << item->getMiss_percent() << endl;
}

void ZombieView::showAttack(Character *character, Zombie *zombie)
{
    // cout << zombie->get_name() << " : HaHa! I damaged to you! you can't beat me " << character->get_name() << "!" << endl;
}

void ZombieView::showStatus(Zombie *zombie)
{
    gotoxy(45, 2);
    cout << zombie->get_name() << " ::  ";
    gotoxy(45, 3);
    cout << zombie->hp->getValue() << "hp  ";
    gotoxy(45, 4);
    cout << zombie->getDamage() << "dg";
    // cout << zombie->get_name() << " ::  " << zombie->hp->getValue() << "hp  "
    //      << zombie->getDamage() << "dg" << endl;
}

bool ShopView::stay()
{
    cout << "if you want to stay in shop please press Enter. else press Escape" << endl;
    getch();
    int input = getch();
    if (input == ESCAPE_KEY)
    {
        ClearTerminal();
        return false;
    }
    else if (input == ENTER_KEY)
    {
        ClearTerminal();
        return true;
    }
    return false;
}

ShopSection ShopView::buySection()
{

    gotoxy(0,20);
    while (true)
    {
        cout << "Shop sections: (Toggle the number on your keyboard to go on the section)" << endl
             << "1. Buy new items" << endl
             << "2. Sell your stuff" << endl
             << "3. Leave" << endl;
        char choice = _getch();
        if (choice == '1')
            return ShopSection::Buy;
        if (choice == '2')
            return ShopSection::Sell;
        if (choice == '3')
        {
            gotoxy(18, 19);
            cout << "        ";
            return ShopSection::Leave;
        }
        cout << endl
             << "Enter a valid input!" << endl;
    }
}

int ShopView::sellItems(Human *player)
{
    int input;
    while (true)
    {
        HumanView::showInventory(player->items);
        gotoxy(0, 20);
        cout << "Choose items to sell or enter (" << player->items.size() + 1 << ") to leave: ";
        cin >> input;
        if (input > 0 && input <= player->items.size() + 1)
        {
            break;
        }
        cout << endl
             << "Enter a valid input!" << endl;
    }
    input--;
    if (input == player->items.size())
        return -1;
    else
    {
        return input;
    }
}
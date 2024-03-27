#include "views.hpp"

void CharacterView::showAttack(Character* enemy , CharacterView* characterView)
{
    cout << characterView->model->get_name() << " : I damaged to " << enemy->get_name() << endl;
}

void CharacterView::showTakeDamage(CharacterView* characterView)
{
    cout << characterView->model->get_name() << " : AAKH! ُThis hurts me" << endl;
}

void HumanView::showUseItem(Item* item , HumanView* humanView)
{
    cout << humanView->model->get_name() << " : I used " << item->getName() << " item" << endl;
}

void HumanView::showAppendHP(int value , HumanView* humanView)
{
    cout << humanView->model->get_name() << " : YOOHO! I got " << value << " HP" << endl;
}

void HumanView::showAppendStamina(int value , HumanView* humanView)
{
    cout << humanView->model->get_name() << " : Eyval! I got " << value << " Stamina" << endl;
}

 void ZombieView::showAttack(Character* character , ZombieView* zombieView)
{
    cout <<zombieView->model->get_name() << " : HaHa! I damaged to you! you can't beat me " <<
    character->get_name() << "!" << endl;
}

#include "views.hpp"

void CharacterView::showAttack(Character* enemy)
{
    cout << this->model->get_name() << " : I damaged to " << enemy->get_name() << endl;
}

void CharacterView::showTakeDamage()
{
    cout << this->model->get_name() << " : AAKH! ُThis hurts me" << endl;
}

void HumanView::showUseItem(Item* item)
{
    cout << this->model->get_name() << " : I used " << item->getName() << " item" << endl;
}

void HumanView::showAppendHP(int value)
{
    cout << this->model->get_name() << " : YOOHO! I got " << value << " HP" << endl;
}

void HumanView::showAppendStamina(int value)
{
    cout << this->model->get_name() << " : Eyval! I got " << value << " Stamina" << endl;
}

void ZombieView::showAttack(Character* character)
{
    cout << this->model->get_name() << " : HaHa! I damaged to you! you can't beat me " << 
    character->get_name() << "!" << endl;
}

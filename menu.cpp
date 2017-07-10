#include "menu.h"

Menu::Menu()
{
    action = NULL;
}

Menu:: ~Menu()
{

}


void Menu::showPixMenu()
{
    this->removeAllAction();


}

void Menu::showProfileMenu()
{

}

void Menu::showWellMenu()
{
    this->removeAllAction();
    action  = new QAction(QStringLiteral("井"),this);
    action->setCheckable(true);
    action->setChecked(true);
    action  = new QAction(QStringLiteral("地层"),this);
    action->setCheckable(true);
    action->setChecked(true);
    action->setData(MARK_PIX_PIX);
    this->addAction(action);

    action  = new QAction(QStringLiteral("名称"),this);
    action->setCheckable(true);
    action->setChecked(true);
    action->setData(MARK_PIX_NAME);
    this->addAction(action);

    this->exec(QCursor::pos());
    action->setData(MARK_WELL_WELL);
    this->addAction(action);

    action  = new QAction(QStringLiteral("井头"),this);
    action->setCheckable(true);
    action->setChecked(true);
    action->setData(MARK_WELL_HEAD);
    this->addAction(action);

    action  = new QAction(QStringLiteral("井名"),this);
    action->setCheckable(true);
    action->setChecked(true);
    action->setData(MARK_WELL_NAME);
    this->addAction(action);

    this->exec(QCursor::pos());
}

void Menu::removeAllAction()
{
    QList<QAction*>list = this->actions();
    for(int i=0;i<list.size();i++)
    {
        this->removeAction(list.at(i));
    }
}

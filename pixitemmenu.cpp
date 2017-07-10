#include "pixitemmenu.h"

PixItemMenu::PixItemMenu()
{
    action  = new QAction(QStringLiteral("删除"),this);
    action->setCheckable(false);
    action->setChecked(true);
    action->setData(MARk_PIX_DEL);
    this->addAction(action);
    action  = new QAction(QStringLiteral("半透明"),this);
    action->setCheckable(true);
    action->setChecked(false);
    action->setData(MARK_PIX_TRANSPARENT);
    this->addAction(action);
}


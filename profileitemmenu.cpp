#include "profileitemmenu.h"

ProfileItemMenu::ProfileItemMenu()
{
    action  = new QAction(QStringLiteral("删除"),this);
    action->setCheckable(false);
    action->setChecked(true);
    action->setData(MARK_PROFILE_DEL);
    this->addAction(action);

    action  = new QAction(QStringLiteral("半透明"),this);
    action->setCheckable(true);
    action->setChecked(true);
    action->setData(MARK_PROFILE_TRANSPARENT);
    this->addAction(action);
}


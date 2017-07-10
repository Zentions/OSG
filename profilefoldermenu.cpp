#include "profilefoldermenu.h"

ProfileFolderMenu::ProfileFolderMenu()
{
    action  = new QAction(QStringLiteral("名称"),this);
    action->setCheckable(true);
    action->setChecked(true);
    action->setData(MARK_PROFILE_NAME);
    this->addAction(action);

    action  = new QAction(QStringLiteral("剖面图"),this);
    action->setCheckable(true);
    action->setChecked(true);
    action->setData(MARK_PROFILE_PIX);
    this->addAction(action);
}


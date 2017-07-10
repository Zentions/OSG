#include "wellfoldermenu.h"

WellFolderMenu::WellFolderMenu()
{
    action  = new QAction(QStringLiteral("井名"),this);
    action->setCheckable(true);
    action->setChecked(true);
    action->setData(MARK_WELL_NAME);
    this->addAction(action);

    action  = new QAction(QStringLiteral("井"),this);
    action->setCheckable(true);
    action->setChecked(true);
    action->setData(MARK_WELL_WELL);
    this->addAction(action);

    action  = new QAction(QStringLiteral("井头"),this);
    action->setCheckable(true);
    action->setChecked(true);
    action->setData(MARK_WELL_HEAD);
    this->addAction(action);
}


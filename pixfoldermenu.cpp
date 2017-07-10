#include "pixfoldermenu.h"

PixFolderMenu::PixFolderMenu()
{
    action  = new QAction(QStringLiteral("名称"),this);
    action->setCheckable(true);
    action->setChecked(true);
    action->setData(MARK_PIX_NAME);
    this->addAction(action);

    action  = new QAction(QStringLiteral("地层图"),this);
    action->setCheckable(true);
    action->setChecked(true);
    action->setData(MARK_PIX_PIX);
    this->addAction(action);
}

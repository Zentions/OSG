#include "wellitemmenu.h"

WellItemMenu::WellItemMenu()
{
    action  = new QAction(QStringLiteral("删除"),this);
    action->setCheckable(false);
    action->setChecked(true);
    action->setData(MARK_WELL_DEL);
    this->addAction(action);
}


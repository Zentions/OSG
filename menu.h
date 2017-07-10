#ifndef MENU_H
#define MENU_H

#define MARK_PIX_PIX 1 //地层文件夹地层标记
#define MARK_PIX_NAME 2 //地层文件夹名称标记
#define MARK_WELL_WELL 3 //井文件夹标井记
#define MARK_WELL_HEAD 4 //井文件夹井头标记
#define MARK_WELL_NAME 5 //井文件夹名称标记
#define MARk_PIX_DEL 6 //地层对象删除标记
#define MARK_WELL_DEL 7//井对象删除标记
#define MARK_PROFILE_PIX 8//剖面图文件夹图片标记
#define MARK_PROFILE_NAME 9//剖面图文件夹名称标记
#define MARK_PROFILE_DEL 10//剖面图对象删除标记
#define MARK_PROFILE_TRANSPARENT 11//剖面图对象半透明标记
#define MARK_PIX_TRANSPARENT 12 //勘探成果图半透明标记
#include <QMenu>
#include <QAction>
#include <QModelIndex>
#include <QVariant>
#include <QCursor>
#include <QtCore>

#include <osg/Group>
#include <osg/ref_ptr>
class Menu : public QMenu
{
public:
    Menu();
    ~Menu();

    void showPixMenu();
    void showWellMenu();
    void showProfileMenu();
    void removeAllAction();
protected:

    QAction *action;


};

#endif // MENU_H

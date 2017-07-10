#ifndef TREEVIEW_H
#define TREEVIEW_H

#define ROLE_MARK Qt::UserRole+1 //根节点
#define ROLE_MARK_FOLDER  Qt::UserRole+2//文件夹节点
#define ROLE_MARK_ITEM Qt::UserRole+3//条目节点

//对应ROLE_MARK
#define MARK_PROJECT 1//总项目标记
#define MARK_FOLDER 2//文件夹标记
#define MARK_ITEM 3//条目标记
//对应ROLE_MARK_FOLDER，标记folder种类
#define MARK_FOLDER_PIX 1 //底层文件文件夹标记
#define MARK_FOLDER_WELL 2 //井文件文件夹标记
#define MARK_FOLDER_PROFILE 3 //连井剖面文件文件夹标记
//对应ROLE_MARK_ITEM,标记item种类
#define MARK_ITEM_PIX 1 //底层文件标记
#define MARK_ITEM_WELL 2 //井文件标记
#define MARK_ITEM_PROFILE 3 //连井剖面文件标记


#include <QWidget>
#include <QTreeView>
#include <QStandardItemModel>
#include <QtCore/QtCore>
#include <QtGui/QtGui>
#include <QPixmap>
#include <QMessageBox>
#include <QAction>
#include <QVariant>
#include "menu.h"
class TreeView : public QTreeView
{
    Q_OBJECT
public:
    TreeView(QWidget* parent = 0);
    ~TreeView();

    void addRoot();
    void addChild(QString,QString);
    void addPixFile(QString name);
    void addWellFile(QString name);
    void addProfileFile(QString name);

    bool isChecked();

    void treeItem_checkAllChild(QStandardItem * item, bool check);
    void treeItem_checkAllChild_recursion(QStandardItem * item,bool check);
    void treeItem_CheckChildChanged(QStandardItem * item);

    void deleteWellItem(QModelIndex);
    void deletePixItem(QModelIndex);
    void deleteProfileItem(QModelIndex);
    Qt::CheckState checkSibling(QStandardItem * item);
    QStandardItemModel *model;

private:
    void init();

    QStandardItem *root;
    QStandardItem *itemChild;
    QStandardItem *itemProject;
    QStandardItem *itemPixChild;
    QStandardItem *itemWellChild;
    QStandardItem *itemProfileChild;
    QStandardItem *itemPixFileChild;
    QStandardItem *itemWellFileChild;
    QStandardItem *itemProfileFileChild;
    QMap<QString,QIcon> m_publicIconMap;
    QString projectPath;
    bool m_state;//判断是否选中
private slots:
    void treeItemChanged (QStandardItem * item );
    void treeItem_CheckActionTriggerd(QAction*);
signals:
    void stateChanged(QString,int,int,bool);

};

#endif // TREEVIEW_H

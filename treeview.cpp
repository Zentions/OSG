#include "treeview.h"

TreeView::TreeView(QWidget *parent)
{
    init();
    this->setParent(parent);
}
TreeView::~TreeView()
{

}
void TreeView::init()
{
    //设置图标
    m_publicIconMap[QStringLiteral("treeItem_Text")] =QIcon(QStringLiteral("Text.png"));
    m_publicIconMap[QStringLiteral("treeItem_Pix")] =QIcon(QStringLiteral("Pix.png"));
    m_publicIconMap[QStringLiteral("treeItem_Osg")] =QIcon(QStringLiteral("Osg.png"));
    //添加表头
    model = new QStandardItemModel(this);
    model->setHorizontalHeaderLabels(QStringList()<<QStringLiteral("项目"));

    connect(model,SIGNAL(itemChanged(QStandardItem*)),this,SLOT(treeItemChanged(QStandardItem*)));
    this->setModel(model);

}

//添加项目文件夹
void TreeView::addChild(QString name,QString path)
{


    //将上一项目的树信息清空
    model->clear();
    model->setHorizontalHeaderLabels(QStringList()<<QStringLiteral("项目"));
    //创建根目录
    root = new QStandardItem(name);
    root->setData(MARK_PROJECT,ROLE_MARK);
    root->setData(MARK_FOLDER,ROLE_MARK_FOLDER);
    model->appendRow(root);
    //创建勘探成果图文件夹
    itemPixChild=new QStandardItem(m_publicIconMap[QStringLiteral("treeItem_Pix")],QStringLiteral("勘探成果图"));
    itemPixChild->setEditable(false);
    //itemPixChild->setData(MARK_FOLDER,ROLE_MARK);//首先它是文件夹
    itemPixChild->setData(MARK_FOLDER_PIX,ROLE_MARK_FOLDER);//其次它属于勘探成果图文件夹
    root->appendRow(itemPixChild);
    //创建井文件夹
    itemWellChild=new QStandardItem(m_publicIconMap[QStringLiteral("treeItem_Osg")],QStringLiteral("井"));
    itemWellChild->setEditable(false);
  //  itemWellChild->setData(MARK_FOLDER,ROLE_MARK);//首先它是文件夹
    itemWellChild->setData(MARK_FOLDER_WELL,ROLE_MARK_FOLDER);//其次它属于井文件文件夹
    root->appendRow(itemWellChild);
    //创建连井剖面文件夹
    itemProfileChild=new QStandardItem(m_publicIconMap[QStringLiteral("treeItem_Osg")],"连井剖面");
    itemProfileChild->setEditable(false);
  //  itemProfileChild->setData(MARK_FOLDER,ROLE_MARK);//首先它是文件夹
    itemProfileChild->setData(MARK_FOLDER_PROFILE,ROLE_MARK_FOLDER);//其次它属于连井剖面文件文件夹
    root->appendRow(itemProfileChild);
    //保存项目路径
    projectPath = path;

}

//添加勘探成果图文件
void TreeView::addPixFile(QString name)
{
    itemPixFileChild=new QStandardItem(name);
    itemPixFileChild->setEditable(true);
    itemPixFileChild->setCheckable(true);
    itemPixFileChild->setTristate(true);
    itemPixFileChild->setCheckState(Qt::Checked);
    itemPixFileChild->setData(MARK_ITEM,ROLE_MARK);
    itemPixFileChild->setData(MARK_ITEM_PIX,ROLE_MARK_ITEM);
    itemPixChild->appendRow(itemPixFileChild);

    //创建子节点
    itemChild=new QStandardItem("名称");
    itemChild->setEditable(false);
    itemChild->setCheckable(true);
    itemChild->setCheckState(Qt::Checked);
    itemPixFileChild->appendRow(itemChild);

    itemChild=new QStandardItem("地层");
    itemChild->setEditable(false);
    itemChild->setCheckable(true);
    itemChild->setCheckState(Qt::Checked);
    itemPixFileChild->appendRow(itemChild);


}
//添加井文件
void TreeView::addWellFile(QString name)
{
    itemWellFileChild=new QStandardItem(name);
    itemWellFileChild->setEditable(true);
    itemWellFileChild->setCheckable(true);
    itemWellFileChild->setTristate(true);
    itemWellFileChild->setCheckState(Qt::Checked);
  //  itemWellFileChild->setData(MARK_ITEM,ROLE_MARK);
    itemWellFileChild->setData(MARK_ITEM_WELL,ROLE_MARK_ITEM);
    itemWellChild->appendRow(itemWellFileChild);

    //创建子节点
    itemChild=new QStandardItem("井名");
    itemChild->setEditable(false);
    itemChild->setCheckable(true);
    itemChild->setCheckState(Qt::Checked);
    itemWellFileChild->appendRow(itemChild);

    itemChild=new QStandardItem("井");
    itemChild->setEditable(false);
    itemChild->setCheckable(true);
    itemChild->setCheckState(Qt::Checked);
    itemWellFileChild->appendRow(itemChild);

    itemChild=new QStandardItem("井头");
    itemChild->setEditable(false);
    itemChild->setCheckable(true);
    itemChild->setCheckState(Qt::Checked);
    itemWellFileChild->appendRow(itemChild);
}
//添加连井剖面文件
void TreeView::addProfileFile(QString name)
{
    itemProfileFileChild=new QStandardItem(name);
    itemProfileFileChild->setEditable(true);
    itemProfileFileChild->setCheckable(true);
    itemProfileFileChild->setTristate(true);
    itemProfileFileChild->setCheckState(Qt::Checked);
  //  itemProfileFileChild->setData(MARK_ITEM,ROLE_MARK);
    itemProfileFileChild->setData(MARK_ITEM_PROFILE,ROLE_MARK_ITEM);
    itemProfileChild->appendRow(itemProfileFileChild);

    //创建子节点
    itemChild=new QStandardItem("名称");
    itemChild->setEditable(false);
    itemChild->setCheckable(true);
    itemChild->setCheckState(Qt::Checked);
    itemProfileFileChild->appendRow(itemChild);

    itemChild=new QStandardItem("剖面图");
    itemChild->setEditable(false);
    itemChild->setCheckable(true);
    itemChild->setCheckState(Qt::Checked);
    itemProfileFileChild->appendRow(itemChild);

}
/*当treeview中有item的复选框发生改变时，将发生改变的item所在的组
及所在行以信号的形式发送出去*/
void TreeView::treeItemChanged (QStandardItem *item)
{
    if(item==NULL)
        return;
    if(item->isCheckable())
    {
        //如果条目是存在复选框的，那么就进行下面的操作
               Qt::CheckState state = item -> checkState (); //获取当前的选择状态
               if (item->isTristate())
               {
                    //如果条目是三态的，说明可以对子目录进行全选和全不选的设置
                   if (state!= Qt::PartiallyChecked)
                   {
                       //当前是选中状态，需要对其子项目进行全选
                       treeItem_checkAllChild(item,state == Qt::Checked ? true : false );
                   }

               }
               else
               {
                //说明是两态的，两态会对父级的三态有影响
                //判断兄弟节点的情况

                 treeItem_CheckChildChanged ( item );

               }


    }
}
//
// \brief 递归设置所有的子项目为全选或全不选状态
// \param item 当前项目
// \param check true时为全选，false时全不选
//
void TreeView::treeItem_checkAllChild(QStandardItem * item, bool check)
{
    if(item == NULL)
        return;
    int rowCount = item->rowCount();
    for(int i=0;i<rowCount;++i)
    {
        QStandardItem* childItems = item->child(i);
        treeItem_checkAllChild_recursion(childItems,check);
    }
    if(item->isCheckable())
        item->setCheckState(check ? Qt::Checked : Qt::Unchecked);
}

void TreeView::treeItem_checkAllChild_recursion(QStandardItem * item,bool check)
{
    if(item == NULL)
        return;
    if(item->isCheckable())
        item->setCheckState(check ? Qt::Checked : Qt::Unchecked);
}
//
// \brief 根据子节点的改变，更改父节点的选择情况
// \param item
//
void TreeView::treeItem_CheckChildChanged(QStandardItem * item)
{
    if(item==NULL)
        return;

    Qt::CheckState state = item->checkState();
    Qt::CheckState siblingState = checkSibling(item);
    QStandardItem * parentItem = item->parent();

    if(NULL == parentItem)
        return;
    emit stateChanged(QString(parentItem->parent()->data(0).toString())
                       ,parentItem->index().row(),item->index().row(),state == Qt::Checked ? true : false);

    if(Qt::PartiallyChecked == siblingState)
    {
        if(parentItem->isCheckable() && parentItem->isTristate())
            parentItem->setCheckState(Qt::PartiallyChecked);
    }
    else if(Qt::Checked == siblingState)
    {
        if(parentItem->isCheckable())
            parentItem->setCheckState(Qt::Checked);
    }
    else
    {
        if(parentItem->isCheckable())
            parentItem->setCheckState(Qt::Unchecked);
    }
}
//
// \brief 测量兄弟节点的情况，如果都选中返回Qt::Checked，都不选中Qt::Unchecked,不完全选中返回Qt::PartiallyChecked
// \param item
// \return 如果都选中返回Qt::Checked，都不选中Qt::Unchecked,不完全选中返回Qt::PartiallyChecked
//
Qt::CheckState TreeView::checkSibling(QStandardItem * item)
{
    //先通过父节点获取兄弟节点
    QStandardItem * parent = item->parent();
    if(NULL == parent)
        return item->checkState();
    int brotherCount = parent->rowCount();
    int checkedCount(0),unCheckedCount(0);
    Qt::CheckState state;
    for(int i=0;i<brotherCount;++i)
    {
        QStandardItem* siblingItem = parent->child(i);
        state = siblingItem->checkState();
        if(Qt::PartiallyChecked == state)
            return Qt::PartiallyChecked;
        else if(Qt::Unchecked == state)
            ++unCheckedCount;
        else
            ++checkedCount;
        if(checkedCount>0 && unCheckedCount>0)
            return Qt::PartiallyChecked;
    }
    if(unCheckedCount>0)
        return Qt::Unchecked;
    return Qt::Checked;
}

void TreeView::treeItem_CheckActionTriggerd(QAction *action)
{

    QVariant var = action->data();
    if(!action->isChecked())
    {
        action->setChecked(false);
        switch(var.toInt())
        {
        case MARK_PIX_NAME:
            for(int i=0;i<itemPixChild->rowCount();i++)
            {
                itemPixChild->child(i)->child(0)->setCheckState(Qt::Unchecked);
            }
            break;
        case MARK_PIX_PIX:
            for(int i=0;i<itemPixChild->rowCount();i++)
            {
                itemPixChild->child(i)->child(1)->setCheckState(Qt::Unchecked);
            }
            break;
        case MARK_WELL_HEAD:
            for(int i=0;i<itemWellChild->rowCount();i++)
            {
                itemWellChild->child(i)->child(2)->setCheckState(Qt::Unchecked);
            }
            break;
        case MARK_WELL_NAME:
            for(int i=0;i<itemWellChild->rowCount();i++)
            {
                itemWellChild->child(i)->child(0)->setCheckState(Qt::Unchecked);
            }
            break;
        case MARK_WELL_WELL:
            for(int i=0;i<itemWellChild->rowCount();i++)
            {
                itemWellChild->child(i)->child(1)->setCheckState(Qt::Unchecked);
            }
            break;
        case MARK_PROFILE_NAME:
            for(int i=0;i<itemProfileChild->rowCount();i++)
            {
                itemProfileChild->child(i)->child(0)->setCheckState(Qt::Unchecked);
            }
            break;
        case MARK_PROFILE_PIX:
            for(int i=0;i<itemProfileChild->rowCount();i++)
            {
                itemProfileChild->child(i)->child(1)->setCheckState(Qt::Unchecked);
            }
            break;

        }

    }
    else
    {
        action->setChecked(true);
        switch(var.toInt())
        {
        case MARK_PIX_NAME:
            for(int i=0;i<itemPixChild->rowCount();i++)
            {
                itemPixChild->child(i)->child(0)->setCheckState(Qt::Checked);
            }
            break;
        case MARK_PIX_PIX:
            for(int i=0;i<itemPixChild->rowCount();i++)
            {
                itemPixChild->child(i)->child(1)->setCheckState(Qt::Checked);
            }
            break;
        case MARK_WELL_HEAD:
            for(int i=0;i<itemWellChild->rowCount();i++)
            {
                itemWellChild->child(i)->child(2)->setCheckState(Qt::Checked);
            }
            break;
        case MARK_WELL_NAME:
            for(int i=0;i<itemWellChild->rowCount();i++)
            {
                itemWellChild->child(i)->child(0)->setCheckState(Qt::Checked);
            }
            break;
        case MARK_WELL_WELL:
            for(int i=0;i<itemWellChild->rowCount();i++)
            {
                itemWellChild->child(i)->child(1)->setCheckState(Qt::Checked);
            }
            break;
        case MARK_PROFILE_NAME:
            for(int i=0;i<itemProfileChild->rowCount();i++)
            {
                itemProfileChild->child(i)->child(0)->setCheckState(Qt::Checked);
            }
            break;
        case MARK_PROFILE_PIX:
            for(int i=0;i<itemProfileChild->rowCount();i++)
            {
                itemProfileChild->child(i)->child(1)->setCheckState(Qt::Checked);
            }
            break;

        }
    }
}
//树中删除勘探成果图节点
void TreeView::deletePixItem(QModelIndex index)
{
    int row = index.row();
    QFile::remove(projectPath+"/勘探成果图/"+itemPixChild->child(row)->text()+".bmp");
    itemPixChild->removeRow(row);

}
//树中删除井节点
void TreeView::deleteWellItem(QModelIndex index)
{
    int row = index.row();
    QFile::remove(projectPath+"/井/"+itemWellChild->child(row)->text()+".dev");
    itemWellChild->removeRow(row);
}
//树中删除连井剖面图节点
void TreeView::deleteProfileItem(QModelIndex index)
{
    int row = index.row();
    QFile::remove(projectPath+"/连井剖面图/"+itemProfileChild->child(row)->text()+".bmp");

    itemProfileChild->removeRow(row);
}


#include "namedialog.h"
#include "ui_namedialog.h"
#include "projectoperation.h"
NameDialog::NameDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NameDialog)
{

    ui->setupUi(this);

    //设置复选框的默认状态
    ui->Pix->setChecked(true);
    ui->Well->setChecked(true);
    ui->Profile->setChecked(true);
}

NameDialog::~NameDialog()
{
    delete ui;
}
//将用户输入的数据作为信号发送
void NameDialog::on_confirmBtn_clicked()
{

    //获取用户选择的项目内容

    boxList.append(ui->Pix);
    boxList.append(ui->Well);
    boxList.append(ui->Profile);

    if(ui->fileRouteEdit->text()=="")
    {
        QMessageBox::information(this,"Error Message","请选择项目路径");
        return ;
    }

    //获取用户输入的名称
    if(ui->name->text()=="")
    {
        QMessageBox::information(this,"Error Message","请输入名称");
        return;
    }

    if(ui->fileRouteEdit->text()=="")
    {
        QMessageBox::information(this,"Error Message","请选择项目路径");
        return ;
    }
    //创建项目文件夹
    if(!ProjectOperation::createFolder(this,ui->fileRouteEdit->text()+"/"+ui->name->text()))
        return;

    //建立项目子文件夹
    this->createSubFolder();

    //创建项目文件
    if(!ProjectOperation::createProjectFile(ui->fileRouteEdit->text()+"/"+ui->name->text()+"/"+ui->name->text()+".pro"))
        return;
    emit sendData(ui->fileRouteEdit->text()+"/"+ui->name->text(),boxList);

    this->close();

}

void NameDialog::on_concelBtn_clicked()
{
    this->close();
}
//方便此类重用
void NameDialog::setTypeName(QString typeName)
{

    ui->label->setText(typeName+"名称：");
}




void NameDialog::on_browseBtn_clicked()
{
    ui->fileRouteEdit->setText(QFileDialog::getExistingDirectory(this,"选择目录",QDir::currentPath(),QFileDialog::ShowDirsOnly));
}

void NameDialog::createSubFolder()
{
    for(int i=0;i<boxList.size();i++)
    {
        if(boxList[i]->checkState())
            ProjectOperation::createFolder(this,ui->fileRouteEdit->text()+"/"+ui->name->text()+"/"+boxList[i]->text());
    }
}

void NameDialog::on_fileRouteEdit_cursorPositionChanged(int arg1, int arg2)
{

}

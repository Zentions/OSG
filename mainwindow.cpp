#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QInputDialog>
#include <sstream>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //初始化根节点
    group=new osg::Group;
    //初始化变化节点
    posNode = new osg::PositionAttitudeTransform;

    //树建立与否的标志
    treeCreated=false;

    //初始化右键菜单
    pixFolderMenu = new PixFolderMenu;
    wellFolderMenu = new WellFolderMenu;
    profileFolderMenu = new ProfileFolderMenu;
    pixItemMenu = new PixItemMenu;
    wellItemMenu = new WellItemMenu;
    profileItemMenu = new ProfileItemMenu;

    //初始化开关节点
    switchPixNode=new osg::Switch;
    switchWellNode=new osg::Switch;
    switchProfileNode=new osg::Switch;

    switchPixNode->setName("switchPixNode");
    switchWellNode->setName("switchWellNode");
    switchProfileNode->setName("switchProfileNode");
   // counter=1;

    //初始化命名窗口
    nameDialog = new NameDialog;

    //添加变换节点
    group->addChild(switchPixNode);
    group->addChild(switchWellNode);
    group->addChild(switchProfileNode);

  //  group->addChild(posNode);

    ui->graphicsView->setNode(group);
     //新建项目时对树的操作
    connect(ui->treeView,SIGNAL(stateChanged(QString,int,int,bool)),this,SLOT(changeState(QString,int,int,bool)));
    //工程命名
    connect(nameDialog,SIGNAL(sendData(QString,QList<QCheckBox*>)),this,SLOT(receveData(QString,QList<QCheckBox*>)));
    connect(nameDialog,SIGNAL(sendData(QString,QList<QCheckBox*>)),this,SLOT(reCreate()));

    //对类别文件夹的操作
    connect(pixFolderMenu,SIGNAL(triggered(QAction*)), ui->treeView,SLOT(treeItem_CheckActionTriggerd(QAction*)) );
    connect(wellFolderMenu,SIGNAL(triggered(QAction*)), ui->treeView,SLOT(treeItem_CheckActionTriggerd(QAction*)) );
    connect(profileFolderMenu,SIGNAL(triggered(QAction*)), ui->treeView,SLOT(treeItem_CheckActionTriggerd(QAction*)) );
    //对节点的操作
    connect(pixItemMenu,SIGNAL(triggered(QAction*)),this,SLOT(operatePixItem(QAction*)));
    connect(wellItemMenu,SIGNAL(triggered(QAction*)),this,SLOT(operateWellItem(QAction*)));
    connect(profileItemMenu,SIGNAL(triggered(QAction*)),this,SLOT(operateProfileItem(QAction*)));

    //设置初始状态的角度
   // setPosition();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Create_a_new_file_triggered()
{


    nameDialog->setTypeName("项目");

    nameDialog->show();


}

void MainWindow::on_Open_a_file_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,"Open Project",QDir::currentPath(),"*.pro");
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    reCreate();
    fileInfo = QFileInfo(fileName);
    treeCreated = true;
    projectPath =fileInfo.absolutePath() ;
    ui->treeView->addChild(fileInfo.baseName(), projectPath);

    ui->graphicsView->setNode(ProjectOperation::openProject(projectPath));
}


//接受treeview中复选框发生变化的item的所在组type以及所在行row
void MainWindow::changeState(QString type,int parentRow,int row,bool checked)
{

    if(type=="勘探成果图")
    {
        if(!checked)
        {
            switchPixNode->getChild(parentRow)->asSwitch()->setValue(row,false);

        }else
        {
            switchPixNode->getChild(parentRow)->asSwitch()->setValue(row,true);
        }
    }

    if(type=="井")
    {
        if(!checked)
        {
            switchWellNode->getChild(parentRow)->asSwitch()->setValue(row,false);

        }else
        {
            switchWellNode->getChild(parentRow)->asSwitch()->setValue(row,true);
        }
    }
    if(type=="连井剖面")
    {
        if(!checked)
        {
            switchProfileNode->getChild(parentRow)->asSwitch()->setValue(row,false);

        }else
        {
            switchProfileNode->getChild(parentRow)->asSwitch()->setValue(row,true);
        }
    }
}




void MainWindow::openFile(QString name)
{
    osg::ref_ptr<osg::DrawPixels> bmp= new osg::DrawPixels;
    bmp->setPosition( osg::Vec3( 0.0, 0.0, 0.0));
    bmp->setImage( osgDB::readImageFile(name.toStdString()));
    osg::ref_ptr< osg::Geode> geode= new osg::Geode;
    geode->addDrawable( bmp.get());
    osgViewer::Viewer viewer;
    viewer.setSceneData(geode.get());
}


void MainWindow::on_Close_a_new_file_triggered()
{

}

void MainWindow::on_Revocation_triggered()
{

}

void MainWindow::on_Restore_triggered()
{

}

void MainWindow::on_table_of_Contents_triggered()
{
    if(well==NULL){
        QMessageBox::information(this,"Error Message","请先添加井");
        return;
    }
    QString fileName = QFileDialog::getOpenFileName(this,"Open File",QDir::currentPath(),"*.bmp");
    if(fileName!=NULL) {
        well->setWellPipeConduit_textureImage(osgDB::readImageFile(fileName.toStdString()));
        QMessageBox::about(this,tr("确认提示框"),tr("图片加载成功!"));
     }else{
         QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));
     }

}

void MainWindow::on_Index_triggered()
{
    if(well==NULL){
        QMessageBox::information(this,"Error Message","请先添加井");
        return;
    }
   // well->CancelTexture(well->getWellPipe());

    TextureDialog *textureDialog = new TextureDialog(well->getWellTrace_dataXYZ()->begin()->z(),well->getWellTrace_dataXYZ()->end()->z());
    if (textureDialog->exec() == QDialog::Accepted) {
        QList<Data> list = textureDialog->getQList();
        std::cout<<list.size()<<std::endl;
        for(int i = 0;i<list.size();i++){

           if(well->setPartsTexture(well->getWellPipe(),list[i].start.toDouble(),list[i].end.toDouble(),osgDB::readImageFile(list[i].path.toStdString()))==-1){
              QMessageBox::information(this,"Error Message","深度不在范围之内");
           }
        }
    }
    delete textureDialog;
}

void MainWindow::on_Online_Help_triggered()
{
    if(well==NULL){
        QMessageBox::information(this,"Error Message","请先添加井");
        return;
    }
    if(well->CancelTexture(well->getWellPipe())){
        QMessageBox::about(this,tr("操作提示框"),tr("清楚纹理成功!"));
    }else{
        QMessageBox::about(this,tr("操作提示框"),tr("清除纹理失败!"));
    }
}


void MainWindow::on_Pick_up_triggered()
{
        //创建Viewer对象，场景浏览器
        osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
        //创建场景组节点
        osg::ref_ptr<osg::Group>root=new osg::Group();
        //创建一个节点，读取模型
        osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\example.osg");
        //添加到场景
        root->addChild(node.get());
        //优化场景数据
        osgUtil::Optimizer optimizer;
        optimizer.optimize(root.get());
        //设置场景数据
        viewer->setSceneData(root.get());
        //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
        viewer->setUpViewInWindow(50,50,1024,768);
        //开始渲染
        viewer->run();
}

void MainWindow::on_Drag_triggered()
{
    //创建Viewer对象，场景浏览器
        osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
        //创建场景组节点
        osg::ref_ptr<osg::Group>root=new osg::Group();
        //创建一个节点，读取模型
        osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\lz.osg");
        //添加到场景
        root->addChild(node.get());
        //优化场景数据
        osgUtil::Optimizer optimizer;
        optimizer.optimize(root.get());
        //设置场景数据
        viewer->setSceneData(root.get());
        //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
        viewer->setUpViewInWindow(50,50,1024,768);
        //开始渲染
        viewer->run();
}

void MainWindow::on_extend_triggered()
{
    //创建Viewer对象，场景浏览器
        osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
        //创建场景组节点
        osg::ref_ptr<osg::Group>root=new osg::Group();
        //创建一个节点，读取模型
        osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\morphing.osg");
        //添加到场景
        root->addChild(node.get());
        //优化场景数据
        osgUtil::Optimizer optimizer;
        optimizer.optimize(root.get());
        //设置场景数据
        viewer->setSceneData(root.get());
        //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
        viewer->setUpViewInWindow(50,50,1024,768);
        //开始渲染
        viewer->run();
}

void MainWindow::on_merge_triggered()
{
    //创建Viewer对象，场景浏览器
        osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
        //创建场景组节点
        osg::ref_ptr<osg::Group>root=new osg::Group();
        //创建一个节点，读取模型
        osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\morphtarget_shape0.osg");
        //添加到场景
        root->addChild(node.get());
        //优化场景数据
        osgUtil::Optimizer optimizer;
        optimizer.optimize(root.get());
        //设置场景数据
        viewer->setSceneData(root.get());
        //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
        viewer->setUpViewInWindow(50,50,1024,768);
        //开始渲染
        viewer->run();
}

void MainWindow::on_delete_2_triggered()
{
    if(well==NULL){
        QMessageBox::information(this,"Error Message","请先添加井");
        return;
    }
    if(well->getWellPipeConduit_textureImage()==NULL){
        QMessageBox::information(this,"Error Message","请先选择图片");
        return;
    }
    well->setRepeatTexture(well->getWellPipe(),20);
}

void MainWindow::on_copy_triggered()
{
    //创建Viewer对象，场景浏览器
        osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
        //创建场景组节点
        osg::ref_ptr<osg::Group>root=new osg::Group();
        //创建一个节点，读取模型
        osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\nathan.osg");
        //添加到场景
        root->addChild(node.get());
        //优化场景数据
        osgUtil::Optimizer optimizer;
        optimizer.optimize(root.get());
        //设置场景数据
        viewer->setSceneData(root.get());
        //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
        viewer->setUpViewInWindow(50,50,1024,768);
        //开始渲染
        viewer->run();
}

void MainWindow::on_Cutting_triggered()
{
    //创建Viewer对象，场景浏览器
        osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
        //创建场景组节点
        osg::ref_ptr<osg::Group>root=new osg::Group();
        //创建一个节点，读取模型
        osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\robot.osg");
        //添加到场景
        root->addChild(node.get());
        //优化场景数据
        osgUtil::Optimizer optimizer;
        optimizer.optimize(root.get());
        //设置场景数据
        viewer->setSceneData(root.get());
        //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
        viewer->setUpViewInWindow(50,50,1024,768);
        //开始渲染
        viewer->run();
}

void MainWindow::on_Property_superposition_triggered()
{
    //创建Viewer对象，场景浏览器
        osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
        //创建场景组节点
        osg::ref_ptr<osg::Group>root=new osg::Group();
        //创建一个节点，读取模型
        osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\axes.osgt");
        //添加到场景
        root->addChild(node.get());
        //优化场景数据
        osgUtil::Optimizer optimizer;
        optimizer.optimize(root.get());
        //设置场景数据
        viewer->setSceneData(root.get());
        //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
        viewer->setUpViewInWindow(50,50,1024,768);
        //开始渲染
        viewer->run();
}

void MainWindow::on_Unselected_triggered()
{
    //创建Viewer对象，场景浏览器
    osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
    //创建场景组节点
    osg::ref_ptr<osg::Group>root=new osg::Group();
    //创建一个节点，读取模型
    osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\clock.osgt");
    //添加到场景
    root->addChild(node.get());
    //优化场景数据
        osgUtil::Optimizer optimizer;
        optimizer.optimize(root.get());
        //设置场景数据
        viewer->setSceneData(root.get());
        //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
        viewer->setUpViewInWindow(50,50,1024,768);
        //开始渲染
        viewer->run();
}
bool isTrue(QString name){
    string t = name.toStdString();
    for(int i = 0;i <t.length();i++){
        if((name[i]>='0'&& name[i]<='9')||name[i]==';'||name[i]=='.' ||name[i]=='-'){
        }else{
            return false;
        }
    }
    return true;
}
void MainWindow::on_Save_as_triggered()
{
    if(well==NULL){
        QMessageBox::information(this,"Error Message","请先添加井");
        return;
    }
    if(well->getWellPipeConduit_textureImage()==NULL){
        QMessageBox::information(this,"Error Message","请先选择图片");
        return;
    }
    bool ok;
    QString name = QInputDialog::getText(this,
                                        tr("贴图深度"),
                                        tr("请输入两个数字，并以英文';'隔开"),
                                        QLineEdit::Normal,
                                        "0.0;0.0",
                                        &ok);
     if(ok && !name.isEmpty() && isTrue(name)) {
          QStringList strList;
          strList= name.split(";");
          double start = strList[0].toDouble();
          double end = strList[1].toDouble();
          if(well->setPartTexture(well->getWellPipe(),start,end)==-1){
              QMessageBox::information(this,"Error Message","深度不在范围之内");
          }

     }else{
         QMessageBox::information(this,"Error Message","输入数字格式错误");
         return;
     }

}
//保存工程
void MainWindow::on_save_triggered()
{

    ProjectOperation::saveProject(projectPath,group);

}

void MainWindow::on_reduction_triggered()
{
    ui->graphicsView->adjustCamera();
}

void MainWindow::on_whirl_alone_triggered()
{
    //创建Viewer对象，场景浏览器
        osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
        //创建场景组节点
        osg::ref_ptr<osg::Group>root=new osg::Group();
        //创建一个节点，读取模型
        osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\glsl_julia.osgt");
        //添加到场景
        root->addChild(node.get());
        //优化场景数据
        osgUtil::Optimizer optimizer;
        optimizer.optimize(root.get());
        //设置场景数据
        viewer->setSceneData(root.get());
        //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
        viewer->setUpViewInWindow(50,50,1024,768);
        //开始渲染
        viewer->run();
}

void MainWindow::on_whirl_triggered()
{
    //创建Viewer对象，场景浏览器
        osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
        //创建场景组节点
        osg::ref_ptr<osg::Group>root=new osg::Group();
        //创建一个节点，读取模型
        osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\glsl_mandelbrot.osgt");
        //添加到场景
        root->addChild(node.get());
        //优化场景数据
        osgUtil::Optimizer optimizer;
        optimizer.optimize(root.get());
        //设置场景数据
        viewer->setSceneData(root.get());
        //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
        viewer->setUpViewInWindow(50,50,1024,768);
        //开始渲染
        viewer->run();
}

void MainWindow::on_panoramic_triggered()
{
    //创建Viewer对象，场景浏览器
        osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
        //创建场景组节点
        osg::ref_ptr<osg::Group>root=new osg::Group();
        //创建一个节点，读取模型
        osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\glsl_simple.osgt");
        //添加到场景
        root->addChild(node.get());
        //优化场景数据
        osgUtil::Optimizer optimizer;
        optimizer.optimize(root.get());
        //设置场景数据
        viewer->setSceneData(root.get());
        //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
        viewer->setUpViewInWindow(50,50,1024,768);
        //开始渲染
        viewer->run();
}

void MainWindow::on_Bottom_view_triggered()
{
    //创建Viewer对象，场景浏览器
        osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
        //创建场景组节点
        osg::ref_ptr<osg::Group>root=new osg::Group();
        //创建一个节点，读取模型
        osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\skydome.osgt");
        //添加到场景
        root->addChild(node.get());
        //优化场景数据
        osgUtil::Optimizer optimizer;
        optimizer.optimize(root.get());
        //设置场景数据
        viewer->setSceneData(root.get());
        //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
        viewer->setUpViewInWindow(50,50,1024,768);
        //开始渲染
        viewer->run();
}

void MainWindow::on_Parallel_projection_triggered()
{
    //创建Viewer对象，场景浏览器
        osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
        //创建场景组节点
        osg::ref_ptr<osg::Group>root=new osg::Group();
        //创建一个节点，读取模型
        osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\SmokeBox.osgt");
        //添加到场景
        root->addChild(node.get());
        //优化场景数据
        osgUtil::Optimizer optimizer;
        optimizer.optimize(root.get());
        //设置场景数据
        viewer->setSceneData(root.get());
        //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
        viewer->setUpViewInWindow(50,50,1024,768);
        //开始渲染
        viewer->run();
}

void MainWindow::on_Perspective_projection_triggered()
{
    //创建Viewer对象，场景浏览器
        osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
        //创建场景组节点
        osg::ref_ptr<osg::Group>root=new osg::Group();
        //创建一个节点，读取模型
        osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\spaceship.osgt");
        //添加到场景
        root->addChild(node.get());
        //优化场景数据
        osgUtil::Optimizer optimizer;
        optimizer.optimize(root.get());
        //设置场景数据
        viewer->setSceneData(root.get());
        //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
        viewer->setUpViewInWindow(50,50,1024,768);
        //开始渲染
        viewer->run();
}

void MainWindow::on_enlarge_triggered()
{
    if(well==NULL){
        QMessageBox::information(this,"Error Message","请先添加井");
        return;
    }
    if(well->getWellPipeConduit_textureImage()==NULL){
        QMessageBox::information(this,"Error Message","请先选择图片");
        return;
    }
    bool ok;
    QString name = QInputDialog::getText(this,
                                        tr("贴图深度"),
                                        tr("请输入两个数字，并以英文';'隔开"),
                                        QLineEdit::Normal,
                                        "0.0;0.0",
                                        &ok);
     if(ok && !name.isEmpty() && isTrue(name)) {
          QStringList strList;
          strList= name.split(";");
          double start = strList[0].toDouble();
          double end = strList[1].toDouble();
          std::cout<<start<<" "<<end<<std::endl;
          if(well->setPartRepeatTexture(well->getWellPipe(),10,start,end)==-1){
              QMessageBox::information(this,"Error Message","深度不在范围之内");
          }
     }else{
         QMessageBox::information(this,"Error Message","输入数字格式错误");
         return;
     }
}

void MainWindow::on_Narrow_triggered()
{
    if(well==NULL){
        QMessageBox::information(this,"Error Message","请先添加井");
        return;
    }
    if(well->getWellPipeConduit_textureImage()==NULL){
        QMessageBox::information(this,"Error Message","请先选择图片");
        return;
    }
    well->setAllTexture(well->getWellPipe());
}



void MainWindow::on_Outsourcing_box_triggered()
{
        //创建Viewer对象，场景浏览器
            osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
            //创建场景组节点
            osg::ref_ptr<osg::Group>root=new osg::Group();
            //创建一个节点，读取模型
            osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\ui\\TabWidget.lua");
            //添加到场景
            root->addChild(node.get());
            //优化场景数据
            osgUtil::Optimizer optimizer;
            optimizer.optimize(root.get());
            //设置场景数据
            viewer->setSceneData(root.get());
            //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
            viewer->setUpViewInWindow(50,50,1024,768);
            //开始渲染
            viewer->run();
}

void MainWindow::on_XYZ_triggered()
{
    //创建Viewer对象，场景浏览器
        osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
        //创建场景组节点
        osg::ref_ptr<osg::Group>root=new osg::Group();
        //创建一个节点，读取模型
        osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\ui\\TransferFunctionWidget.lua");
        //添加到场景
        root->addChild(node.get());
        //优化场景数据
        osgUtil::Optimizer optimizer;
        optimizer.optimize(root.get());
        //设置场景数据
        viewer->setSceneData(root.get());
        //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
        viewer->setUpViewInWindow(50,50,1024,768);
        //开始渲染
        viewer->run();
}

void MainWindow::on_Staff_triggered()
{
    //创建Viewer对象，场景浏览器
        osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
        //创建场景组节点
        osg::ref_ptr<osg::Group>root=new osg::Group();
        //创建一个节点，读取模型
        osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\ui\\VolumeEditor.lua");
        //添加到场景
        root->addChild(node.get());
        //优化场景数据
        osgUtil::Optimizer optimizer;
        optimizer.optimize(root.get());
        //设置场景数据
        viewer->setSceneData(root.get());
        //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
        viewer->setUpViewInWindow(50,50,1024,768);
        //开始渲染
        viewer->run();
}

void MainWindow::on_North_view_triggered()
{
    //创建Viewer对象，场景浏览器
        osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
        //创建场景组节点
        osg::ref_ptr<osg::Group>root=new osg::Group();
        //创建一个节点，读取模型
        osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\ui\\VolumeEditorWidget.lua");
        //添加到场景
        root->addChild(node.get());
        //优化场景数据
        osgUtil::Optimizer optimizer;
        optimizer.optimize(root.get());
        //设置场景数据
        viewer->setSceneData(root.get());
        //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
        viewer->setUpViewInWindow(50,50,1024,768);
        //开始渲染
        viewer->run();
}

void MainWindow::on_Wellhead_triggered()
{
    //创建Viewer对象，场景浏览器
        osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
        //创建场景组节点
        osg::ref_ptr<osg::Group>root=new osg::Group();
        //创建一个节点，读取模型
        osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\ui\\VolumeSettings.lua");
        //添加到场景
        root->addChild(node.get());
        //优化场景数据
        osgUtil::Optimizer optimizer;
        optimizer.optimize(root.get());
        //设置场景数据
        viewer->setSceneData(root.get());
        //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
        viewer->setUpViewInWindow(50,50,1024,768);
        //开始渲染
        viewer->run();

}

void MainWindow::on_Well_trajectory_triggered()
{
    //创建Viewer对象，场景浏览器
        osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
        //创建场景组节点
        osg::ref_ptr<osg::Group>root=new osg::Group();
        //创建一个节点，读取模型
        osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\ui\\WidgetUtils.lua");
        //添加到场景
        root->addChild(node.get());
        //优化场景数据
        osgUtil::Optimizer optimizer;
        optimizer.optimize(root.get());
        //设置场景数据
        viewer->setSceneData(root.get());
        //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
        viewer->setUpViewInWindow(50,50,1024,768);
        //开始渲染
        viewer->run();
}

void MainWindow::on_Logs_triggered()
{
    //创建Viewer对象，场景浏览器
        osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
        //创建场景组节点
        osg::ref_ptr<osg::Group>root=new osg::Group();
        //创建一个节点，读取模型
        osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\SolarSystem\\earth_clouds256128.jpg");
        //添加到场景
        root->addChild(node.get());
        //优化场景数据
        osgUtil::Optimizer optimizer;
        optimizer.optimize(root.get());
        //设置场景数据
        viewer->setSceneData(root.get());
        //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
        viewer->setUpViewInWindow(50,50,1024,768);
        //开始渲染
        viewer->run();
}

void MainWindow::on_Perforation_triggered()
{
    //创建Viewer对象，场景浏览器
        osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
        //创建场景组节点
        osg::ref_ptr<osg::Group>root=new osg::Group();
        //创建一个节点，读取模型
        osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\shaders\\blocky.frag");
        //添加到场景
        root->addChild(node.get());
        //优化场景数据
        osgUtil::Optimizer optimizer;
        optimizer.optimize(root.get());
        //设置场景数据
        viewer->setSceneData(root.get());
        //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
        viewer->setUpViewInWindow(50,50,1024,768);
        //开始渲染
        viewer->run();
}

void MainWindow::on_Stratified_triggered()
{

}

void MainWindow::on_Reservoir_Simulation_triggered()
{
    TextureDialog *textureDialog = new TextureDialog(1.0,0);
    if (textureDialog->exec() == QDialog::Accepted) {
        QList<Data> list = textureDialog->getQList();
        std::cout<<list.size()<<std::endl;
    }
    delete textureDialog;
}

void MainWindow::on_Geological_model_triggered()
{
    //创建Viewer对象，场景浏览器
        osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
        //创建场景组节点
        osg::ref_ptr<osg::Group>root=new osg::Group();
        //创建一个节点，读取模型
        osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\osgWidget\\border-bottom.tga");
        //添加到场景
        root->addChild(node.get());
        //优化场景数据
        osgUtil::Optimizer optimizer;
        optimizer.optimize(root.get());
        //设置场景数据
        viewer->setSceneData(root.get());
        //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
        viewer->setUpViewInWindow(50,50,1024,768);
        //开始渲染
        viewer->run();
}

void MainWindow::on_crack_triggered()
{
    //创建Viewer对象，场景浏览器
        osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
        //创建场景组节点
        osg::ref_ptr<osg::Group>root=new osg::Group();
        //创建一个节点，读取模型
        osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\osgWidget\\osgwidgetshader-frag.glsl");
        //添加到场景
        root->addChild(node.get());
        //优化场景数据
        osgUtil::Optimizer optimizer;
        optimizer.optimize(root.get());
        //设置场景数据
        viewer->setSceneData(root.get());
        //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
        viewer->setUpViewInWindow(50,50,1024,768);
        //开始渲染
        viewer->run();
}

void MainWindow::on_color_triggered()
{
    /*colorBtn=new QPushButton;
    colorBtn->setText(tr("choose the color"));//pushbutton按钮名称
    colorFrame=new QFrame;
    colorFrame->setFrameShape(QFrame::Box);
    colorFrame->setAutoFillBackground(true);
    mainLayout=new QGridLayout(this);
    mainLayout->addWidget(colorBtn,1,0);//初始化0,0，布局设计
    mainLayout->addWidget(colorFrame,1,1);//初始化0,1
    connect(colorBtn,SIGNAL(clicked()),this,SLOT(showColor()));//事件关联*/
    osg::ref_ptr<osg::Camera>camera=new osg::Camera;

    camera->setClearColor( osg::Vec4(0.0, 0.0, 1.0, 1.0) );

}


void MainWindow::on_Hide_Show_triggered()
{
    osg::ref_ptr<osg::Geometry> geo=new osg::Geometry;
    osg::Vec4Array*colarray=new osg::Vec4Array;//颜色RGB值数组
    osg::UByteArray*colindex=new osg::UByteArray;//颜色索引数组

    colarray->push_back(osg::Vec4(1.0,0.0,0.0,1.0));//Red
    colarray->push_back(osg::Vec4(0.0,1.0,0.0,1.0));//Green
    colarray->push_back(osg::Vec4(0.0,0.0,1.0,1.0));//Blue
    colarray->push_back(osg::Vec4(1.0,1.0,1.0,1.0));//White

    colindex->push_back(3);
    colindex->push_back(2);
    colindex->push_back(1);
    colindex->push_back(0);

    geo->setColorArray(colarray);
    geo->setColorBinding(osg::Geometry::BIND_PER_VERTEX);

}

void MainWindow::on_move_triggered()
{
    //创建Viewer对象，场景浏览器
        osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
        //创建场景组节点
        osg::ref_ptr<osg::Group>root=new osg::Group();
        //创建一个节点，读取模型
        osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\Images\\Brick-Norman-Brown.TGA");
        //添加到场景
        root->addChild(node.get());
        //优化场景数据
        osgUtil::Optimizer optimizer;
        optimizer.optimize(root.get());
        //设置场景数据
        viewer->setSceneData(root.get());
        //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
        viewer->setUpViewInWindow(50,50,1024,768);
        //开始渲染
        viewer->run();
}

void MainWindow::on_Light_control_triggered()
{
    //创建Viewer对象，场景浏览器
        osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
        //创建场景组节点
        osg::ref_ptr<osg::Group>root=new osg::Group();
        //创建一个节点，读取模型
        osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\Images\\continous_smoke.rgb");
        //添加到场景
        root->addChild(node.get());
        //优化场景数据
        osgUtil::Optimizer optimizer;
        optimizer.optimize(root.get());
        //设置场景数据
        viewer->setSceneData(root.get());
        //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
        viewer->setUpViewInWindow(50,50,1024,768);
        //开始渲染
        viewer->run();
}

void MainWindow::on_drilling_triggered()
{
    //创建Viewer对象，场景浏览器
        osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
        //创建场景组节点
        osg::ref_ptr<osg::Group>root=new osg::Group();
        //创建一个节点，读取模型
        osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\fonts\\arial.ttf");
        //添加到场景
        root->addChild(node.get());
        //优化场景数据
        osgUtil::Optimizer optimizer;
        optimizer.optimize(root.get());
        //设置场景数据
        viewer->setSceneData(root.get());
        //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
        viewer->setUpViewInWindow(50,50,1024,768);
        //开始渲染
        viewer->run();
}

void MainWindow::on_profile_triggered()
{
    //创建Viewer对象，场景浏览器
        osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
        //创建场景组节点
        osg::ref_ptr<osg::Group>root=new osg::Group();
        //创建一个节点，读取模型
        osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\Configuration\\3DSphericalDisplay.view");
        //添加到场景
        root->addChild(node.get());
        //优化场景数据
        osgUtil::Optimizer optimizer;
        optimizer.optimize(root.get());
        //设置场景数据
        viewer->setSceneData(root.get());
        //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
        viewer->setUpViewInWindow(50,50,1024,768);
        //开始渲染
        viewer->run();
}

void MainWindow::on_well_deviation_triggered()
{
    //创建Viewer对象，场景浏览器
        osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
        //创建场景组节点
        osg::ref_ptr<osg::Group>root=new osg::Group();
        //创建一个节点，读取模型
        osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\Configuration\\3DSphericalDisplay.view");
        //添加到场景
        root->addChild(node.get());
        //优化场景数据
        osgUtil::Optimizer optimizer;
        optimizer.optimize(root.get());
        //设置场景数据
        viewer->setSceneData(root.get());
        //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
        viewer->setUpViewInWindow(50,50,1024,768);
        //开始渲染
        viewer->run();
}

void MainWindow::on_straight_line_triggered()
{
    //创建Viewer对象，场景浏览器
    osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
    //创建场景组节点
    osg::ref_ptr<osg::Group>root=new osg::Group();
    //创建一个节点，读取牛的模型
    osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\cow.osg");
    //添加到场景
    root->addChild(node.get());
    //优化场景数据
    osgUtil::Optimizer optimizer;
    optimizer.optimize(root.get());
    //设置场景数据
    viewer->setSceneData(root.get());
    //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
    viewer->setUpViewInWindow(50,50,1024,768);
    //开始渲染
    viewer->run();
}

void MainWindow::on_text_editor_triggered()
{
    //创建Viewer对象，场景浏览器
    osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
    //创建场景组节点
    osg::ref_ptr<osg::Group>root=new osg::Group();
    //创建一个节点，读取牛的模型
    osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\glider.osg");
    //添加到场景
    root->addChild(node.get());
    //优化场景数据
    osgUtil::Optimizer optimizer;
    optimizer.optimize(root.get());
    //设置场景数据
    viewer->setSceneData(root.get());
    //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
    viewer->setUpViewInWindow(50,50,1024,768);
    //开始渲染
    viewer->run();
}

void MainWindow::on_Draw_boundary_triggered()
{
    //创建Viewer对象，场景浏览器
    osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
    //创建场景组节点
    osg::ref_ptr<osg::Group>root=new osg::Group();
    //创建一个节点，读取牛的模型
    osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\glider.osg");
    //添加到场景
    root->addChild(node.get());
    //优化场景数据
    osgUtil::Optimizer optimizer;
    optimizer.optimize(root.get());
    //设置场景数据
    viewer->setSceneData(root.get());
    //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
    viewer->setUpViewInWindow(50,50,1024,768);
    //开始渲染
    viewer->run();
}

void MainWindow::on_Generate_contours_triggered()
{
    //创建Viewer对象，场景浏览器
    osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
    //创建场景组节点
    osg::ref_ptr<osg::Group>root=new osg::Group();
    //创建一个节点，读取牛的模型
    osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\glider.osg");
    //添加到场景
    root->addChild(node.get());
    //优化场景数据
    osgUtil::Optimizer optimizer;
    optimizer.optimize(root.get());
    //设置场景数据
    viewer->setSceneData(root.get());
    //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
    viewer->setUpViewInWindow(50,50,1024,768);
    //开始渲染
    viewer->run();
}

void MainWindow::on_layer_triggered()
{
    //创建Viewer对象，场景浏览器
    osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
    //创建场景组节点
    osg::ref_ptr<osg::Group>root=new osg::Group();
    //创建一个节点，读取牛的模型
    osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\glider.osg");
    //添加到场景
    root->addChild(node.get());
    //优化场景数据
    osgUtil::Optimizer optimizer;
    optimizer.optimize(root.get());
    //设置场景数据
    viewer->setSceneData(root.get());
    //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
    viewer->setUpViewInWindow(50,50,1024,768);
    //开始渲染
    viewer->run();
}

void MainWindow::on_Structural_map_triggered()
{
    //创建Viewer对象，场景浏览器
    osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
    //创建场景组节点
    osg::ref_ptr<osg::Group>root=new osg::Group();
    //创建一个节点，读取牛的模型
    osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\glider.osg");
    //添加到场景
    root->addChild(node.get());
    //优化场景数据
    osgUtil::Optimizer optimizer;
    optimizer.optimize(root.get());
    //设置场景数据
    viewer->setSceneData(root.get());
    //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
    viewer->setUpViewInWindow(50,50,1024,768);
    //开始渲染
    viewer->run();
}

void MainWindow::on_Thematic_map_triggered()
{
    //创建Viewer对象，场景浏览器
    osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
    //创建场景组节点
    osg::ref_ptr<osg::Group>root=new osg::Group();
    //创建一个节点，读取牛的模型
    osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\glider.osg");
    //添加到场景
    root->addChild(node.get());
    //优化场景数据
    osgUtil::Optimizer optimizer;
    optimizer.optimize(root.get());
    //设置场景数据
    viewer->setSceneData(root.get());
    //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
    viewer->setUpViewInWindow(50,50,1024,768);
    //开始渲染
    viewer->run();
}

void MainWindow::on_point_triggered()
{
    //创建Viewer对象，场景浏览器
    osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
    //创建场景组节点
    osg::ref_ptr<osg::Group>root=new osg::Group();
    //创建一个节点，读取牛的模型
    osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\glider.osg");
    //添加到场景
    root->addChild(node.get());
    //优化场景数据
    osgUtil::Optimizer optimizer;
    optimizer.optimize(root.get());
    //设置场景数据
    viewer->setSceneData(root.get());
    //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
    viewer->setUpViewInWindow(50,50,1024,768);
    //开始渲染
    viewer->run();
}

void MainWindow::on_line_triggered()
{
    //创建Viewer对象，场景浏览器
    osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
    //创建场景组节点
    osg::ref_ptr<osg::Group>root=new osg::Group();
    //创建一个节点，读取牛的模型
    osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\glider.osg");
    //添加到场景
    root->addChild(node.get());
    //优化场景数据
    osgUtil::Optimizer optimizer;
    optimizer.optimize(root.get());
    //设置场景数据
    viewer->setSceneData(root.get());
    //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
    viewer->setUpViewInWindow(50,50,1024,768);
    //开始渲染
    viewer->run();
}

void MainWindow::on_surface_triggered()
{
    //创建Viewer对象，场景浏览器
    osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
    //创建场景组节点
    osg::ref_ptr<osg::Group>root=new osg::Group();
    //创建一个节点，读取牛的模型
    osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\glider.osg");
    //添加到场景
    root->addChild(node.get());
    //优化场景数据
    osgUtil::Optimizer optimizer;
    optimizer.optimize(root.get());
    //设置场景数据
    viewer->setSceneData(root.get());
    //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
    viewer->setUpViewInWindow(50,50,1024,768);
    //开始渲染
    viewer->run();
}

void MainWindow::on_body_part_triggered()
{
    //创建Viewer对象，场景浏览器
    osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
    //创建场景组节点
    osg::ref_ptr<osg::Group>root=new osg::Group();
    //创建一个节点，读取牛的模型
    osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\glider.osg");
    //添加到场景
    root->addChild(node.get());
    //优化场景数据
    osgUtil::Optimizer optimizer;
    optimizer.optimize(root.get());
    //设置场景数据
    viewer->setSceneData(root.get());
    //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
    viewer->setUpViewInWindow(50,50,1024,768);
    //开始渲染
    viewer->run();
}

void MainWindow::on_Sphere_triggered()
{
    //创建Viewer对象，场景浏览器
    osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
    //创建场景组节点
    osg::ref_ptr<osg::Group>root=new osg::Group();
    //创建一个节点，读取牛的模型
    osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\glider.osg");
    //添加到场景
    root->addChild(node.get());
    //优化场景数据
    osgUtil::Optimizer optimizer;
    optimizer.optimize(root.get());
    //设置场景数据
    viewer->setSceneData(root.get());
    //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
    viewer->setUpViewInWindow(50,50,1024,768);
    //开始渲染
    viewer->run();
}

void MainWindow::on_cuboid_triggered()
{
    //创建Viewer对象，场景浏览器
    osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
    //创建场景组节点
    osg::ref_ptr<osg::Group>root=new osg::Group();
    //创建一个节点，读取牛的模型
    osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\glider.osg");
    //添加到场景
    root->addChild(node.get());
    //优化场景数据
    osgUtil::Optimizer optimizer;
    optimizer.optimize(root.get());
    //设置场景数据
    viewer->setSceneData(root.get());
    //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
    viewer->setUpViewInWindow(50,50,1024,768);
    //开始渲染
    viewer->run();
}

void MainWindow::on_Ellipsoid_triggered()
{
    //创建Viewer对象，场景浏览器
    osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
    //创建场景组节点
    osg::ref_ptr<osg::Group>root=new osg::Group();
    //创建一个节点，读取牛的模型
    osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\glider.osg");
    //添加到场景
    root->addChild(node.get());
    //优化场景数据
    osgUtil::Optimizer optimizer;
    optimizer.optimize(root.get());
    //设置场景数据
    viewer->setSceneData(root.get());
    //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
    viewer->setUpViewInWindow(50,50,1024,768);
    //开始渲染
    viewer->run();
}

void MainWindow::on_Cone_triggered()
{
    //创建Viewer对象，场景浏览器
    osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
    //创建场景组节点
    osg::ref_ptr<osg::Group>root=new osg::Group();
    //创建一个节点，读取牛的模型
    osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\glider.osg");
    //添加到场景
    root->addChild(node.get());
    //优化场景数据
    osgUtil::Optimizer optimizer;
    optimizer.optimize(root.get());
    //设置场景数据
    viewer->setSceneData(root.get());
    //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
    viewer->setUpViewInWindow(50,50,1024,768);
    //开始渲染
    viewer->run();
}

void MainWindow::on_Cylinder_triggered()
{
    //创建Viewer对象，场景浏览器
    osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
    //创建场景组节点
    osg::ref_ptr<osg::Group>root=new osg::Group();
    //创建一个节点，读取牛的模型
    osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\glider.osg");
    //添加到场景
    root->addChild(node.get());
    //优化场景数据
    osgUtil::Optimizer optimizer;
    optimizer.optimize(root.get());
    //设置场景数据
    viewer->setSceneData(root.get());
    //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
    viewer->setUpViewInWindow(50,50,1024,768);
    //开始渲染
    viewer->run();
}

void MainWindow::on_Yuantong_triggered()
{
    //创建Viewer对象，场景浏览器
    osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
    //创建场景组节点
    osg::ref_ptr<osg::Group>root=new osg::Group();
    //创建一个节点，读取牛的模型
    osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\glider.osg");
    //添加到场景
    root->addChild(node.get());
    //优化场景数据
    osgUtil::Optimizer optimizer;
    optimizer.optimize(root.get());
    //设置场景数据
    viewer->setSceneData(root.get());
    //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
    viewer->setUpViewInWindow(50,50,1024,768);
    //开始渲染
    viewer->run();
}

void MainWindow::on_Ring_triggered()
{
    //创建Viewer对象，场景浏览器
    osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
    //创建场景组节点
    osg::ref_ptr<osg::Group>root=new osg::Group();
    //创建一个节点，读取牛的模型
    osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\glider.osg");
    //添加到场景
    root->addChild(node.get());
    //优化场景数据
    osgUtil::Optimizer optimizer;
    optimizer.optimize(root.get());
    //设置场景数据
    viewer->setSceneData(root.get());
    //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
    viewer->setUpViewInWindow(50,50,1024,768);
    //开始渲染
    viewer->run();
}
//从osg::NodeCallBack继承一个新类，实现simpleCallBack的回调
class simpleCallBack:public osg::NodeCallback
{
public:
    simpleCallBack():_angle(0){}

    virtual void operator()(osg::Node* node, osg::NodeVisitor* nv)
    {
        //创建矩阵转换节点
        osg::ref_ptr<osg::MatrixTransform> mt=dynamic_cast<osg::MatrixTransform*>(node);
        //创建矩阵
        osg::Matrix mx;
        //绕着Z轴旋转
        mx.makeRotate(_angle,osg::Vec3(0.0,0.0,1.0));
        //设置矩阵
        mt->setMatrix(mx);

        _angle+=0.01;

        //继续遍历
        traverse(node,nv);

    }

public:
    //旋转角度
    double _angle;
};


void MainWindow::receveData(QString path,QList<QCheckBox*> boxList)
{

    //在此创建树
    treeCreated = true;
    projectPath = path;
    fileInfo = QFileInfo(path);
    ui->treeView->addChild(fileInfo.baseName(), path);
}

//添加勘探成果图

void MainWindow::on_Pix_triggered()
{
    //判断是否有根目录
    if(!treeCreated)
    {
        QMessageBox::information(this,"Error Message","请先添加一个项目");
        return ;
    }
    //打开文件
    QStringList fileNames = QFileDialog::getOpenFileNames(this,"Open File",QDir::currentPath(),"*.bmp");
    foreach (QString fileName, fileNames) {
        if(fileName.isEmpty())
        {
            return ;
        }

        fileInfo = QFileInfo(fileName);

        fileName = fileInfo.baseName();
        //拷贝文件
        QFile::copy(fileInfo.absoluteFilePath(),projectPath+"/Exploratory/"+fileInfo.fileName());

        //创建勘探成果图对象
        Pix pix;
        pix.setImagebyURL(fileInfo.absoluteFilePath());
        pix.setVertexArraybyURL(fileInfo.path()+"/"+fileName+".txt");

        osg::ref_ptr<osg::Geometry> geom = pix.getGeometry();
       // const osg::BoundingBox &box=pix.getGeometry()->getBoundingBox();
      //  float size=(box.xMax()-box.xMin())/10;
        geom->setName(fileInfo.fileName().toStdString());
        //添加自动对齐节点
      /*  osg::ref_ptr<osg::AutoTransform> at = new osg::AutoTransform();
        at->addChild(geom);
        at->setAutoRotateMode(osg::AutoTransform::ROTATE_TO_CAMERA);
        at->setAutoScaleToScreen(false);
        at->setMinimumScale(1.0f);
        at->setMaximumScale(2.0f);
        at->setPosition( osg::Vec3(box.xMin()+(box.xMax()-box.xMin())/2,box.yMax()+size,box.zMin() )  );
*/

        //创建勘探成果图节点
        osg::ref_ptr<osg::Switch> pixSwitch = new osg::Switch;
        pixSwitch->addChild(pix.getText());
        pixSwitch->addChild(geom);
        //添加转换节点
        switchPixNode->addChild(pixSwitch);

        //添加到treeview中
        ui->treeView->addPixFile(fileName);


       // counter++;

    }
    //重新计算包围盒
    ui->graphicsView->adjustCamera();
    //setPosition();

}

//添加井
void MainWindow::on_Well_triggered()
{//判断是否有根目录
        if(!treeCreated){
            QMessageBox::information(this,"Error Message","请先添加一个项目");
            return ;
        }
        //打开文件
        QString fileName = QFileDialog::getOpenFileName(this,"Open File",QDir::currentPath(),"*.wells");
        //创建井节点
       // osg::ref_ptr<osg::Switch> wellSwitch = new osg::Switch;
        well = new Well();
        well->setWellFileName(fileName);
        well->readWellData();
        well->setWellPipe(well->drawWellPipe());
     //   wellSwitch->addChild(well->getWellPipe());

        switchWellNode->addChild(well->getWellPipe());

        ui->graphicsView->adjustCamera();
        //添加到treeview中
        ui->treeView->addWellFile(fileName);
}

//加载连井剖面
void MainWindow::on_Profile_triggered()
{
    //判断是否有根目录
    if(!treeCreated)
    {
        QMessageBox::information(this,"Error Message","请先添加一个项目");
        return ;
    }
    //打开文件
    QStringList fileNames = QFileDialog::getOpenFileNames(this,"Open File",QDir::currentPath(),"*.bmp");
    foreach (QString fileName, fileNames) {
        if(fileName.isEmpty())
        {
            return ;
        }


        Profile * pro = new Profile();

        pro->setImagebyURL(fileName);

        fileInfo = QFileInfo(fileName);
        fileName = fileInfo.baseName();

        QString txtpath= fileInfo.path()+"/"+fileName+".txt";

        pro->setVertexArraybyURL(txtpath);
        osg::ref_ptr<osg::Geometry> geom = pro->getGeometry();
        geom->setName(fileInfo.fileName().toStdString());

        //添加Text


        //创建连井剖面节点
        osg::ref_ptr<osg::Switch> profileSwitch = new osg::Switch;

        profileSwitch->addChild(pro->getText());
        profileSwitch->addChild(geom);
        //添加转换节点
        switchProfileNode->addChild(profileSwitch);

        ui->treeView->addProfileFile(fileName);
      //  counter++;
        //拷贝文件
        QFile::copy(fileInfo.absoluteFilePath(),projectPath+"/Profile/"+fileInfo.fileName());

    }
    //重新计算包围盒
    ui->graphicsView->adjustCamera();
    //setPosition();
}


//重新创建场景
void MainWindow::reCreate()
{

    group=new osg::Group;
   // posNode = new osg::PositionAttitudeTransform;
    switchPixNode=new osg::Switch;
    switchWellNode=new osg::Switch;
    switchProfileNode=new osg::Switch;
    group->addChild(switchPixNode);
    group->addChild(switchWellNode);
    group->addChild(switchProfileNode);
    //group->addChild(posNode);
    //counter=0;
    ui->graphicsView->setNode(group);
}



void MainWindow::setPosition()
{
    osg::Quat quat;
    quat.makeRotate(osg::PI_4,osg::Vec3(1.0,0.0,0.0));
    posNode->setAttitude(quat);

}

void MainWindow::on_treeView_customContextMenuRequested(const QPoint &pos)
{
    QModelIndex index = ui->treeView->indexAt(pos);
    temppos = pos;
    QVariant FolderVar = index.data(ROLE_MARK_FOLDER);
    QVariant ItemVar = index.data(ROLE_MARK_ITEM);
    if(FolderVar.isValid())
    {

        if(MARK_FOLDER_PIX == FolderVar.toInt())
            pixFolderMenu->exec(QCursor::pos());
        else if(MARK_FOLDER_WELL == FolderVar.toInt())
            wellFolderMenu->exec(QCursor::pos());
        else if(MARK_FOLDER_PROFILE == FolderVar.toInt())
            profileFolderMenu->exec(QCursor::pos());

    }
    if(ItemVar.isValid())
    {
        if(MARK_ITEM_PIX == ItemVar.toInt())
            pixItemMenu->exec(QCursor::pos());
        if(MARK_ITEM_WELL == ItemVar.toInt())
            wellItemMenu->exec(QCursor::pos());
        if(MARK_ITEM_PROFILE == ItemVar.toInt())
            profileItemMenu->exec(QCursor::pos());
    }
}
//操作勘探成果图节点
void MainWindow::operatePixItem(QAction *action)
{

    QVariant MenuVar = action->data();
    //得到树上对象的index
    QModelIndex index = ui->treeView->indexAt(temppos);
    osg::StateSet* stateset1;

    if(MenuVar.isValid())
    {
        if(MARk_PIX_DEL==MenuVar.toInt())
        {
            switchPixNode->removeChild(switchPixNode->getChild(index.row()));
            ui->treeView->deletePixItem(index);
          //  counter--;
        }
        else if(MARK_PIX_TRANSPARENT==MenuVar.toInt())
        {
            if(action->isChecked())
            {
                action->setChecked(true);
                osg::ref_ptr<osg::Geometry> geom = switchPixNode->getChild(index.row())
                        ->asGroup()->getChild(0)->asGeometry();
                //创建颜色数组
                osg::ref_ptr<osg::Vec4Array> vc = new osg::Vec4Array();

                //添加数据
                vc->push_back(osg::Vec4(1.0f,1.0f,1.0f,0.5f));
                //设置颜色数组
                geom->setColorArray(vc.get());
                //设置颜色数组
                geom->setColorBinding(osg::Geometry::BIND_OVERALL);
            }
            else
            {
                action->setChecked(false);
                osg::ref_ptr<osg::Geometry> geom = switchPixNode->getChild(index.row())
                        ->asGroup()->getChild(0)->asGeometry();

                //创建颜色数组
                osg::ref_ptr<osg::Vec4Array> vc = new osg::Vec4Array();

                //添加数据
                vc->push_back(osg::Vec4(1.0f,1.0f,1.0f,1.0f));
                //设置颜色数组
                geom->setColorArray(vc.get());
                //设置颜色数组
                geom->setColorBinding(osg::Geometry::BIND_OVERALL);
            }
        }

    }

  //  ui->graphicsView->adjustCamera();
}
//操作井节点
void MainWindow::operateWellItem(QAction *action)
{
    QVariant MenuVar = action->data();
    QModelIndex index = ui->treeView->indexAt(temppos);
    switchWellNode->removeChild(switchWellNode->getChild(index.row()));
    ui->treeView->deleteWellItem(index);
   // counter--;
   // ui->graphicsView->adjustCamera();
}
//操作连井剖面图节点
void MainWindow::operateProfileItem(QAction *action)
{
    QVariant MenuVar = action->data();
    if(MenuVar.isValid())
    {
        if(MARK_PROFILE_DEL==MenuVar.toInt())
        {
            QModelIndex index = ui->treeView->indexAt(temppos);
            switchProfileNode->removeChild(switchProfileNode->getChild(index.row()));
            ui->treeView->deleteProfileItem(index);
        }
        else if(MARK_PROFILE_TRANSPARENT==MenuVar.toInt())
        {
           // if(Action)
        }
    }


   // ui->graphicsView->adjustCamera();
}



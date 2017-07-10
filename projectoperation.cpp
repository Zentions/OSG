#include "projectoperation.h"

ProjectOperation::ProjectOperation()
{
}

bool ProjectOperation::createFolder(QWidget *parent,QString route)
{
    QDir *folder = new QDir;
    bool exist = folder->exists(route);
    if(exist)
    {
        QMessageBox::warning(parent,"创建文件夹","项目已经存在！");
        return false;
    }
    else
    {
        folder->mkdir(route);
        return true;
    }
}

bool ProjectOperation::createProjectFile(QString route)
{
    QFile file(route);
    if ( file.exists())
    {
            return true;
    }
    file.open( QIODevice::ReadWrite | QIODevice::Text );
    file.close();
    return true;
}

bool ProjectOperation::saveProject(QString projectPath, osg::ref_ptr<osg::Group> root)
{

    QFileInfo fileInfo = QFileInfo(projectPath);
    //osg::ref_ptr<osg::Group> secondNode;
    QFile file(projectPath+"/"+fileInfo.baseName()+".pro");
    QTextStream stream(&file);

    if(!file.open(QIODevice::WriteOnly))
    {
        return false;
    }


   /* for(int i=0;i<root->getNumChildren();i++)
    {
        secondNode=root->getChild(i)->asGroup();
    }*/

    osg::ref_ptr<osg::Group> switchPixNode = root->getChild(0)->asGroup();
    osg::ref_ptr<osg::Group> switchWellNode = root->getChild(1)->asGroup();
    osg::ref_ptr<osg::Group> switchProfileNode = root->getChild(2)->asGroup();

    stream<<"Pix"<<endl;
    for(int i=0;i<switchPixNode->getNumChildren();i++)
    {

        osg::ref_ptr<osg::Group> pixSwitch = switchPixNode->getChild(i)->asGroup();

        //osg::ref_ptr<osg::Group> at = pixSwitch->getChild(0)->asGroup();
       // osg::ref_ptr<osgText::Text> text = at->getChild(0);

        //写入勘探成果图图片信息
        osg::ref_ptr<osg::Geometry> geom = pixSwitch->getChild(1)->asGeometry();
        osg::Vec3Array* vertexArray = dynamic_cast<osg::Vec3Array*>(geom->getVertexArray());
        //图片
        stream<<QObject::trUtf8("Exploratory/")<<QString::fromStdString(geom->getName())<<endl;
       //坐标
        for(int j=0;j<vertexArray->getNumElements();j++)
        {
            stream<<QString::number((*vertexArray)[j].x(),'f')<<","<<QString::number((*vertexArray)[j].y(),'f')<<","<<QString::number((*vertexArray)[j].z(),'f')<<endl;
        }

    }
    stream<<"Well"<<endl;
    for(int i=0;i<switchWellNode->getNumChildren();i++)
    {
        osg::ref_ptr<osg::Group>wellSwitch = switchWellNode->getChild(i)->asGroup();
        osg::ref_ptr<osg::Geometry> geom = wellSwitch->getChild(1)->asGeometry();

        stream<<QObject::trUtf8("Well/")<<QString::fromStdString(geom->getName())<<endl;
    }
    stream<<"Profile"<<endl;
    for(int i=0;i<switchProfileNode->getNumChildren();i++)
    {
        osg::ref_ptr<osg::Group> profileSwitch = switchProfileNode->getChild(i)->asGroup();

        //osg::ref_ptr<osg::Group> at = pixSwitch->getChild(0)->asGroup();
       // osg::ref_ptr<osgText::Text> text = at->getChild(0);

        //写入连井剖面图图图片信息
        osg::ref_ptr<osg::Geometry> geom = profileSwitch->getChild(1)->asGeometry();

        osg::Vec3Array* vertexArray = dynamic_cast<osg::Vec3Array*>(geom->getVertexArray());
        osg::Vec2Array* texcoordArray = dynamic_cast<osg::Vec2Array*>(geom->getTexCoordArray(0));
        //图片
        stream<<QObject::trUtf8("Profile/")<<QString::fromStdString(geom->getName())<<endl;
       qDebug()<<QObject::trUtf8("Profile/")<<QString::fromStdString(geom->getName());
        //坐标
        for(int j=0;j<vertexArray->getNumElements();j++)
        {
            stream<<QString::number((*vertexArray)[j].x(),'f')<<","<<QString::number((*vertexArray)[j].y(),'f')<<","<<QString::number((*vertexArray)[j].z(),'f')<<endl;
        }
        //纹理

        for(int j=0;j<texcoordArray->getNumElements();j++)
        {
            stream<<QString::number((*texcoordArray)[j].x(),'f')<<","<<QString::number((*texcoordArray)[j].y(),'f')<<endl;
        }

    }

    file.close();
}

osg::ref_ptr<osg::Group> ProjectOperation::openProject(QString projectPath)
{
    QFileInfo fileInfo = QFileInfo(projectPath);
    QFile file(projectPath+"/"+fileInfo.baseName()+".pro");
    QTextStream stream(&file);

    osg::ref_ptr<osg::Group> root=new osg::Group;
    osg::ref_ptr<osg::Switch> switchPixNode=new osg::Switch;
    osg::ref_ptr<osg::Switch> switchWellNode=new osg::Switch;
    osg::ref_ptr<osg::Switch> switchProfileNode=new osg::Switch;
    float x,y,z;
    Pix *pix = new Pix;
    Well *well = new Well;
    Profile *profile = new Profile;
    root->addChild(switchPixNode);
    root->addChild(switchWellNode);
    root->addChild(switchProfileNode);


    if (!file.open(QIODevice::ReadOnly))
         return NULL;

    while(!stream.atEnd())
    {
        QString str = stream.readLine();
        if(str=="Pix")
        {
             break;
        }

    }
    //读取勘探成果图

    int counter=0;
    while(!stream.atEnd())
    {
        QString str = stream.readLine();

        counter++;

        if(str=="Well")
            break;

        if(counter%5==1)
        {
            pix = new Pix;
            pix->setImagebyURL(projectPath+"/"+str);
            continue;
        }
        else if(counter%5==0)
        {
            QStringList list=str.split(",");
            x=list[0].toDouble();
            y=list[1].toDouble();
            z=list[2].toDouble();
            pix->setVertexOBO(x,y,z);
            osg::ref_ptr<osg::Switch> pixSwitch = new osg::Switch;
            pixSwitch->addChild(pix->getGeometry());
            switchPixNode->addChild(pixSwitch);
            continue;
        }
        else
        {
            QStringList list=str.split(",");
            x=list[0].toDouble();
            y=list[1].toDouble();
            z=list[2].toDouble();
            pix->setVertexOBO(x,y,z);
            continue;
        }
    }

    while(!stream.atEnd())
    {
        QString str = stream.readLine();
        if(str=="Profile")
            break;
        well = new Well;
        well->setWellData(projectPath+"/"+str);


        osg::ref_ptr<osg::Switch> wellSwitch = new osg::Switch;
        wellSwitch->addChild(well->getWell());
        switchWellNode->addChild(wellSwitch);
    }

    counter=0;
    while(!stream.atEnd())
    {
        QString str = stream.readLine();


        counter++;

        if(counter%9==1)
        {
            profile = new Profile;
            profile->setImagebyURL(projectPath+"/"+str);
            qDebug()<<projectPath+"/"+str;
            continue;
        }
        else if(counter%9==0)
        {
            QStringList list=str.split(",");
            x=list[0].toDouble();
            y=list[1].toDouble();

            profile->setTexCoordArrayOBO(x,y);
            osg::ref_ptr<osg::Switch> profileSwitch = new osg::Switch;
            profileSwitch->addChild(profile->getGeometry());
            switchProfileNode->addChild(profileSwitch);
            continue;
        }
        else if(counter%9>=2&&counter%9<=5)
        {
            QStringList list=str.split(",");
            x=list[0].toDouble();
            y=list[1].toDouble();
            z=list[2].toDouble();
            profile->setVertexOBO(x,y,z);
            continue;
        }
        else
        {
            QStringList list=str.split(",");
            x=list[0].toDouble();
            y=list[1].toDouble();
            profile->setTexCoordArrayOBO(x,y);
        }

    }

    file.close();
    return root;

}

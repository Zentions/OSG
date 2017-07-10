#ifndef PROJECTOPERATION_H
#define PROJECTOPERATION_H
#include <iomanip>
#include <QDir>
#include <QMessageBox>
#include <QWidget>
#include <QDebug>
#include <QDataStream>
#include <QTextStream>
#include <QFileInfo>

#include <osg/ref_ptr>
#include <osg/Group>
#include <osg/Switch>
#include <osgText/Text>

#include "pix.h"
#include "profile.h"
#include "well.h"

class ProjectOperation
{
public:
    ProjectOperation();
    static bool createFolder(QWidget*parent,QString route);
    static bool createProjectFile(QString route);
    static bool saveProject(QString projectPath,osg::ref_ptr<osg::Group> root);
    static osg::ref_ptr<osg::Group> openProject(QString projectPath);

};

#endif // PROJECTOPERATION_H

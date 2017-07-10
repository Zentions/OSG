#ifndef PIX_H
#define PIX_H
#include <QtWidgets/QGraphicsScene>
#include <QtCore/QtCore>
#include <QtGui/QtGui>
#include <QtGui/QPaintEngine>
#include <QtOpenGL/QGLWidget>

#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>

#include <osg/Node>
#include <osg/Geode>
#include <osg/Group>
#include <osg/ShapeDrawable>
#include <osg/PositionAttitudeTransform>
#include <osg/AnimationPath>
#include <osg/ClipNode>
#include <osg/MatrixTransform>
#include <osg/PolygonMode>
#include <osg/Geometry>
#include <osg/Texture2D>
#include <osg/TexGen>
#include <osg/TextureCubeMap>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgGA/StateSetManipulator>
#include <osg/BlendFunc>


class Pix
{
public:
    Pix();

    //设置图片透明度
    void settransparency();

    //取消透明度
    void removetransparency();

    //获得数据
    osg::ref_ptr<osg::Image> getImage(){return this->image;}
    osg::ref_ptr<osg::Geometry> getGeometry(){drawGeometry();return this->geometry;}
    osg::ref_ptr<osg::Vec3Array> getVertexArray(){ return this->vertexarray;}
    osg::ref_ptr<osgText::Text> getText(){ drawText();
                   return this->text;}

    //设置数据
    void setVertexArray(osg::ref_ptr<osg::Vec3Array> ver){this->vertexarray = ver;}
    void setVertexArraybyURL(QString filename);

    //设置顶点数据 ONE BY ONE
    void setVertexOBO(float x,float y,float z);

    void setImage(osg::ref_ptr<osg::Image> ima){ this->image = ima;}
    void setImagebyURL(QString filename);

private:
    osg::ref_ptr<osg::Vec3Array> vertexarray;
    osg::ref_ptr<osg::Geometry> geometry;
    osg::ref_ptr<osg::Image> image;
    osg::ref_ptr<osgText::Text> text;
    QString name;

    void drawGeometry();
    void drawText();
    void setTexCoordArray(osg::ref_ptr<osg::Geometry> geo);
};

#endif // PIX_H

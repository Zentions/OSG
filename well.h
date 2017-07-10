#ifndef WELL_H
#define WELL_H

#include "graphicsview.h"


#include <osg/BoundingBox>

#include<osg/Image>
#include<osg/TexGen>
#include<osg/Texture>
#include<osg/State>

#include <osg/Drawable>
#include <osg/Vec2>
#include <osg/Vec3>
#include <osg/Vec4>
#include <osg/Array>
#include <osg/PrimitiveSet>
#include<osgText/Text>
#include<osgText/String>
#include<osg/Node>
#include <osg/Geometry>
#include <osg/ArrayDispatchers>
#include <osg/Notify>
#include <osg/Drawable>
#include <osg/Vec2>
#include <osg/Vec3>
#include <osg/Vec4>
#include <osg/Array>
#include <osg/PrimitiveSet>

#include <string>
#include <vector>
#include<iostream>
#include<ostream>
#include <iomanip>
#include <fstream>
#include<cstring>
#include<list>
#include<sstream>

using namespace std;
class Well : public osg::Node
{
public:
    Well();
       void setWellData(QString);
       osg::ref_ptr<osg::Geometry> getWell()
       {
           return line;
       }
       osg::ref_ptr<osgText::Text> getText()
       {
           return text;
       }


/** start  Well  get() and set() */

       void setWellFileName(QString fileName);
       QString getWellFileName();

       void setWellName(QString name);
       QString getWellName();

       void setWellType(QString type);
       QString getWellType();

       void setWellHeadXYZ(osg::Vec3 HeadXYZ);
       osg::Vec3  getWellHeadXYZ();

       void setWellTrace_dataNum(int num);
       int  getWellTrace_dataNum();


       void setWellTrace_dataXYZ(osg::ref_ptr<osg::Vec3Array> dataXYZ);
       osg::ref_ptr<osg::Vec3Array> getWellTrace_dataXYZ();

       void setWellTrace_simpleDataXYZ(int index,osg::Vec3 vec3);
       osg::Vec3 getWellTrace_simpleDataXYZ();

       void setWellTraceColor(osg::ref_ptr<osg::Vec4Array> traceColor);
       osg::ref_ptr<osg::Vec4Array>  getWellTraceColor();
//导管
       void setWellPipeConduit_name(std::string conduitName);
       std::string getWellPipeConduit_name();

       void  setWellPipeConduit_outDiameter(float outDiameter);
       float getWellPipeConduit_outDiameter();

       void setWellPipeConduit_deep(float deep);
       float getWellPipeConduit_deep();

       void setWellPipeConduit_dataNum(int num);
       int  getWellPipeConduit_dataNum();

       void setWellPipeConduit_trianNum(int num);
       int  getWellPipeConduit_trianNum();

       void setWellPipeConduit_dataXYZ(QVector<osg::Vec3> dataXYZ);
       QVector<osg::Vec3>  getWellPipeConduit_dataXYZ();

       void setWellPipeConduit_trianIndex(osg::ref_ptr<osg::Vec3dArray> trianIndex);
       osg::ref_ptr<osg::Vec3dArray> getWellPipeConduit_trianIndex();

       void setWellPipeConduit_textureImage(osg::ref_ptr<osg::Image> image);
       osg::ref_ptr<osg::Image>  getWellPipeConduit_textureImage();

 //表层套管
       void setWellPipeSurfaceCasing_name(std::string surfaceName);
       std::string getWellPipeSurfaceCasing_name();

       void  setWellPipeSurfaceCasing_outDiameter(float outDiameter);
       float getWellPipeSurfaceCasing_outDiameter();

       void setWellPipeSurfaceCasing_deep(float deep);
       float getWellPipeSurfaceCasing_deep();

       void setWellPipeSurfaceCasing_dataNum(int num);
       int  getWellPipeSurfaceCasing_dataNum();

       void setWellPipeSurfaceCasing_trianNum(int num);
       int  getWellPipeSurfaceCasing_trianNum();

       void setWellPipeSurfaceCasing_dataXYZ(osg::ref_ptr<osg::Vec3Array> dataXYZ);
       osg::ref_ptr<osg::Vec3Array>  getWellPipeSurfaceCasing_dataXYZ();

       void setWellPipeSurfaceCasing_trianIndex(osg::ref_ptr<osg::Vec3dArray> trianIndex);
       osg::ref_ptr<osg::Vec3dArray> getWellPipeSurfaceCasing_trianIndex();

       void setWellPipeSurfaceCasing_textureImage(osg::ref_ptr<osg::Image> image);
       osg::ref_ptr<osg::Image>  getWellPipeSurfaceCasing_textureImage();

 //技术套管
             void setWellPipeIntermediateCasing_name(std::string intermediaName);
             std::string getWellPipeIntermediateCasing_name();

             void  setWellPipeIntermediateCasing_outDiameter(float outDiameter);
             float getWellPipeIntermediateCasing_outDiameter();

             void setWellPipeIntermediateCasing_deep(float deep);
             float getWellPipeIntermediateCasing_deep();

             void setWellPipeIntermediateCasing_dataNum(int num);
             int  getWellPipeIntermediateCasing_dataNum();

             void setWellPipeIntermediateCasing_trianNum(int num);
             int  getWellPipeIntermediateCasing_trianNum();
             void setWellPipe(osg::ref_ptr<osg::Geode>);
             osg::ref_ptr<osg::Geode>  getWellPipe();

             void setWellPipeIntermediateCasing_dataXYZ(osg::ref_ptr<osg::Vec3Array> dataXYZ);
             osg::ref_ptr<osg::Vec3Array>  getWellPipeIntermediateCasing_dataXYZ();

             void setWellPipeIntermediateCasing_trianIndex(osg::ref_ptr<osg::Vec3dArray> trianIndex);
             osg::ref_ptr<osg::Vec3dArray> getWellPipeIntermediateCasing_trianIndex();

             void setWellPipeIntermediateCasing_textureImage(osg::ref_ptr<osg::Image> image);
             osg::ref_ptr<osg::Image>  getWellPipeIntermediateCasing_textureImage();

 //光管
             void setWellPipeSmoothTube_name(std::string smoothTubeName);
             std::string getWellPipeSmoothTube_name();

             void  setWellPipeSmoothTube_outDiameter(float outDiameter);
             float getWellPipeSmoothTube_outDiameter();

             void setWellPipeSmoothTube_deep(float deep);
             float getWellPipeSmoothTube_deep();

             void setWellPipeSmoothTube_dataNum(int num);
             int  getWellPipeSmoothTube_dataNum();

             void setWellPipeSmoothTube_trianNum(int num);
             int  getWellPipeSmoothTube_trianNum();

             void setWellPipeSmoothTube_dataXYZ(osg::ref_ptr<osg::Vec3Array> dataXYZ);
             osg::ref_ptr<osg::Vec3Array>  getWellPipeSmoothTube_dataXYZ();

             void setWellPipeSmoothTube_trianIndex(osg::ref_ptr<osg::Vec3dArray> trianIndex);
             osg::ref_ptr<osg::Vec3dArray> getWellPipeSmoothTube_trianIndex();

             void setWellPipeSmoothTube_textureImage(osg::ref_ptr<osg::Image> image);
             osg::ref_ptr<osg::Image>  getWellPipeSmoothTube_textureImage();
             void setAllTexture(osg::ref_ptr<osg::Geode> geode);
             int setPartTexture(osg::ref_ptr<osg::Geode> geode,float start,float end);
             void setRepeatTexture(osg::ref_ptr<osg::Geode> geode,int m);
             int setPartRepeatTexture(osg::ref_ptr<osg::Geode> geode,int num,float start,float end);
             int Find(float X);
             int setPartsTexture(osg::ref_ptr<osg::Geode> geode,float start,float end,osg::ref_ptr<osg::Image> image);
             bool CancelTexture(osg::ref_ptr<osg::Geode> geode);
/** start  Well  get() and set() */

//读取井文件数据(井迹数据+井筒数据)
           bool  readWellData();
 //绘制井名
           osg::ref_ptr<osg::Geode>  drawWellName();
 //绘制井迹
           osg::ref_ptr<osg::Geode>  drawWellTrace();
 //绘制井筒
           osg::ref_ptr<osg::Geode>  drawWellPipe();

//用井迹数据生成对应井筒数据
           void  WellTraceToWellPipe();

   private:
       osg::ref_ptr<osg::Geometry> line;
       osg::ref_ptr<osg::Vec3Array> v;
       osg::ref_ptr<osg::Vec4Array> c;
       osg::ref_ptr<osg::Vec3Array> h;
       osg::ref_ptr<osgText::Text> text;
       osg::ref_ptr<osg::Switch> wellSwitch;
       int lineCounter=0;
       int wellCounter=0;
       double x,y,z;
       double headx,heady,headz;
       QString wellname;
       QFileInfo fileInfo;

      // std::string                            _wellFileName;//井文件名
       QString                                _wellFileName;
       QString                            _wellName;//井名
       QString                            _wellType;//井类型
       osg::Vec3                               _wellHead_XYZ;//井头坐标
       double                                  _wellHeadX;
       double                                  _wellHeadY;
       double                                  _wellHeadZ;
       int                                     _wellCount;//井的个数

       int                                    _wellTrace_dataNum;//井迹数据点个数
       osg::ref_ptr<osg::Vec3Array>           _wellTrace_dataXYZ;//井迹数据
       osg::ref_ptr<osg::Vec4Array>           _wellTrace_color;//井迹颜色

       std::string                            _wellPipeConduit_name;       //导管名称
       float                                  _wellPipeConduit_outDiameter;//井筒导管外径
       float                                  _wellPipeConduit_deep;       //井筒导管下深
       int                                    _wellPipeConduit_dataNum;//井筒导管数据点个数
       osg::ref_ptr<osg::Geode>                _WellPipe;
       QList<osg::Texture2D*>                 _WellPipeTextureList;
       int                                    _wellPipeConduit_trianNum;//组成井筒导管三角网三角形个数
       QVector<osg::Vec3>                     _wellPipeConduit_dataXYZ;//井筒导管数据点
       osg::ref_ptr<osg::Vec3dArray>          _wellPipeConduit_trianIndex;//井筒导管组成三角形三顶点对应索引值
       osg::ref_ptr<osg::Image>               _wellPipeConduit_textureImage;//井筒导管纹理映射图(.bmp)

       std::string                            _wellPipeSurfaceCasing_name;       //表层套管名称
       float                                  _wellPipeSurfaceCasing_outDiameter;//井筒表层套管外径
       float                                  _wellPipeSurfaceCasing_deep;       //井筒表层套管下深
       int                                    _wellPipeSurfaceCasing_dataNum;//井筒表层套管数据点个数
       int                                    _wellPipeSurfaceCasing_trianNum;//组成井筒表层套管三角网三角形个数
       osg::ref_ptr<osg::Vec3Array>           _wellPipeSurfaceCasing_dataXYZ;//井筒表层套管数据点
       osg::ref_ptr<osg::Vec3dArray>          _wellPipeSurfaceCasing_trianIndex;//井筒表层套管组成三角形三顶点对应索引值
       osg::ref_ptr<osg::Image>               _wellPipeSurfaceCasing_textureImage;//井筒表层套管纹理映射图(.bmp)


       std::string                            _wellPipeIntermediateCasing_name;       //技术套管名称
       float                                  _wellPipeIntermediateCasing_outDiameter;//井筒技术套管外径
       float                                  _wellPipeIntermediateCasing_deep;       //井筒技术套管下深
       int                                    _wellPipeIntermediateCasing_dataNum;//井筒技术套管数据点个数
       int                                    _wellPipeIntermediateCasing_trianNum;//组成井筒技术套管三角网三角形个数
       osg::ref_ptr<osg::Vec3Array>           _wellPipeIntermediateCasing_dataXYZ;//井筒技术套管数据点
       osg::ref_ptr<osg::Vec3dArray>          _wellPipeIntermediateCasing_trianIndex;//井筒技术套管组成三角形三顶点对应索引值
       osg::ref_ptr<osg::Image>               _wellPipeIntermediateCasing_textureImage;//井筒技术套管纹理映射图(.bmp)

       std::string                            _wellPipeSmoothTube_name;       //光管名称
       float                                  _wellPipeSmoothTube_outDiameter;//井筒光管外径
       float                                  _wellPipeSmoothTube_deep;       //井筒光管下深
       int                                    _wellPipeSmoothTube_dataNum;//井筒光管数据点个数
       int                                    _wellPipeSmoothTube_trianNum;//组成井筒光管三角网三角形个数
       osg::ref_ptr<osg::Vec3Array>           _wellPipeSmoothTube_dataXYZ;//井筒光管数据点
       osg::ref_ptr<osg::Vec3dArray>          _wellPipeSmoothTube_trianIndex;//井筒光管组成三角形三顶点对应索引值
       osg::ref_ptr<osg::Image>               _wellPipeSmoothTube_textureImage;//井筒光管纹理映射图(.bmp)
};

#endif // WELL_H

#include "pix.h"
Pix::Pix()
{
    this->geometry    = NULL;
    this->image       = NULL;
    this->vertexarray = NULL;
}
//按照路径读图，并把图片名赋值给name
void Pix::setImagebyURL(QString filename){
    this->image = osgDB::readImageFile(filename.toStdString());

    QFileInfo fileInfo = QFileInfo(filename);
    this->name = fileInfo.baseName();
}
//一次添加一个顶点，使用此函数是要注意添加顺序，按照三角带图元顺序添加
void Pix::setVertexOBO(float x, float y, float z){
    if(this->vertexarray==NULL)
        this->vertexarray = new osg::Vec3Array;
    this->vertexarray->push_back(osg::Vec3(x,y,z));
}
//按照路径读取坐标
void Pix::setVertexArraybyURL(QString filename){
    if(filename.isEmpty())
    {
        return ;
    }
    double x,y,z;


    //读文件获得坐标
    QFile *file = new QFile(filename);

    QFileInfo fileInfo = QFileInfo(filename);
    this->name = fileInfo.baseName();

    if(!file->open(QIODevice::ReadOnly|QIODevice::Text))
    {
        return;
    }
    while(!file->atEnd())
    {

        QByteArray line = file->readLine();
        QString str(line);
        QStringList list=str.split(",");
        if(list.size()==1)
        {
            //第一次读出来的是一个Z值
            z=list[0].toDouble();
            continue;
        }

        x=list[0].toDouble();
        y=list[1].toDouble();

        Pix::setVertexOBO(x,y,z);
    }


}
//按照已有的顶点、图片数据画出来几何体
void Pix::drawGeometry(){

    //创建一个几何体对象
    osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();

    //设置顶点数据
    geom->setVertexArray(this->vertexarray.get());

    //添加图元，绘图基元为多边形
    geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::TRIANGLE_STRIP,0,this->vertexarray->getNumElements()));

    Pix::setTexCoordArray(geom);


     osg::StateSet* stateset =  geom->getOrCreateStateSet();


    //load image from the file
    osg::ref_ptr<osg::Texture2D> Texture = new osg::Texture2D;
    Texture->setDataVariance(osg::Object::DYNAMIC);

    //assign the texture from the image file
    Texture->setImage(image.get());

    stateset->setTextureAttributeAndModes(0,Texture.get(),osg::StateAttribute::ON);


    osg::ref_ptr<osg::BlendFunc> blendFunc = new osg::BlendFunc();  // blend func
    blendFunc->setSource(osg::BlendFunc::SRC_ALPHA);
    blendFunc->setDestination(osg::BlendFunc::ONE_MINUS_SRC_ALPHA);
    stateset->setAttributeAndModes( blendFunc );
    stateset->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);

    this->geometry = geom;

    geom->getOrCreateStateSet()->setRenderBinDetails(-2, "RenderBin");
}
//按照已有的顶点、图片数据画出来文字
void Pix::drawText(){
    if(this->geometry==NULL)
        this->drawGeometry();
    //添加Text
    osg::ref_ptr<osgText::Text> text = new osgText::Text;
    const osg::BoundingBox &box = this->getGeometry()->getBoundingBox();//获取包围盒
    float size=(box.xMax()-box.xMin())/10;
    QString pixname =this->name;
    text->setFontResolution( 1280, 1280 );
    text->setCharacterSize( size );

   // text->setPosition( osg::Vec3( (cor[4]-X)/proH+0.5*(cor[2]-cor[0])/proH,(cor[5]-Y)/proW+(cor[1]-cor[5])/proW+size,counter)  );//暂时写死
    text->setPosition( osg::Vec3(box.xMin()+(box.xMax()-box.xMin())/2,box.yMax()+size,box.zMin() )  );//暂时写死

    text->setAxisAlignment( osgText::Text::XY_PLANE );
    text->setAlignment( osgText::Text::CENTER_TOP );
    text->setText(pixname.toStdString());

    this->text = text;
}
//给几何体设定纹理坐标
void Pix::setTexCoordArray(osg::ref_ptr<osg::Geometry> geo){


    //归一化数组处理
    osg::Vec3Array* v3a = dynamic_cast<osg::Vec3Array*>(geo->getVertexArray());
    osg::ref_ptr<osg::Vec3Array> nor_vertex = new osg::Vec3Array;
        //获取包围盒
    const osg::BoundingBox &bbox = geo->getBoundingBox();

    osg::Vec3 min,max;

    if (v3a) min.set(bbox.xMin(), bbox.yMin(), bbox.zMin());
    if (v3a) max.set(bbox.xMax(), bbox.yMax(), bbox.zMax());

    for (unsigned i=0; i<geo->getVertexArray()->getNumElements(); ++i) {

        osg::Vec3 P;
        if (v3a) P.set(((*v3a)[i].x()-min.x())/(max.x()-min.x()), ((*v3a)[i].y()-min.y())/(max.y()-min.y()), ((*v3a)[i].z()-min.z())/(max.z()-min.z()));

        nor_vertex->push_back(P);

    }

    //计算纹理坐标，把归一化的顶点数组给几何体
    v3a = nor_vertex;

    osg::ref_ptr<osg::Vec2Array> tc = new osg::Vec2Array;
    for (unsigned i=0; i<geo->getVertexArray()->getNumElements(); ++i) {

        osg::Vec3 P;

       if (v3a) P.set((*v3a)[i].x(), (*v3a)[i].y(), (*v3a)[i].z());

         osg::Vec2 uv;
       uv.set(P.x(), P.y());

        tc->push_back(uv);


        }

    geo->setTexCoordArray(0, tc);


}
//设置图片透明
void Pix::settransparency(){

    //创建颜色数组
    osg::ref_ptr<osg::Vec4Array> vc = new osg::Vec4Array();

    //添加数据
    vc->push_back(osg::Vec4(1.0f,1.0f,1.0f,0.5f));
    //设置颜色数组
    geometry->setColorArray(vc.get());
    //设置颜色数组
    geometry->setColorBinding(osg::Geometry::BIND_OVERALL);
}
//重置状态 去掉透明属性
void Pix::removetransparency(){
    //创建颜色数组
    osg::ref_ptr<osg::Vec4Array> vc = new osg::Vec4Array();
    //添加数据
    vc->push_back(osg::Vec4(1.0f,1.0f,1.0f,1.0f));
    //设置颜色数组
    geometry->setColorArray(vc.get());
    //设置颜色数组
    geometry->setColorBinding(osg::Geometry::BIND_OVERALL);
}

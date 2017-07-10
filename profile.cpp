#include "profile.h"
Profile::Profile()
{
    this->geometry    = NULL;
    this->image       = NULL;
    this->vertexarray = NULL;
}
void Profile::setImagebyURL(QString filename){
    //按照路径读图，并把图片名赋值给name
    this->image = osgDB::readImageFile(filename.toStdString());
    QFileInfo fileInfo = QFileInfo(filename);
    this->name = fileInfo.baseName();
}
//一次添加一个顶点，使用此函数是要注意添加顺序，按照三角带图元顺序添加
void Profile::setVertexOBO(float x, float y, float z){
    if(this->vertexarray==NULL)
        this->vertexarray = new osg::Vec3Array;
    this->vertexarray->push_back(osg::Vec3(x,y,z));
}
//按照路径读取坐标
void Profile::setVertexArraybyURL(QString filename){
    if(filename.isEmpty())
    {
        return ;
    }
    double x,y,zl,zh;
    int flag = 0;
    osg::Vec2Array* temp = new  osg::Vec2Array;

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
        //第一次读出来的是图片的两个Z值，有且只有两个Z值
        if(flag==0){
                   flag=1;
                   zh=list[0].toDouble();
                   zl=list[1].toDouble();
                   continue;
        }

        if(list.size()==2){
        x=list[0].toDouble();
        y=list[1].toDouble();

        Profile::setVertexOBO(x,y,zl);
        Profile::setVertexOBO(x,y,zh);
        }
        else{
            temp->push_back(osg::Vec2(list[0].toDouble(),0));
            temp->push_back(osg::Vec2(list[0].toDouble(),1));
        }
    }
    int n = temp->getNumElements();
    for(int i=0;i<n;i=i+2){
        this->setTexCoordArrayOBO((*temp)[i].x()/(*temp)[n-1].x(),0);
        this->setTexCoordArrayOBO((*temp)[i].x()/(*temp)[n-1].x(),1);
    }


}
void Profile::setTexCoordArrayOBO(float x, float y){
    if(this->texcoordarray==NULL)
        this->texcoordarray = new osg::Vec2Array;
    this->texcoordarray->push_back(osg::Vec2(x,y));
}
//按照已有的顶点、图片数据画出来几何体
void Profile::drawGeometry(){

    //创建一个几何体对象
    osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();

    //设置顶点数据
    geom->setVertexArray(this->vertexarray.get());

    //添加图元，绘图基元为多边形
    geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::TRIANGLE_STRIP,0,this->vertexarray->getNumElements()));

    geom->setTexCoordArray(0,this->texcoordarray);



    osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D;
    texture->setImage(this->getImage());
    texture->setFilter(osg::Texture::MAG_FILTER,osg::Texture::LINEAR_MIPMAP_LINEAR);
    texture->setFilter(osg::Texture::MIN_FILTER,osg::Texture::LINEAR_MIPMAP_LINEAR);
    geom->getOrCreateStateSet()->setMode(GL_DEPTH_TEST,osg::StateAttribute::ON);
    geom->getOrCreateStateSet()->setTextureAttributeAndModes(0,texture,osg::StateAttribute::ON);

    geom->getOrCreateStateSet()->setMode(GL_BLEND,osg::StateAttribute::ON);
    geom->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);

    //设置渲染优先级------级别理论上来讲 比 背景的node 靠前就行，没设置过的是-1.
    //此处设置优先级为了防止剖面图在井后面绘制，被井的颜色覆盖

    geom->getOrCreateStateSet()->setRenderBinDetails(-2, "RenderBin");


    this->geometry = geom;
}
//按照已有的顶点、图片数据画出来文字
void Profile::drawText(){
    if(this->geometry==NULL)
        this->drawGeometry();
    //添加Text
    osg::ref_ptr<osgText::Text> text = new osgText::Text;
    const osg::BoundingBox &box = this->getGeometry()->getBoundingBox();//获取包围盒
    float size=(box.xMax()-box.xMin())/10;
    QString pixname =this->name;
    text->setFontResolution( 1280, 1280 );
    text->setCharacterSize( size );

    text->setPosition( osg::Vec3(box.xMin()+(box.xMax()-box.xMin())/2,box.yMin()+(box.yMax()-box.yMin())/2,box.zMax()+size)  );//暂时写死

    text->setAxisAlignment( osgText::Text::XZ_PLANE );
    text->setAlignment( osgText::Text::CENTER_TOP );
    text->setText(pixname.toStdString());

    this->text = text;
}
//给几何体设定纹理坐标
void Profile::setTexCoordArray(osg::ref_ptr<osg::Geometry> geo){


    //从顶点数组分段获得纹理分段
    osg::Vec3Array* v3a = dynamic_cast<osg::Vec3Array*>(geo->getVertexArray());

    //存储纹理分段长度 和 总长度

    long double sum=0.0,temp=0.0;

    int n = geo->getVertexArray()->getNumElements();


    for (unsigned i=1; i<n; ++i) {
        long double a = fabs((*v3a)[i].x() - (*v3a)[i-1].x());
        long double b = fabs((*v3a)[i].y() - (*v3a)[i-1].y());
            sum = sum + sqrt(a*a+b*b);
    }

    qDebug()<<(double)sum;

    //计算纹理坐标

    osg::ref_ptr<osg::Vec2Array> tc = new osg::Vec2Array;

    tc->push_back(osg::Vec2(0,0));

    for (unsigned i=1; i<n; ++i) {

        long double a = fabs((*v3a)[i].x() - (*v3a)[i-1].x());
        long double b = fabs((*v3a)[i].y() - (*v3a)[i-1].y());
            temp = temp + sqrt(a*a+b*b);

        qDebug()<<(double)temp;

        osg::Vec2 uv;

        uv.set(temp/sum, i%2);

        tc->push_back(uv);

        }

    geo->setTexCoordArray(0, tc);


}


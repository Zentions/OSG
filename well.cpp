#include "mainwindow.h"
#include "ui_mainwindow.h"
#define PI 3.14159
#define DIVNUM 72
#define FloutDIV  72.0

Well::Well()
{
    line = new osg::Geometry;
    v=new osg::Vec3Array;
    c=new osg::Vec4Array;

    h = new osg::Vec3Array;
    text = new osgText::Text;


    //实例化各属性
    //_wellHead_XYZ=new osg::Vec3;//井头坐标
    _wellTrace_dataXYZ=new osg::Vec3Array;//井迹数据
    _wellTrace_color=new osg::Vec4Array;//井迹颜色

    _wellPipeConduit_trianIndex=new osg::Vec3dArray;//井筒导管三角形顶点索引值

    _wellPipeSurfaceCasing_dataXYZ=new osg::Vec3Array;//井筒表层套管数据点
    _wellPipeSurfaceCasing_trianIndex=new osg::Vec3dArray;//井筒表层套管三角形顶点索引值
    _wellPipeSurfaceCasing_textureImage=new osg::Image;//井筒表层套管纹理图

    _wellPipeIntermediateCasing_dataXYZ=new osg::Vec3Array;//井筒技术套管数据点
    _wellPipeIntermediateCasing_trianIndex=new osg::Vec3dArray;//井筒技术套管三角形顶点索引值
    _wellPipeIntermediateCasing_textureImage=new osg::Image;//井筒技术套管纹理图

    _wellPipeSmoothTube_dataXYZ=new osg::Vec3Array;//井筒光管数据点
    _wellPipeSmoothTube_trianIndex=new osg::Vec3dArray;//井筒光管三角形顶点索引值
    _wellPipeSmoothTube_textureImage=new osg::Image;//井筒光管纹理图
    osg::Texture2D *_WellPipeTexture = new osg::Texture2D;

    _WellPipeTexture->setFilter(osg::Texture::MIN_FILTER,osg::Texture::LINEAR);
    _WellPipeTexture->setFilter(osg::Texture::MAG_FILTER,osg::Texture::LINEAR);
    _WellPipeTexture->setWrap(osg::Texture::WRAP_S,osg::Texture::REPEAT);
    _WellPipeTexture->setWrap(osg::Texture::WRAP_T,osg::Texture::REPEAT);
    _WellPipeTextureList.append(_WellPipeTexture);
}


//start  set() and get()

/**
 * @brief Well::setWellFileName
 * @param fileName
 */
void Well::setWellFileName(QString fileName){

    _wellFileName=fileName;
}
/**
 * @brief Well::getWellFileName
 * @return
 */
QString Well::getWellFileName(){
    return _wellFileName;
}

/**
 * @brief Well::setWellName
 * @param name
 */
void Well::setWellName(QString name){
    _wellName=name;
}
/**
 * @brief Well::getWellName
 * @return
 */
QString Well::getWellName(){
    return _wellName;
}

void Well::setWellType(QString type){
    _wellType=type;
}
QString  Well::getWellType(){
    return _wellType;
}

void Well::setWellHeadXYZ(osg::Vec3 HeadXYZ){

    _wellHead_XYZ=HeadXYZ;
}

osg::Vec3 Well::getWellHeadXYZ(){
    return _wellHead_XYZ;
}

void Well::setWellTrace_dataNum(int num){

    _wellTrace_dataNum=num;
}
int Well::getWellTrace_dataNum(){
    return _wellTrace_dataNum;
}

void Well::setWellTrace_dataXYZ(osg::ref_ptr<osg::Vec3Array> dataXYZ){
    _wellTrace_dataXYZ=dataXYZ;
}
osg::ref_ptr<osg::Vec3Array>  Well::getWellTrace_dataXYZ(){
    return _wellTrace_dataXYZ;
}
void Well::setWellTrace_simpleDataXYZ(int index,osg::Vec3 vec3){
    //_wellTrace_dataXYZ->insert(index,vec3);
}
osg::Vec3  Well::getWellTrace_simpleDataXYZ(){

}
void Well::setWellPipe(osg::ref_ptr<osg::Geode> WellPipe){
    _WellPipe = WellPipe;
}
osg::ref_ptr<osg::Geode>  Well::getWellPipe(){
    return _WellPipe;
}
void Well::setWellTraceColor(osg::ref_ptr<osg::Vec4Array> traceColor){
    _wellTrace_color=traceColor;
}

osg::ref_ptr<osg::Vec4Array> Well::getWellTraceColor(){
    return _wellTrace_color;
}
//导管
void Well::setWellPipeConduit_name(std::string name){
    _wellPipeConduit_name=name;
}
std::string Well::getWellPipeConduit_name(){
    return _wellPipeConduit_name;
}

void Well::setWellPipeConduit_outDiameter(float outDiameter){
    _wellPipeConduit_outDiameter=outDiameter;
}
float  Well::getWellPipeConduit_outDiameter(){
    return _wellPipeConduit_outDiameter;
}

void Well::setWellPipeConduit_deep(float deep){
    _wellPipeConduit_deep=deep;
}
float  Well::getWellPipeConduit_deep(){
    return _wellPipeConduit_deep;
}
void Well::setWellPipeConduit_dataNum(int num){
    _wellPipeConduit_dataNum=num;
}
int Well::getWellPipeConduit_dataNum(){
    return _wellPipeConduit_dataNum;
}
void Well::setWellPipeConduit_trianNum(int num){
    _wellPipeConduit_trianNum=num;
}
int Well::getWellPipeConduit_trianNum(){
    return _wellPipeConduit_trianNum;
}
void Well::setWellPipeConduit_dataXYZ(QVector<osg::Vec3> dataXYZ){
    _wellPipeConduit_dataXYZ=dataXYZ;
}
QVector<osg::Vec3>  Well::getWellPipeConduit_dataXYZ(){
    return _wellPipeConduit_dataXYZ;
}
void Well::setWellPipeConduit_trianIndex(osg::ref_ptr<osg::Vec3dArray> trianIndex){
    _wellPipeConduit_trianIndex=trianIndex;
}
osg::ref_ptr<osg::Vec3dArray> Well::getWellPipeConduit_trianIndex(){
    return _wellPipeConduit_trianIndex;
}
void Well::setWellPipeConduit_textureImage(osg::ref_ptr<osg::Image> image){
    _wellPipeConduit_textureImage=image;
}
osg::ref_ptr<osg::Image>  Well::getWellPipeConduit_textureImage(){
    return _wellPipeConduit_textureImage;
}

//表层套管
void Well::setWellPipeSurfaceCasing_name(string name){
    _wellPipeSurfaceCasing_name=name;
}
std::string Well::getWellPipeSurfaceCasing_name(){
    return _wellPipeSurfaceCasing_name;
}

void Well::setWellPipeSurfaceCasing_outDiameter(float outDiameter){
    _wellPipeSurfaceCasing_outDiameter=outDiameter;
}
float  Well::getWellPipeSurfaceCasing_outDiameter(){
    return _wellPipeSurfaceCasing_outDiameter;
}

void Well::setWellPipeSurfaceCasing_deep(float deep){
    _wellPipeSurfaceCasing_deep=deep;
}
float  Well::getWellPipeSurfaceCasing_deep(){
    return _wellPipeSurfaceCasing_deep;
}
void Well::setWellPipeSurfaceCasing_dataNum(int num){
    _wellPipeSurfaceCasing_dataNum=num;
}
int Well::getWellPipeSurfaceCasing_dataNum(){
    return _wellPipeSurfaceCasing_dataNum;
}
void Well::setWellPipeSurfaceCasing_trianNum(int num){
    _wellPipeSurfaceCasing_trianNum=num;
}
int Well::getWellPipeSurfaceCasing_trianNum(){
    return _wellPipeSurfaceCasing_trianNum;
}
void Well::setWellPipeSurfaceCasing_dataXYZ(osg::ref_ptr<osg::Vec3Array> dataXYZ){
    _wellPipeSurfaceCasing_dataXYZ=dataXYZ;
}
osg::ref_ptr<osg::Vec3Array>  Well::getWellPipeSurfaceCasing_dataXYZ(){
    return _wellPipeSurfaceCasing_dataXYZ;
}
void Well::setWellPipeSurfaceCasing_trianIndex(osg::ref_ptr<osg::Vec3dArray> trianIndex){
    _wellPipeSurfaceCasing_trianIndex=trianIndex;
}
osg::ref_ptr<osg::Vec3dArray> Well::getWellPipeSurfaceCasing_trianIndex(){
    return _wellPipeSurfaceCasing_trianIndex;
}
void Well::setWellPipeSurfaceCasing_textureImage(osg::ref_ptr<osg::Image> image){
    _wellPipeSurfaceCasing_textureImage=image;
}
osg::ref_ptr<osg::Image>  Well::getWellPipeSurfaceCasing_textureImage(){
    return _wellPipeSurfaceCasing_textureImage;
}
//技术套管
void Well::setWellPipeIntermediateCasing_name(string name){
    _wellPipeIntermediateCasing_name=name;
}
std::string Well::getWellPipeIntermediateCasing_name(){
    return _wellPipeIntermediateCasing_name;
}

void Well::setWellPipeIntermediateCasing_outDiameter(float outDiameter){
    _wellPipeIntermediateCasing_outDiameter=outDiameter;
}
float  Well::getWellPipeIntermediateCasing_outDiameter(){
    return _wellPipeIntermediateCasing_outDiameter;
}

void Well::setWellPipeIntermediateCasing_deep(float deep){
    _wellPipeIntermediateCasing_deep=deep;
}
float  Well::getWellPipeIntermediateCasing_deep(){
    return _wellPipeIntermediateCasing_deep;
}
void Well::setWellPipeIntermediateCasing_dataNum(int num){
    _wellPipeIntermediateCasing_dataNum=num;
}
int Well::getWellPipeIntermediateCasing_dataNum(){
    return _wellPipeIntermediateCasing_dataNum;
}
void Well::setWellPipeIntermediateCasing_trianNum(int num){
    _wellPipeIntermediateCasing_trianNum=num;
}
int Well::getWellPipeIntermediateCasing_trianNum(){
    return _wellPipeIntermediateCasing_trianNum;
}
void Well::setWellPipeIntermediateCasing_dataXYZ(osg::ref_ptr<osg::Vec3Array> dataXYZ){
    _wellPipeIntermediateCasing_dataXYZ=dataXYZ;
}
osg::ref_ptr<osg::Vec3Array>  Well::getWellPipeIntermediateCasing_dataXYZ(){
    return _wellPipeIntermediateCasing_dataXYZ;
}
void Well::setWellPipeIntermediateCasing_trianIndex(osg::ref_ptr<osg::Vec3dArray> trianIndex){
    _wellPipeIntermediateCasing_trianIndex=trianIndex;
}
osg::ref_ptr<osg::Vec3dArray> Well::getWellPipeIntermediateCasing_trianIndex(){
    return _wellPipeIntermediateCasing_trianIndex;
}
void Well::setWellPipeIntermediateCasing_textureImage(osg::ref_ptr<osg::Image> image){
    _wellPipeIntermediateCasing_textureImage=image;
}
osg::ref_ptr<osg::Image>  Well::getWellPipeIntermediateCasing_textureImage(){
    return _wellPipeIntermediateCasing_textureImage;
}


//光管
void Well::setWellPipeSmoothTube_name(string name){
    _wellPipeSmoothTube_name=name;
}
std::string Well::getWellPipeSmoothTube_name(){
    return _wellPipeSmoothTube_name;
}

void Well::setWellPipeSmoothTube_outDiameter(float outDiameter){
    _wellPipeSmoothTube_outDiameter=outDiameter;
}
float  Well::getWellPipeSmoothTube_outDiameter(){
    return _wellPipeSmoothTube_outDiameter;
}

void Well::setWellPipeSmoothTube_deep(float deep){
    _wellPipeSmoothTube_deep=deep;
}
float  Well::getWellPipeSmoothTube_deep(){
    return _wellPipeSmoothTube_deep;
}
void Well::setWellPipeSmoothTube_dataNum(int num){
    _wellPipeSmoothTube_dataNum=num;
}
int Well::getWellPipeSmoothTube_dataNum(){
    return _wellPipeSmoothTube_dataNum;
}
void Well::setWellPipeSmoothTube_trianNum(int num){
    _wellPipeSmoothTube_trianNum=num;
}
int Well::getWellPipeSmoothTube_trianNum(){
    return _wellPipeSmoothTube_trianNum;
}
void Well::setWellPipeSmoothTube_dataXYZ(osg::ref_ptr<osg::Vec3Array> dataXYZ){
    _wellPipeSmoothTube_dataXYZ=dataXYZ;
}
osg::ref_ptr<osg::Vec3Array>  Well::getWellPipeSmoothTube_dataXYZ(){
    return _wellPipeSmoothTube_dataXYZ;
}
void Well::setWellPipeSmoothTube_trianIndex(osg::ref_ptr<osg::Vec3dArray> trianIndex){
    _wellPipeSmoothTube_trianIndex=trianIndex;
}
osg::ref_ptr<osg::Vec3dArray> Well::getWellPipeSmoothTube_trianIndex(){
    return _wellPipeSmoothTube_trianIndex;
}
void Well::setWellPipeSmoothTube_textureImage(osg::ref_ptr<osg::Image> image){
    _wellPipeSmoothTube_textureImage=image;
}
osg::ref_ptr<osg::Image>  Well::getWellPipeSmoothTube_textureImage(){
    return _wellPipeSmoothTube_textureImage;
}
//end set() and get()



bool Well::readWellData(){
    QString fileName;
    fileName=_wellFileName;
    if(fileName.isEmpty())
    {
        return false;
    }

    QFile file(fileName);
    QString line;//读取一行的字符型数据
    QStringList strList;//一行拆分后的数据串集合
    double x1;
    double x2;
    double y1;
    double y2;
    double z1;
    double z2;

    if(!file.open(QIODevice::ReadOnly| QIODevice::Text)){

        //打开失败的消息提示
       // QMessageBox("打开文件失败");
    }else{

        QTextStream in(&file);

        //判断是否是标准wenll文件
        line=in.readLine();
        line=line.simplified();
        strList=line.split(" ");
      if(!strList.startsWith("#WELLDATA")) {
            return false;
      }

      line=in.readLine();
      line=line.simplified();
      strList=line.split(" ");
     if(strList.startsWith("#WELLNAME")){
         _wellName=strList[1];
      }
        while(!in.atEnd()){


            line=in.readLine();
            line=line.simplified();
            strList=line.split(" ");
           if(strList.startsWith("#WELLTRACEDATA")){
               _wellTrace_dataNum=strList[1].toInt();

                int i=0;
                while(i<_wellTrace_dataNum){
                    line=in.readLine();
                    line=line.simplified();
                    strList=line.split(" ");
                    x1=strList[0].toDouble();
                    y1=strList[1].toDouble();
                    z1=strList[2].toDouble()*(-1.0f);
                    _wellTrace_dataXYZ->push_back(osg::Vec3(x1,y1,z1));
                    i++;
                }

           }else if(strList.startsWith("#WELLPIPEDATA")){
               _wellPipeConduit_dataNum=strList[1].toInt();

               int j=0;
               while(j<_wellPipeConduit_dataNum){

                   line=in.readLine();
                   line=line.simplified();
                   strList=line.split(" ");
                   x2=strList[0].toDouble();
                   y2=strList[1].toDouble();
                   z2=strList[2].toDouble()*(-1.0f);
                   _wellPipeConduit_dataXYZ.append(osg::Vec3(x2,y2,z2));
                   j++;
               }


           }

        }

    }
             return true;
}


osg::ref_ptr<osg::Geode> Well::drawWellTrace(){

    //创建一个叶节点对象
    osg::ref_ptr<osg::Geode> geode = new osg::Geode();
    //创建颜色数组
    osg::ref_ptr<osg::Vec4Array> vc = new osg::Vec4Array();
    //添加数据
    vc->push_back(osg::Vec4(0.0f,0.0f,0.0f,0.0f));
    vc->push_back(osg::Vec4(1.0f,0.0f,0.0f,0.0f));
    vc->push_back(osg::Vec4(0.0f,0.0f,0.0f,0.0f));
    vc->push_back(osg::Vec4(0.0f,0.0f,0.0f,0.0f));
    //创建法线数组
    osg::ref_ptr<osg::Vec3Array> nc = new osg::Vec3Array();
    //添加法线
    nc->push_back(osg::Vec3(0,-1.0f,0));
             //创建一个几何体对象
             osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();
         //设置顶点数据
         geom->setVertexArray(_wellTrace_dataXYZ.get());

         //设置颜色数组
         geom->setColorArray(vc.get());
         //设置颜色的绑定方式为单个顶点
         geom->setColorBinding(osg::Geometry::BIND_OVERALL);

         //设置法线数组
         geom->setNormalArray(nc.get());
         //设置法线的绑定方式为全部顶点
         geom->setNormalBinding(osg::Geometry::BIND_OVERALL);

         //添加图元，绘图基元为三角形带
         geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINE_STRIP,0,_wellTrace_dataNum));
         //添加到叶节点
         geode->addDrawable(geom.get());

    return geode;
}

osg::ref_ptr<osg::Geode> Well::drawWellPipe(){
    osg::ref_ptr<osg::Geode> geode = new osg::Geode();

    int n = _wellPipeConduit_dataXYZ.size()/72;

    for(int i=0;i<n-1;i++)
    {
        osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();

        osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array();
        osg::ref_ptr<osg::Vec2Array> vt = new osg::Vec2Array();
        osg::Vec3 a = _wellPipeConduit_dataXYZ[72*(i+1)];
        osg::Vec3 b = _wellPipeConduit_dataXYZ[72*i];
        for(int j=0;j<72;j++)
        {
             v->push_back(_wellPipeConduit_dataXYZ[72*(i+1)+j]);
             v->push_back(_wellPipeConduit_dataXYZ[72*i+j]);
        }
         v->push_back(a);
         v->push_back(b);
         vt->push_back(osg::Vec2(0.0f,0.0f));

         geom->setVertexArray(v.get());

         osg::ref_ptr<osg::Vec3Array> nc = new osg::Vec3Array();

         nc->push_back(osg::Vec3(0.0f,1.0f,0.0f));

         geom->setNormalArray(nc.get());
         geom->setTexCoordArray(0,vt.get());
         geom->setNormalBinding(osg::Geometry::BIND_OVERALL);

         geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::TRIANGLE_STRIP ,0,146));
         //VBO动态修改
         geom->setUseDisplayList(false);
         geom->setUseVertexBufferObjects(true);

         geode->addDrawable(geom.get());

     }
     return geode.get();

}
void Well::setAllTexture(osg::ref_ptr<osg::Geode> geode)
{
    _WellPipeTextureList[0]->setImage(_wellPipeConduit_textureImage);
    int n = _wellPipeConduit_dataXYZ.size()/72;
    float r = 0,rr = 0;
    for(int i =0;i<n-1;i++)//计算纹理坐标
    {
        osg::Geometry* geom = dynamic_cast<osg::Geometry*>(geode->getDrawable(i));
        osg::Vec2Array *vt = dynamic_cast<osg::Vec2Array*>(geom->getTexCoordArray(0));
        r+=1.0/n;
        float t1 = 0;
        vt->clear();
        for(int j=0;j<73;j++)
        {

             vt->push_back(osg::Vec2(t1,r));
             vt->push_back(osg::Vec2(t1,rr));
             t1+=1.0f/73;
         }
         rr = r;

         geom->getOrCreateStateSet()->setTextureAttributeAndModes(0, _WellPipeTextureList[0]);//加载纹理

         vt->dirty();

    }


}
void Well::setRepeatTexture(osg::ref_ptr<osg::Geode> geode,int m)
{
    _WellPipeTextureList[0]->setImage(_wellPipeConduit_textureImage);
    int n = _wellPipeConduit_dataXYZ.size()/72;
    float r = 0,rr = 0;
    for(int i =0;i<n-1;i++)//计算纹理坐标
    {
        osg::Geometry* geom = dynamic_cast<osg::Geometry*>(geode->getDrawable(i));
        osg::Vec2Array *vt = dynamic_cast<osg::Vec2Array*>(geom->getTexCoordArray(0));
        r+=m*1.0/n;
        float t1 = 0;
        vt->clear();
        for(int j=0;j<73;j++)
        {

             vt->push_back(osg::Vec2(t1,r));
             vt->push_back(osg::Vec2(t1,rr));
             t1+=1.0f/73;
         }
         rr = r;

         geom->getOrCreateStateSet()->setTextureAttributeAndModes(0,_WellPipeTextureList[0] );//加载纹理

         vt->dirty();

    }
}
int Well::Find(float X)//计算深度
{
    int i = 0,j = _wellTrace_dataNum -1;
    if((X>(*_wellTrace_dataXYZ)[i].z()) ||(X<(*_wellTrace_dataXYZ)[j].z())){
         return -1;
    }
    int mid;
    while(i<j)
    {
        mid = (i+j)/2;
        osg::Vec3 ve1 = (*_wellTrace_dataXYZ)[mid];
        if(X>ve1.z()) j = mid-1;
        else if(X<ve1.z())i = mid+1;
        else if(X==ve1.z()) return mid;
        if(j-i==1) return mid;
    }

}
int Well::setPartTexture(osg::ref_ptr<osg::Geode> geode,float start,float end)
{
    _WellPipeTextureList[0]->setImage(_wellPipeConduit_textureImage);
    int n = Find(start);
    int m = Find(end);
    if(n==-1 || m==-1){//计算出错返回-1
        return -1;
    }else {//计算正确返回0
        float r = 0,rr = 0;
        for(int i =0;i<_wellTrace_dataNum-1;i++)//计算纹理坐标
        {
            osg::Geometry* geom = dynamic_cast<osg::Geometry*>(geode->getDrawable(i));
            osg::Vec2Array *vt = dynamic_cast<osg::Vec2Array*>(geom->getTexCoordArray(0));
            vt->clear();
            if(i>=n && i<=m){
                r+=1.0/(m-n);
                float t1 = 0;

                for(int j=0;j<73;j++)
                {

                   vt->push_back(osg::Vec2(t1,r));
                   vt->push_back(osg::Vec2(t1,rr));
                   t1+=1.0f/73;
                 }
                 rr = r;
                 geom->getOrCreateStateSet()->setTextureAttributeAndModes(0,_WellPipeTextureList[0]);//加载纹理

            }else{
                 geom->getOrCreateStateSet()->removeTextureAttribute(0,_WellPipeTextureList[0]);//去掉纹理
            }
            vt->dirty();
        }
        return 0;
    }

}
int Well::setPartRepeatTexture(osg::ref_ptr<osg::Geode> geode,int num,float start,float end)
{
    _WellPipeTextureList[0]->setImage(_wellPipeConduit_textureImage);
    int n = Find(start);
    int m = Find(end);
    if(n==-1 || m==-1){//计算出错返回-1
        return -1;
    }else {//计算正确返回0
        float r = 0,rr = 0;
        for(int i =0;i<_wellTrace_dataNum-1;i++)//计算纹理坐标
        {
            osg::Geometry* geom = dynamic_cast<osg::Geometry*>(geode->getDrawable(i));
            osg::Vec2Array *vt = dynamic_cast<osg::Vec2Array*>(geom->getTexCoordArray(0));
            vt->clear();
            if(i>=n && i<=m){
                r+=num*1.0/(m-n);
                float t1 = 0;

                for(int j=0;j<73;j++)
                {

                   vt->push_back(osg::Vec2(t1,r));
                   vt->push_back(osg::Vec2(t1,rr));
                   t1+=1.0f/73;
                 }
                 rr = r;
                 geom->getOrCreateStateSet()->setTextureAttributeAndModes(0,_WellPipeTextureList[0]);//加载纹理

            }else{
               geom->getOrCreateStateSet()->removeTextureAttribute(0,_WellPipeTextureList[0]);//去掉纹理
            }
            vt->dirty();
        }
        return 0;
    }
}
int Well::setPartsTexture(osg::ref_ptr<osg::Geode> geode,float start,float end,osg::ref_ptr<osg::Image> image)
{
    osg::Texture2D *_WellPipeTexture = new osg::Texture2D;
    _WellPipeTexture->setImage(image);
    _WellPipeTexture->setFilter(osg::Texture::MIN_FILTER,osg::Texture::LINEAR);
    _WellPipeTexture->setFilter(osg::Texture::MAG_FILTER,osg::Texture::LINEAR);
    _WellPipeTexture->setWrap(osg::Texture::WRAP_S,osg::Texture::REPEAT);
    _WellPipeTexture->setWrap(osg::Texture::WRAP_T,osg::Texture::REPEAT);
    _WellPipeTextureList.append(_WellPipeTexture);
    int n = Find(start);
    int m = Find(end);
    if(n==-1 || m==-1){//计算出错返回-1
        return -1;
    }else {//计算正确返回0
        float r = 0,rr = 0;
        for(int i =n;i<m;i++)//计算纹理坐标
        {
            osg::Geometry* geom = dynamic_cast<osg::Geometry*>(geode->getDrawable(i));
            osg::Vec2Array *vt = dynamic_cast<osg::Vec2Array*>(geom->getTexCoordArray(0));
            vt->clear();
            r+=1.0/(m-n);
            float t1 = 0;

            for(int j=0;j<73;j++)
            {

                 vt->push_back(osg::Vec2(t1,r));
                 vt->push_back(osg::Vec2(t1,rr));
                 t1+=1.0f/73;
            }
            rr = r;
            geom->getOrCreateStateSet()->setTextureAttributeAndModes(0,_WellPipeTexture);//加载纹理
            vt->dirty();
        }
        return 0;
    }

}
bool Well::CancelTexture(osg::ref_ptr<osg::Geode> geode){
    if(geode==NULL) return false;
    for(int i =0;i<_wellTrace_dataNum-1;i++)//计算纹理坐标
    {
        osg::Geometry* geom = dynamic_cast<osg::Geometry*>(geode->getDrawable(i));
        for(int j=0;j<_WellPipeTextureList.size();j++){
            geom->getOrCreateStateSet()->removeTextureAttribute(0,_WellPipeTextureList[j]);//去掉纹理
        }

    }
    return true;
}
void Well::WellTraceToWellPipe(){


}

void Well::setWellData(QString name)
{

}



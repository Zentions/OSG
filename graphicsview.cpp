#include "graphicsview.h"
#include <QtWidgets/QGraphicsScene>
#include <QtGui/QPaintEngine>
#include <QtOpenGL/QGLWidget>

GraphicsView::GraphicsView(QWidget *parent)
{

    this->setScene(new QGraphicsScene);

    this->setParent(parent);

    init();
}

GraphicsView::~GraphicsView()
{

}

void GraphicsView::init()
{
    QGLWidget* glViewPort = new QGLWidget;
    glViewPort->setMouseTracking(true);
    glViewPort->setMaximumSize(2000, 2000);
    this->setViewport(glViewPort);
    this->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    startTimer(10);

    m_pViewer = new osgViewer::Viewer;
    m_pViewer->setCameraManipulator(new osgGA::TrackballManipulator);
    m_pViewer->addEventHandler(new osgViewer::StatsHandler);
    m_pViewer->addEventHandler(new osgGA::StateSetManipulator(m_pViewer->getCamera()->getOrCreateStateSet()));
    m_pViewer->getCamera()->setNearFarRatio(0.0000002);
    m_pViewer->getCamera()->setComputeNearFarMode(osg::CullSettings::COMPUTE_NEAR_FAR_USING_PRIMITIVES);
    m_pViewer->setUpViewerAsEmbeddedInWindow(0, 0, width(), height());

  //  m_pViewer->setSceneData(osgDB::readNodeFile("cow.osg"));
    m_pGraphicsWindow = dynamic_cast<osgViewer::GraphicsWindow*>(
        m_pViewer->getCamera()->getGraphicsContext());


}

void GraphicsView::timerEvent(QTimerEvent *event)
{
    this->scene()->update();
}

void GraphicsView::drawBackground(QPainter *painter, const QRectF& rect)
{
    if (painter->paintEngine()->type() != QPaintEngine::OpenGL2)
    {
        return;
    }
    // Save the painter state
    painter->save();
    painter->beginNativePainting();

    m_pViewer->frame();

    painter->endNativePainting();
    painter->restore();
}

void GraphicsView::setNode(osg::ref_ptr<osg::Group> group)
{
    m_pSceneData = group;
    /*//获得当前观察器的相机
    osg::ref_ptr<osg::Camera> camera = m_pViewer->getCamera();
    //获得节点的包围球
    const osg::BoundingSphere& bs = group->getBound();
    //清除它的颜色和深度缓存，
    //这意味着这个相机渲染子场景时会覆盖之前任何相机的渲染数据
    camera->setClearMask(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    //设置相机的参考坐标系，设置为ABSOLUTE_RF意味着相机的所有变换矩阵和观察/投影矩阵的设置
    //都是相对于世界坐标的不会受到上一级矩阵的影响
    camera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
     double viewDistance = 10.0*bs.radius();
    double znear = viewDistance - bs.radius();
    double zfar = viewDistance + bs.radius();
    float top = bs.radius();
    float right = bs.radius();
   camera->setProjectionMatrixAsOrtho(-right, right, -top, top,znear,zfar);

    //根据模型的中心位置，设置相机的观察矩阵。
    osg::Vec3d upDirection(0.0,1.0,0.0);
    osg::Vec3d viewDirection(0.0,0.0,1.0);
    osg::Vec3d center = bs.center();
    osg::Vec3d eyePoint = center + viewDirection*viewDistance;
    camera->setViewMatrixAsLookAt(eyePoint, center, upDirection);*/
    m_pViewer->setSceneData(m_pSceneData);

}
void GraphicsView::adjustCamera()
{
   m_pViewer->setCameraManipulator(new osgGA::TrackballManipulator);
}


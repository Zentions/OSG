#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H


#include "eventadapter.h"

class GraphicsView : public EventAdapter
{
    Q_OBJECT

public:
    GraphicsView(QWidget* parent = 0);
    ~GraphicsView();

    osgViewer::Viewer* getOSGViewer(){ return m_pViewer; }
    osg::Group* getRoot(){ return m_pSceneData; }
    void setNode(osg::ref_ptr<osg::Group> group);
    void adjustCamera();
protected:
    virtual void drawBackground(QPainter *painter, const QRectF& rect);
    virtual void timerEvent(QTimerEvent *event);

private:
    void init();

private:
    osg::ref_ptr<osg::Group> m_pSceneData;
    osg::StateSet* m_pStateSet;
    osgViewer::Viewer* m_pViewer;

};

#endif // GRAPHICSVIEW_H

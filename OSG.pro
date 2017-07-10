#-------------------------------------------------
#
# Project created by QtCreator 2016-09-06T16:31:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OSG
TEMPLATE = app
ROOT = C:\OSG\OpenSceneGraph-3.4.0

SOURCES += main.cpp\
        mainwindow.cpp \
    eventadapter.cpp \
    function.cpp \
    graphicsview.cpp \
    treeview.cpp \
    namedialog.cpp \
    menu.cpp \
    pixfoldermenu.cpp \
    wellfoldermenu.cpp \
    profilefoldermenu.cpp \
    pixitemmenu.cpp \
    wellitemmenu.cpp \
    profileitemmenu.cpp \
    projectoperation.cpp \
    pix.cpp \
    profile.cpp \
    well.cpp \
    texturedialog.cpp \
    form.cpp

HEADERS  += mainwindow.h \
    eventadapter.h \
    function.h \
    graphicsview.h \
    treeview.h \
    namedialog.h \
    menu.h \
    pixfoldermenu.h \
    wellfoldermenu.h \
    profilefoldermenu.h \
    pixitemmenu.h \
    wellitemmenu.h \
    profileitemmenu.h \
    projectoperation.h \
    pix.h \
    profile.h \
    texcoordgenerator.h \
    well.h \
    texturedialog.h \
    form.h

FORMS    += \
    mainwindow.ui \
    namedialog.ui \
    texturedialog.ui \
    form.ui \
    test.ui

INCLUDEPATH  += D:\qt\OpenSceneGraph-3.4.0\include
LIBS += D:\qt\OpenSceneGraph-3.4.0\lib\libOpenThreads.dll.a
LIBS += D:\qt\OpenSceneGraph-3.4.0\lib\libosg.dll.a
LIBS += D:\qt\OpenSceneGraph-3.4.0\lib\libosgDB.dll.a
LIBS += D:\qt\OpenSceneGraph-3.4.0\lib\libosgGA.dll.a
LIBS += D:\qt\OpenSceneGraph-3.4.0\lib\libosgUtil.dll.a
LIBS += D:\qt\OpenSceneGraph-3.4.0\lib\libosgViewer.dll.a
LIBS += D:\qt\OpenSceneGraph-3.4.0\lib\libosgQt.dll.a
LIBS += D:\qt\OpenSceneGraph-3.4.0\lib\libosgText.dll.a
QT += opengl

DISTFILES += \
    images/body part.png \
    images/Bottom view.png \
    images/color.png \
    images/Cone.png \
    images/copy.png \
    images/crack.png \
    images/cuboid.png \
    images/Cutting.png \
    images/Cylinder.png \
    images/delete.png \
    images/Drag.png \
    images/Draw boundary.png \
    images/drilling.png \
    images/Ellipsoid.png \
    images/enlarge.png \
    images/exit.png \
    images/extend.png \
    images/further.png \
    images/Generate contours.png \
    images/Geological model.png \
    images/Hide Show.png \
    images/index.png \
    images/layer.png \
    images/Light control.png \
    images/line.png \
    images/Logs.png \
    images/merge.png \
    images/move.png \
    images/Narrow.png \
    images/new.png \
    images/North view.png \
    images/Online Help.png \
    images/open.png \
    images/Outsourcing box.png \
    images/panoramic.png \
    images/Parallel projection.png \
    images/Perforation.png \
    images/Perspective projection.png \
    images/perspective.png \
    images/Pick up.png \
    images/Plan view.png \
    images/point.png \
    images/profile.png \
    images/Property superposition.png \
    images/reduction.png \
    images/Reservoir Simulation.png \
    images/Revocation.png \
    images/Ring.png \
    images/Save as.png \
    images/save.png \
    images/select.png \
    images/Sphere.png \
    images/Staff.png \
    images/straight line.png \
    images/Stratified.png \
    images/Structural map.png \
    images/surface.png \
    images/table of Contents.png \
    images/text editor.png \
    images/Thematic map.png \
    images/Unselected.png \
    images/well deviation.png \
    images/Well trajectory.png \
    images/Wellhead.png \
    images/whirl£¨alone£©.png \
    images/whirl.png \
    images/XYZ.png \
    images/Yuantong.png

RESOURCES += \
    1.qrc

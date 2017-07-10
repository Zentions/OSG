#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QDir>
#include <QTextStream>
#include <QMessageBox>
#include <QRegExp>
#include <QFileInfo>
#include <QAction>

#include <osgText/Text>
#include <osg/DrawPixels>
#include <osg/ref_ptr>
#include <osgDB/ReadFile>
#include <osgDB/ConvertUTF>
#include <osg/Vec3>
#include <osg/Vec4>
#include <osg/Geode>
#include <osgViewer/Viewer>
#include <osg/Texture2D>
#include <osg/Image>
#include <osg/StateSet>
#include <osg/StateAttribute>
#include <osg/TexGen>
#include <osg/TexEnv>
#include <osg/Geometry>
#include <osg/LineWidth>
#include <osg/Switch>
#include <osg/Point>
#include <osg/BoundingSphere>
#include <osgUtil/Optimizer>
#include <osg/PositionAttitudeTransform>
#include <osg/Quat>
#include <osg/BoundingBox>
#include <osg/AutoTransform>

#include "graphicsview.h"
#include "function.h"
#include "pixfoldermenu.h"
#include "pixitemmenu.h"
#include "wellfoldermenu.h"
#include "wellitemmenu.h"
#include "profilefoldermenu.h"
#include "profileitemmenu.h"
#include "profile.h"
#include "menu.h"
#include "well.h"
#include "projectoperation.h"
#include "namedialog.h"
#include "texturedialog.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void openFile(QString name);
    void setPosition();
private:
    Ui::MainWindow *ui;
    GraphicsView *w;
    NameDialog *nameDialog ;

    //创建场景组节点
    osg::ref_ptr<osg::Group> group;
    osg::ref_ptr<osgViewer::Viewer> viewer;
    osg::ref_ptr<osg::Switch> switchTextNode;
    osg::ref_ptr<osg::Switch> switchPixNode;
    osg::ref_ptr<osg::Switch> switchOsgNode;
    osg::ref_ptr<osg::Switch> switchWellNode;
    osg::ref_ptr<osg::Switch> switchProfileNode;
    osg::ref_ptr<osg::PositionAttitudeTransform> posNode;
    Well *well;
    //创建各类子菜单
    PixFolderMenu *pixFolderMenu;
    WellFolderMenu *wellFolderMenu;
    ProfileFolderMenu *profileFolderMenu;
    PixItemMenu *pixItemMenu;
    WellItemMenu *wellItemMenu;
    ProfileItemMenu *profileItemMenu;
    //辅助参数
    QFileInfo fileInfo;
    QString projectPath;
    QPoint temppos;
   // ProfileItemMenu *profileItemMenu;
    bool treeCreated;//判断树的父节点是否生成
    int counter;//记录第几个载入
    double proW;//实际图形与osg图形的宽度比
    double proH;//实际图形与osg图形的高度比
    double X;
    //以第一张图的左上角为相对原点
    double Y;
private slots:
    void changeState(QString,int,int,bool);
    void receveData(QString,QList<QCheckBox*>);
    void operatePixItem(QAction*);
    void operateWellItem(QAction*);
    void operateProfileItem(QAction*);
    void reCreate();
    void on_Open_a_file_triggered();

    void on_Create_a_new_file_triggered();

    void on_Close_a_new_file_triggered();

    void on_Revocation_triggered();

    void on_Restore_triggered();

    void on_table_of_Contents_triggered();

    void on_Index_triggered();

    void on_Online_Help_triggered();

    void on_Pick_up_triggered();

    void on_Drag_triggered();

    void on_extend_triggered();

    void on_merge_triggered();

    void on_delete_2_triggered();

    void on_copy_triggered();

    void on_Cutting_triggered();

    void on_Property_superposition_triggered();

    void on_Unselected_triggered();

    void on_Save_as_triggered();

    void on_save_triggered();

    void on_reduction_triggered();

    void on_whirl_alone_triggered();

    void on_whirl_triggered();

    void on_panoramic_triggered();

    void on_Bottom_view_triggered();

    void on_Parallel_projection_triggered();

    void on_Perspective_projection_triggered();

    void on_enlarge_triggered();

    void on_Narrow_triggered();

    void on_Outsourcing_box_triggered();

    void on_XYZ_triggered();

    void on_Staff_triggered();

    void on_North_view_triggered();

    void on_Wellhead_triggered();

    void on_Well_trajectory_triggered();

    void on_Logs_triggered();

    void on_Perforation_triggered();

    void on_Stratified_triggered();

    void on_Reservoir_Simulation_triggered();

    void on_Geological_model_triggered();

    void on_crack_triggered();

    void on_color_triggered();

    void on_Hide_Show_triggered();

    void on_move_triggered();

    void on_Light_control_triggered();

    void on_drilling_triggered();

    void on_profile_triggered();

    void on_well_deviation_triggered();

    void on_straight_line_triggered();

    void on_text_editor_triggered();

    void on_Draw_boundary_triggered();

    void on_Generate_contours_triggered();

    void on_layer_triggered();

    void on_Structural_map_triggered();

    void on_Thematic_map_triggered();

    void on_point_triggered();

    void on_line_triggered();

    void on_surface_triggered();

    void on_body_part_triggered();

    void on_Sphere_triggered();

    void on_cuboid_triggered();

    void on_Ellipsoid_triggered();

    void on_Cone_triggered();

    void on_Cylinder_triggered();

    void on_Yuantong_triggered();

    void on_Ring_triggered();

    void on_Pix_triggered();
    void on_Well_triggered();

    void on_treeView_customContextMenuRequested(const QPoint &pos);

    void on_Profile_triggered();
};

#endif // MAINWINDOW_H

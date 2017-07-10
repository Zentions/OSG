#ifndef NAMEDIALOG_H
#define NAMEDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QFileDialog>
#include <QDir>
#include <QDebug>

namespace Ui {
class NameDialog;
}

class NameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NameDialog(QWidget *parent = 0);
    QString getName();
    void setTypeName(QString typeName);
    ~NameDialog();

private slots:

    void on_confirmBtn_clicked();

    void on_concelBtn_clicked();



    void on_browseBtn_clicked();

    void on_fileRouteEdit_cursorPositionChanged(int arg1, int arg2);

signals:
    void sendData(QString,QList<QCheckBox*>);

private:
    Ui::NameDialog *ui;
    QList<QCheckBox*> boxList;
    void createSubFolder();
};

#endif // NAMEDIALOG_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ros.h"
#include "sensor_msgs/LaserScan.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void updateRI() ;
    void updateRN() ;
    void updateAll() ;
    void rosInit() ;
    void nodeInit() ;
    //void killall() ;
    void updatePWM() ;
    void carDecision(float _x, float _y1_1, float _y2_1, float _y1_2, float _y2_2) ;
    void subscribeLidar() ;
    void processLaserScan(const sensor_msgs::LaserScan::ConstPtr& scan) ;
    void callback(const sensor_msgs::LaserScan::ConstPtr& scan) ;



private slots:
    void on_readyCheck_clicked();

    void on_ethCheck_clicked();

    void on_killButton_clicked();

    void on_armEngine_clicked();

    void on_startLoop_clicked();

    void on_stopLoop_clicked();

    void on_goLeft_clicked() ;

    void on_goRight_clicked() ;

    void on_stopNow_clicked() ;

    void on_noCollision_clicked() ;

    void on_enoughRoom_clicked() ;

    void on_testPrint_clicked() ;

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

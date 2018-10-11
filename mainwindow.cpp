#include <mainwindow.h>
#include "ui_mainwindow.h"
#include <roscoreinit.h>
#include <rosnodeinit.h>
#include <killall.h>
#include "JHPWMPCA9685.h"
#include "hcsr04.h"
#include "ros.h"
#include "std_msgs/String.h"
#include "ros/node_handle.h"
#include "sensor_msgs/LaserScan.h"

QString ri_current = "wait...";
QString rn_current = "wait...";
PCA9685 *pca9685 = new PCA9685(0x40);

#define PWM_FULL_REVERSE 204 // 1ms/20ms * 4096
#define PWM_NEUTRAL 295      // 1.5ms/20ms * 4096
#define STEERING_NEUTRAL 279
#define PWM_FULL_FORWARD 409 // 2ms/20ms * 4096

#define STEERING_CHANNEL 0
// The ESC is plugged into the following PWM channel
#define ESC_CHANNEL 1

float currentPWM = PWM_NEUTRAL ;
int currentChannel = ESC_CHANNEL ;
int minSpeed = 310;



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    updateAll();



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateAll()
{

    ui->labelRoscoreInit->setText(ri_current) ;

    ui->labelUrgNode->setText(rn_current) ;
}

void MainWindow::rosInit()
{
    RosCoreInit();
    updateRI();
}

void MainWindow::nodeInit()
{
    RosNodeInit();
    updateRN();
}

void MainWindow::updateRI()
{
    if(ri_current == "wait...") {
        ri_current = "Ready!" ;
    }
    else {
        ri_current = "" ;
    }
    updateAll();
}

void MainWindow::updateRN()
{
    if(rn_current == "wait...") {
        rn_current = "Ready!" ;
    }
    else {
        rn_current = "wait..." ;
    }
    updateAll();
}

void MainWindow::on_readyCheck_clicked()
{
    rosInit();
}

void MainWindow::on_ethCheck_clicked()
{
    nodeInit();
}

void MainWindow::on_killButton_clicked()
{
    KillAll();
}

void MainWindow::on_armEngine_clicked()
{
    pca9685 = new PCA9685() ;
    int err = pca9685->openPCA9685();
    if (err < 0){
        printf("Error: %d", pca9685->error);
    }
    printf("PCA9685 Device Address: 0x%02X\n",pca9685->kI2CAddress) ;
    pca9685->setAllPWM(0,0) ;
    pca9685->reset() ;
    pca9685->setPWMFrequency(50) ;
    // Set the PWM to "neutral" (1.5ms)
    sleep(1) ;
    pca9685->setPWM(ESC_CHANNEL,0,PWM_NEUTRAL);
    pca9685->setPWM(STEERING_CHANNEL,0,STEERING_NEUTRAL);
    currentPWM = PWM_NEUTRAL ;
    updatePWM() ;
    currentChannel=ESC_CHANNEL ;
}

void MainWindow::updatePWM()
{
    pca9685->setPWM(currentChannel,0,currentPWM) ;

}

void MainWindow::on_stopLoop_clicked()
{
    currentChannel = ESC_CHANNEL;
    currentPWM = PWM_NEUTRAL ;
    updatePWM() ;
}

void MainWindow::on_startLoop_clicked()
{
    currentChannel = ESC_CHANNEL;
    currentPWM = minSpeed;
    updatePWM() ;
}

void MainWindow::on_stopNow_clicked()
{
    float _x = 0.9;
    float _y1_1 = 0.2;
    float _y2_1 = -0.2;
    float _y1_2 = 1;
    float _y2_2 = -1;

    carDecision(_x, _y1_1, _y2_1, _y1_2, _y2_2);
}

void MainWindow::on_goLeft_clicked()
{
    float _x = 0.9;
    float _y1_1 = 0.2;
    float _y2_1 = -0.2;
    float _y1_2 = 2;
    float _y2_2 = -1;

    carDecision(_x, _y1_1, _y2_1, _y1_2, _y2_2);
}

void MainWindow::on_goRight_clicked()
{
    float _x = 0.9;
    float _y1_1 = 0.2;
    float _y2_1 = -0.2;
    float _y1_2 = 1;
    float _y2_2 = -2;

    carDecision(_x, _y1_1, _y2_1, _y1_2, _y2_2);
}

void MainWindow::on_noCollision_clicked()
{
    float _x = 2;
    float _y1_1 = 0.2;
    float _y2_1 = -0.2;
    float _y1_2 = 1;
    float _y2_2 = -2;

    carDecision(_x, _y1_1, _y2_1, _y1_2, _y2_2);
}

void MainWindow::on_enoughRoom_clicked()
{
    float _x = 0.5;
    float _y1_1 = 0.5;
    float _y2_1 = -0.5;
    float _y1_2 = 1;
    float _y2_2 = -2;

    carDecision(_x, _y1_1, _y2_1, _y1_2, _y2_2);
}


void MainWindow::carDecision(float _x, float _y1_1, float _y2_1, float _y1_2, float _y2_2)
{
    float wallAhead = 1 ;
    float leftMargin = 0.3;
    float rightMargin = -0.3;
    float leftWall = 1.3 ;
    float rightWall = -1.3 ;

    if(_x < wallAhead) {
        if((_y1_1 < leftMargin && _y1_1 > 0) && (_y2_1 > rightMargin && _y2_1 < 0)) {
            currentChannel = ESC_CHANNEL ;
            currentPWM = PWM_NEUTRAL ;
            updatePWM();
            sleep(1);

            if(_y1_2 > leftWall) {
                /* go left */
                currentChannel = STEERING_CHANNEL;
                currentPWM = STEERING_NEUTRAL ;
                updatePWM();

                for(int i = 0; i < 7; i++) {
                    currentPWM ++;
                    currentPWM ++;
                    currentPWM ++;
                    currentPWM ++;
                    currentPWM ++;
                    currentPWM ++;
                    updatePWM();
                    sleep(0.5);
                }

                //sleep(1);

                currentChannel = ESC_CHANNEL ;
                currentPWM = minSpeed;
                updatePWM() ;

                sleep(2);

                currentChannel = ESC_CHANNEL ;
                currentPWM = PWM_NEUTRAL ;
                updatePWM();

                //sleep(1);

                currentChannel = STEERING_CHANNEL;
                for(int i = 0; i < 7; i++) {
                    currentPWM --;
                    currentPWM --;
                    currentPWM --;
                    currentPWM --;
                    currentPWM --;
                    currentPWM --;
                    updatePWM();
                    sleep(0.5);
                }

                currentPWM = STEERING_NEUTRAL ;
                updatePWM();

                //sleep(1);

                currentChannel = ESC_CHANNEL ;
                currentPWM = minSpeed;
                updatePWM() ;
            }
            else if (_y2_2 < rightWall) {
                /* go right */
                currentChannel = STEERING_CHANNEL;
                currentPWM = STEERING_NEUTRAL ;
                updatePWM() ;

                for(int i = 0; i < 7; i++) {
                    currentPWM --;
                    currentPWM --;
                    currentPWM --;
                    currentPWM --;
                    currentPWM --;
                    currentPWM --;
                    updatePWM();
                    sleep(0.5);
                }

                //sleep(1);

                currentChannel = ESC_CHANNEL ;
                currentPWM = minSpeed;
                updatePWM() ;

                sleep(2);

                currentChannel = ESC_CHANNEL ;
                currentPWM = PWM_NEUTRAL ;
                updatePWM();

                //sleep(1);

                currentChannel = STEERING_CHANNEL;
                for(int i = 0; i < 7; i++) {
                    currentPWM ++;
                    currentPWM ++;
                    currentPWM ++;
                    currentPWM ++;
                    currentPWM ++;
                    currentPWM ++;
                    updatePWM();
                    sleep(0.5);
                }
                currentPWM = STEERING_NEUTRAL ;
                updatePWM();

                //sleep(1);

                currentChannel = ESC_CHANNEL ;
                currentPWM = minSpeed;
                updatePWM() ;
            }
            else {
                currentChannel = ESC_CHANNEL ;
                currentPWM = PWM_NEUTRAL ;
                updatePWM();
            }
        }
        else {
            currentChannel = ESC_CHANNEL ;
            currentPWM = PWM_NEUTRAL;
            updatePWM() ;

            sleep(1);

            currentChannel = ESC_CHANNEL ;
            currentPWM = minSpeed;
            updatePWM() ;
        }
    }
}

/*void MainWindow::subscribeLidar()
{
    sensor_msgs::LaserScan ls;
    float xs[5] ;
    for(int i = 0; i < 5; i++) {
        xs[i] = i;
    }

    for(int i = 0; i < 5; i++) {
        printf("%f\n", xs[i]);
    }

}
*/

void MainWindow::on_testPrint_clicked()
{

}

void MainWindow::subscribeLidar()
{


    ros::NodeHandle nh;
    //ros::Subscriber scanSub;

    //scanSub = nh.subscribe<sensor_msgs::LaserScan>("/scan",10,processLaserScan,this);

    //scanSub = nh.subscribe<sensor_msgs::LaserScan>("/scan", 1, &MainWindow::processLaserScan, this);

    ros::Subscriber sub = nh.subscribe("/scan", 1, &MainWindow::callback, this);

}

void MainWindow::callback(const sensor_msgs::LaserScan::ConstPtr& str)
{

}

/*
void MainWindow::processLaserScan(const sensor_msgs::LaserScan::ConstPtr& scan){
     //scan->ranges[] are laser readings
    printf("%f", scan->ranges[0]);
}
*/


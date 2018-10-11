#include "mainwindow.h"
#include <time.h>
#include <QApplication>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <roscoreinit.h>
#include "ros/ros.h"
#include "ros/init.h"
#include "sensor_msgs/LaserScan.h"

using namespace std;

void laserCallBack(const sensor_msgs::LaserScan::ConstPtr & msg) {
   
    for(int i = 0; i  < 2; i++) {
        printf("%f", msg->ranges[i]);
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    ros::init(argc, argv, "main");
    
    //ros::NodeHandle n;
    //ros::Subscriber laser_sub = n.subscribe("scan", 5, laserCallBack);
    //ros::Subscriber laser_sub = n.subscribe()
    return a.exec();
}

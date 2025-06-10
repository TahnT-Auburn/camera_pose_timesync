#ifndef CAMERA_POSE_TIMESYNC_NODE_HPP
#define CAMERA_POSE_TIMESYNC_NODE_HPP

#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <nav_msgs/Odometry.h>
#include <sensor_msgs/Imu.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/CompressedImage.h>

#include <camera_pose_timesync/CombinedImagePose.h>
#include <j1939can/SteerAngle.h>
#include <j1939can/VehicleSpeed.h>

#include <string>

class CameraPoseTimesyncNode
{
    private:
    ros::NodeHandle n;

    ros::Subscriber image_sub1;
    ros::Subscriber image_sub2;
    ros::Subscriber image_sub3;
    ros::Subscriber odom_sub1;
    ros::Subscriber odom_sub2;
    ros::Subscriber imu_sub1;
    ros::Subscriber steer_sub;
    ros::Subscriber vel_sub;
    // ros::Subscriber imu_sub2;

    ros::Publisher pub;

    bool recv_image_1;
    bool recv_image_2;
    bool recv_image_3;
    bool recv_odom_1;
    bool recv_odom_2;
    bool recv_imu_1;
    bool recv_steer;
    bool recv_vel;
    // bool recv_imu_2;

    camera_pose_timesync::CombinedImagePose output_msg;
    
    void image1Callback(const sensor_msgs::CompressedImage::ConstPtr &msg);
    void image2Callback(const sensor_msgs::CompressedImage::ConstPtr &msg);
    void image3Callback(const sensor_msgs::CompressedImage::ConstPtr &msg);
    void odom1Callback(const nav_msgs::Odometry::ConstPtr &msg);
    void odom2Callback(const nav_msgs::Odometry::ConstPtr &msg);
    void imu1Callback(const sensor_msgs::Imu::ConstPtr &msg);
    void steerCallback(const j1939can::SteerAngle::ConstPtr &msg);
    void velCallback(const j1939can::VehicleSpeed::ConstPtr &msg);
    // void imu2Callback(const sensor_msgs::Imu::ConstPtr &msg);

    void publishData();

    public:
    CameraPoseTimesyncNode();
    ~CameraPoseTimesyncNode();
};



#endif
#include "camera_pose_timesync/camera_pose_timesync_node.hpp"

CameraPoseTimesyncNode::CameraPoseTimesyncNode()
{
    this->recv_image_1 = false;
    this->recv_image_2 = false;
    this->recv_odom_1 = false;
    this->recv_odom_2 = false;
    this->recv_imu_1 = false;
    this->recv_imu_2 = false;

    this->n = ros::NodeHandle("~");

    std::string image_topic_1;
    std::string image_topic_2;
    std::string odom_topic_1;
    std::string odom_topic_2;
    std::string imu_topic_1;
    std::string imu_topic_2;
    std::string output_topic;

    this->n.param<std::string>("image_topic_1", image_topic_1, "image_topic_1");
    this->n.param<std::string>("image_topic_2", image_topic_2, "image_topic_2");
    this->n.param<std::string>("odom_topic_1", odom_topic_1, "odom_topic_1");
    this->n.param<std::string>("odom_topic_2", odom_topic_2, "odom_topic_2");
    this->n.param<std::string>("imu_topic_1", imu_topic_1, "imu_topic_1");
    this->n.param<std::string>("imu_topic_2", imu_topic_2, "imu_topic_2");
    this->n.param<std::string>("output_topic", output_topic, "output_topic");)

    this->image_sub1 = this->n.subscribe(image_topic_1, 1, &CameraPoseTimesyncNode::image1Callback, this);
    this->image_sub2 = this->n.subscribe(image_topic_2, 1, &CameraPoseTimesyncNode::image2Callback, this);
    this->odom_sub1 = this->n.subscribe(odom_topic_1, 1, &CameraPoseTimesyncNode::odom1Callback, this);
    this->odom_sub2 = this->n.subscribe(odom_topic_2, 1, &CameraPoseTimesyncNode::odom2Callback, this);
    this->imu_sub1 = this->n.subscribe(imu_topic_1, 1, &CameraPoseTimesyncNode::imu1Callback, this);
    this->imu_sub2 = this->n.subscribe(imu_topic_2, 1, &CameraPoseTimesyncNode::imu2Callback, this);
}

CameraPoseTimesyncNode::~CameraPoseTimesyncNode()
{
    // Do Nothing
}

void CameraPoseTimesyncNode::image1Callback(const sensor_msgs::Image::ConstPtr &msg)
{
    recv_image_1 = true;
    output_msg.camera_1 = *msg;

    publishData();
}

void CameraPoseTimesyncNode::image2Callback(const sensor_msgs::Image::ConstPtr &msg)
{
    recv_image_2 = true;
    output_msg.camera_2 = *msg;

    publishData();
}

void CameraPoseTimesyncNode::odom1Callback(const nav_msgs::Odometry::ConstPtr &msg)
{
    recv_odom_1 = true;
    output_msg.odom_1 = *msg;

    publishData();
}

void CameraPoseTimesyncNode::odom2Callback(const nav_msgs::Odometry::ConstPtr &msg)
{
    recv_odom_2 = true;
    output_msg.odom_2 = *msg;

    publishData();
}

void CameraPoseTimesyncNode::imu1Callback(const sensor_msgs::Imu::ConstPtr &msg)
{
    recv_imu_1 = true;
    output_msg.imu_1 = *msg;

    publishData();
}

void CameraPoseTimesyncNode::imu2Callback(const sensor_msgs::Imu::ConstPtr &msg)
{
    recv_imu_2 = true;
    output_msg.imu_2 = *msg;

    publishData();
}

void CameraPoseTimesyncNode::publishData()
{
    if (recv_imu_1 && recv_imu_2 && recv_odom_1 && recv_odom_2 && recv_image_1 && recv_image_2)
    {
        recv_image_1 = false;
        recv_image_2 = false;
        recv_odom_1 = false;
        recv_odom_2 = false;
        recv_imu_1 = false;
        recv_imu_2 = false;

        output_msg.header.stamp = ros::Time::now();
        pub.publish(output_msg);
    }
}
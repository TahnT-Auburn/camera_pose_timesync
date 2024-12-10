#include "camera_pose_timesync/camera_pose_timesync_node.hpp"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "camera_pose_timesync");
    CameraPoseTimesyncNode node;
    ros::spin();

    return 0;   
}
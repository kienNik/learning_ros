#include <geometry_msgs/TransformStamped.h>
#include <ros/ros.h>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2_ros/static_transform_broadcaster.h>
#include <tf2_ros/transform_broadcaster.h>

#include <iostream>

int main(int argc, char* argv[])
{
    ros::init(argc, argv, "tf2_broadcast");

    double x = 0.0;
    double y = 0.0;
    double yaw = 0.0;

    tf2_ros::TransformBroadcaster broadcaster;
    geometry_msgs::TransformStamped transform;

    transform.header.frame_id = "base_footprint";
    transform.header.stamp = ros::Time::now();
    transform.child_frame_id = "map_docking";

    transform.transform.translation.x = x;
    transform.transform.translation.y = y;

    tf2::Quaternion quat;
    quat.setRPY(0.0, 0.0, yaw);
    transform.transform.rotation.w = quat.w();
    transform.transform.rotation.x = quat.x();
    transform.transform.rotation.y = quat.y();
    transform.transform.rotation.z = quat.z();

    ROS_INFO("Sending transform");

    while (ros::ok()) {
        transform.header.stamp = ros::Time::now();
        broadcaster.sendTransform(transform);
        ros::Rate(1.0).sleep();
    }

    return 0;
}

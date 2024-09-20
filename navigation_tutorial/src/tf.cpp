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
    double z = 0.5;
    double yaw = 0.0;

    tf2_ros::TransformBroadcaster broadcaster;
    geometry_msgs::TransformStamped transform;

    transform.header.frame_id = "base_link";
    transform.header.stamp = ros::Time::now();
    transform.child_frame_id = "lidar";

    transform.transform.translation.x = x;
    transform.transform.translation.y = y;

    tf2::Quaternion quat;
    quat.setRPY(0.0, 0.0, yaw);
    transform.transform.translation.z = z;
    transform.transform.rotation.w = quat.w();
    transform.transform.rotation.x = quat.x();
    transform.transform.rotation.y = quat.y();
    transform.transform.rotation.z = quat.z();

    double x_cam3d = 0.0;
    double y_cam3d = 0.0;
    double z_cam3d = 0.2;
    double yaw_cam3d = 0.0;

    tf2_ros::TransformBroadcaster broadcaster_cam3d;
    geometry_msgs::TransformStamped transform_cam3d;

    transform_cam3d.header.frame_id = "base_link";
    transform_cam3d.header.stamp = ros::Time::now();
    transform_cam3d.child_frame_id = "cam3d";

    transform_cam3d.transform.translation.x = x;
    transform_cam3d.transform.translation.y = y;

    tf2::Quaternion quat_cam3d;
    quat_cam3d.setRPY(0.0, 0.0, yaw_cam3d);
    transform_cam3d.transform.translation.z = z_cam3d;
    transform_cam3d.transform.rotation.w = quat_cam3d.w();
    transform_cam3d.transform.rotation.x = quat_cam3d.x();
    transform_cam3d.transform.rotation.y = quat_cam3d.y();
    transform_cam3d.transform.rotation.z = quat_cam3d.z();

    ROS_INFO("Sending transform");

    while (ros::ok()) {
        transform.header.stamp = ros::Time::now();
        transform_cam3d.header.stamp = ros::Time::now();
        broadcaster.sendTransform(transform);
        broadcaster_cam3d.sendTransform(transform_cam3d);
        ros::Rate(1.0).sleep();
    }

    return 0;
}

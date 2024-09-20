#include <dynamic_config_tutorial/FootprintConfig.h>
#include <dynamic_reconfigure/server.h>
#include <ros/ros.h>

void callback(dynamic_config_tutorial::FootprintConfig& config, uint32_t level)
{
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "dynamic_config_server");

    ros::NodeHandle nh_1;
    // ros::NodeHandle nh_2("without_load");

    dynamic_reconfigure::Server<dynamic_config_tutorial::FootprintConfig> server1(nh_1);
    // dynamic_reconfigure::Server<dynamic_config_tutorial::FootprintConfig> server2(nh_2);

    dynamic_reconfigure::Server<dynamic_config_tutorial::FootprintConfig>::CallbackType f;

    f = boost::bind(&callback, _1, _2);
    server1.setCallback(f);
    // server2.setCallback(f);

    ROS_INFO("Spinning node");
    ros::spin();
    return 0;
}
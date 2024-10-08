#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <actionlib_tutorials/AveragingAction.h>
#include <ros/ros.h>

#include <boost/thread.hpp>
#include <thread>

void spinThread()
{
    ROS_WARN("thread1 start");
    while (ros::ok()) {
        ROS_INFO_THROTTLE(1.0, "thread1");
    }
    ROS_WARN("thread1 end");
}

void spinThread2()
{
    ROS_WARN("thread2 start");
    while (ros::ok()) {
        ROS_INFO_THROTTLE(1.0, "thread2");
    }
    ROS_WARN("thread2 end");
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "test_averaging");

    // create the action client
    actionlib::SimpleActionClient<actionlib_tutorials::AveragingAction> ac("averaging", true);
    std::thread spin_thread(&spinThread);
    std::thread spin_thread2(&spinThread2);

    ROS_INFO("Waiting for action server to start.");
    ac.waitForServer();

    ROS_INFO("Action server started, sending goal.");
    // send a goal to the action
    actionlib_tutorials::AveragingGoal goal;
    goal.samples = 100;
    ac.sendGoal(goal);

    // wait for the action to return
    bool finished_before_timeout = ac.waitForResult(ros::Duration(30.0));

    if (finished_before_timeout) {
        actionlib::SimpleClientGoalState state = ac.getState();
        ROS_INFO("Action finished: %s", state.toString().c_str());
    } else
        ROS_INFO("Action did not finish before the time out.");

    // shutdown the node and join the thread back before exiting
    ros::shutdown();
    spin_thread.join();
    spin_thread2.join();

    // exit
    return 0;
}
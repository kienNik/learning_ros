#include <geometry_msgs/Point.h>
#include <ros/ros.h>
#include <tf2/LinearMath/Matrix3x3.h>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2/LinearMath/Transform.h>
#include <tf2/LinearMath/Vector3.h>
#include <tf2/utils.h>

#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
    ros::init(argc, argv, "tf2_tutorial");

    double x_V = 1.0;
    double y_V = 2.0;
    double theta_V = 0;

    // V to O transform
    tf2::Vector3 translation(x_V, y_V, 0.0);
    tf2::Quaternion rotation;
    rotation.setRPY(0.0, 0.0, theta_V);

    tf2::Transform transform_V_to_O(rotation, translation);

    // O to V transform
    auto transform_O_to_V = transform_V_to_O.inverse();

    auto x_O = transform_O_to_V.getOrigin().x();
    auto y_O = transform_O_to_V.getOrigin().y();
    auto theta_O = tf2::getYaw(transform_O_to_V.getRotation());

    cout << x_O << " " << y_O << " " << theta_O / M_PI * 180 << endl;

    x_O = -x_V * cos(theta_V) - y_V * sin(theta_V);
    y_O = x_V * sin(theta_V) - y_V * cos(theta_V);
    theta_O = -theta_V;
    cout << x_O << " " << y_O << " " << theta_O / M_PI * 180 << endl;

    return 0;
}

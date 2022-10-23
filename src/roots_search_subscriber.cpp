#include <ros/ros.h>
#include "std_msgs/Float32MultiArray.h"
#include <ros/console.h>
#include <string>

ros::Subscriber roots_subscriber;

std::string input_topic_name;

void roots_callback(const std_msgs::Float32MultiArray & msg) {
    int  i = 1;
    std::string result;
    if (msg.data.empty()) {
        result = "There are no roots ";
    }
    for (auto it = msg.data.begin(); it != msg.data.end(); it++) {
        result += " x" + std::to_string(i) + " = " + std::to_string(*it) + ",";
        i++;
    }
    result.erase(result.length() - 1);
    ROS_INFO_STREAM(result);
}

int main (int argc, char **argv) {
    ros::init(argc, argv, "get_roots");
    ros::NodeHandle nh;
    nh.param<std::string>("input_roots_topic", input_topic_name, "roots");

    roots_subscriber = nh.subscribe(input_topic_name,1,roots_callback);

    ros::spin();
    return 0;
}
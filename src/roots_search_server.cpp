#include <ros/ros.h>
#include <roots_search/GetRoots.h>
#include <cmath>

ros::Publisher roots_publisher;

std::string output_topic_name;

bool get_roots(roots_search::GetRoots::Request &req,
               roots_search::GetRoots::Response &resp) {
  int discriminant = pow(req.b, 2.0) - 4*req.a*req.c;
  if (discriminant < 0) {
    resp.answer.data.clear();
  } else if (discriminant == 0) {
    resp.answer.data.push_back((-req.b) / (2 * req.a));
  } else {
    resp.answer.data.push_back(((-req.b) + sqrt(discriminant)) / (2 * req.a));
    resp.answer.data.push_back(((-req.b) - sqrt(discriminant)) / (2 * req.a));
  }
  roots_publisher.publish(resp.answer);
  return 1;
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "get_roots_server");
  ros::NodeHandle n;
  n.param<std::string>("outpit_roots_topic", output_topic_name, "roots");

  roots_publisher = n.advertise<std_msgs::Float32MultiArray>(output_topic_name, 1);

  ros::ServiceServer service = n.advertiseService("get_roots", get_roots);
  ros::spin();

  return 0;
}
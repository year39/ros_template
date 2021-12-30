#include "rclcpp/rclcpp.hpp"
#include "ros_template/pub.hpp"

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Pub>());
  rclcpp::shutdown();
  return 0;
}

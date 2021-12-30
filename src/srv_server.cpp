
#include "rclcpp/rclcpp.hpp"
#include "ros_template/srv/detail/trigger__struct.hpp"
#include "ros_template/srv/trigger.hpp"
#include <memory>

using Trig = ros_template::srv::Trigger;

void trigger_callback(
    std::shared_ptr<ros_template::srv::Trigger::Request> req,
    std::shared_ptr<ros_template::srv::Trigger::Response> res) {
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "trigger_callback");
  res->status = req->code + 10;
}

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("srv_server");
  auto service = node->create_service<ros_template::srv::Trigger>(
      "trigger", &trigger_callback);

  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Service ready");
  rclcpp::spin(node);
  rclcpp::shutdown();

  return 0;
}

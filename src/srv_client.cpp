
#include "rclcpp/rclcpp.hpp"
#include "ros_template/srv/trigger.hpp"
#include <chrono>
#include <rclcpp/executors.hpp>

using namespace std::chrono_literals;

int main(int argc, char** argv) {
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("srv_client");
  auto client = node->create_client<ros_template::srv::Trigger>("trigger");
  auto req = std::make_shared<ros_template::srv::Trigger::Request>();
  req->code = 10;

  while(!client->wait_for_service(1s)) {
    if(!rclcpp::ok()) {
      RCLCPP_ERROR(node->get_logger(), "rclcpp not ok");
      return 0;
    }
  }

  auto result = client->async_send_request(req);
  if(rclcpp::spin_until_future_complete(node, result) == rclcpp::executor::FutureReturnCode::SUCCESS) {
    RCLCPP_INFO(node->get_logger(), "result: %d", result.get()->status);
  } else {
    RCLCPP_INFO(node->get_logger(), "Failed to call service");
  }

  rclcpp::shutdown();
  return 0;
}

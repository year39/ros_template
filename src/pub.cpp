#include "ros_template/pub.hpp"
#include <chrono>
#include <memory>

using namespace std::chrono_literals;

Pub::Pub() : Node("min_pub") {
  count = 0;
  pub = this->create_publisher<std_msgs::msg::String>("min_pub", 10);
  pub_info = this->create_publisher<ros_template::msg::Info>("info_pub", 1);
  timer = this->create_wall_timer(500ms, std::bind(&Pub::timer_callback, this));
}

void Pub::timer_callback() {
  auto msg = std_msgs::msg::String();
  this->count++;
  RCLCPP_INFO(this->get_logger(), "Publishing %d", this->count);
  msg.data = "Hello " + std::to_string(this->count);
  pub->publish(msg);

  {
    auto info = ros_template::msg::Info();
    info.info = "Hello " + std::to_string(this->count);
    info.id = this->count;
    pub_info->publish(info);
  }
}

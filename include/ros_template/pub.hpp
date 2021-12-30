#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "ros_template/msg/info.hpp"

class Pub : public rclcpp::Node {
public:
  Pub();

private:
  void timer_callback();
  size_t count;
  rclcpp::TimerBase::SharedPtr timer;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr pub;
  rclcpp::Publisher<ros_template::msg::Info>::SharedPtr pub_info;
};

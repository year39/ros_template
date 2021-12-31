#include "rclcpp/rclcpp.hpp"
#include <string>
#include <chrono>

using namespace std::chrono_literals;

class Parameters : public rclcpp::Node {
public:
  Parameters() : rclcpp::Node("parameters") {
    this->declare_parameter<std::string>("msg_parameter", "this is the parameter's value");
    timer = this->create_wall_timer(1s, std::bind(&Parameters::timer_callback, this));
  }

private:
  void timer_callback() {
    std::string val;
    this->get_parameter("msg_parameter", val);
    RCLCPP_INFO(this->get_logger(), "Parameter's value: %s", val.c_str());
  }

  rclcpp::TimerBase::SharedPtr timer;
};

int main(int argc, char** argv) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Parameters>());
  rclcpp::shutdown();

  return 0;
}

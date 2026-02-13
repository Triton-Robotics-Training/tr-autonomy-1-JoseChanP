#include "spin_sol.h"

using namespace std::chrono_literals;
int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<SpinSolution>());
  rclcpp::shutdown();
  return 0;
}

//your code here
SpinSolution::SpinSolution() : Node("spinsolution") {
  current_pos_ = {0.0, 0.0};
  current_vel_ = {0.0, 0.0};
  last_update_time_ = this->now();
  pos_subscription_ = this->create_subscription<ArrayMsg>("measuredpos", 10, std::bind(&SpinSolution::pos_callback, this, std::placeholders::_1));

  vel_subscription_ = this->create_subscription<ArrayMsg>("measuredvel", 10, std::bind(&SpinSolution::vel_callback, this, std::placeholders::_1));
  
  publisher_ = this->create_publisher<ArrayMsg>("predictedpos", 10);

  timer_ = this->create_wall_timer(50ms, std::bind(&SpinSolution::timer_callback, this));
}

void SpinSolution::pos_callback(const ArrayMsg::SharedPtr msg) {
  current_pos_ = msg->data;
}

void SpinSolution::vel_callback(const ArrayMsg::SharedPtr msg) {
current_vel_ = msg->data;
}

void SpinSolution::timer_callback() {
  rclcpp::Time now = this->now();
  double dt = (now - last_update_time_).seconds();
  last_update_time_ = now;

  current_pos_[0] += current_vel_[0] * dt;
  current_pos_[1] += current_vel_[1] * dt;
  ArrayMsg msg;
  msg.data = current_pos_;
  publisher_->publish(msg);
}

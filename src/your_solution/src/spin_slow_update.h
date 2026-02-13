#ifndef YOUR_SOLUTION_SRC_SPIN_SLOW_UPDATE_H_
#define YOUR_SOLUTION_SRC_SPIN_SLOW_UPDATE_H_

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"
using ArrayMsg = std_msgs::msg::Float64MultiArray;

class SlowSolution : public rclcpp::Node {
 public:
  SlowSolution();
 private:
  void topic_callback(const ArrayMsg::SharedPtr msg);
  rclcpp::Subscription<ArrayMsg>::SharedPtr subscription_;
  rclcpp::Publisher<ArrayMsg>::SharedPtr publisher_;
};

#endif //YOUR_SOLUTION_SRC_SPIN_SLOW_UPDATE_H_

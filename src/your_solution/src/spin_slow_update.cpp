#include "spin_slow_update.h"

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<SlowSolution>());
  rclcpp::shutdown();
  return 0;
}


SlowSolution::SlowSolution() : Node("slowsolution") {
  subscription_ = this->create_subscription<ArrayMsg>("measuredpos", 10, std::bind(&SlowSolution::topic_callback, this,std::placeholders::_1));
  publisher_ =this->create_publisher<ArrayMsg>("predictedpos", 10);
}  
  // your code here
void SlowSolution::topic_callback(const ArrayMsg::SharedPtr msg){
  ArrayMsg predicted_pos;
  predicted_pos.data = msg->data;
  publisher_->publish(predicted_pos);
}

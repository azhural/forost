#include <rclcpp/rclcpp.hpp>
#include <behaviortree_cpp/bt_factory.h>
#include <forost/ConditionNode.h>
#include <forost/SyncActionNode.h>

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);

  auto nh = rclcpp::Node::make_unique("forost");
  nh->declare_parameter("bt_xml");

  std::string bt_xml;
  nh->get_parameter("bt_xml", bt_xml);

  BT::BehaviorTreeFactory factory;

  factory.registerNodeType<forost::ConditionNode>("foROStConditionNode");
  factory.registerNodeType<forost::SyncActionNode>("foROStSyncActionNode");

  auto tree = factory.createTreeFromFile(bt_xml);

  auto status = BT::NodeStatus::RUNNING;

  while(rclcpp::ok() && status == BT::NodeStatus::RUNNING) {
    status = tree.tickOnce();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }

  return 0;
}

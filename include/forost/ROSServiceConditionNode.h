#ifndef ROS_SERVICE_CONDITION_NODE_H
#define ROS_SERVICE_CONDITION_NODE_H

#include <behaviortree_cpp/condition_node.h>
#include <rclcpp/rclcpp.hpp>

namespace forost {

class ROSServiceConditionNode : public BT::ConditionNode {
public:
    ROSServiceConditionNode(const std::string& name, const BT::NodeConfig& config); 
    virtual ~ROSServiceConditionNode() override = default;

    static BT::PortsList providedPorts();

protected:
    virtual BT::NodeStatus tick() override;
};

}
#endif
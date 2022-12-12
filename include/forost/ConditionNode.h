#ifndef FOROST_CONDITION_NODE_H
#define FOROST_CONDITION_NODE_H

#include <behaviortree_cpp/condition_node.h>
#include <rclcpp/rclcpp.hpp>

namespace forost {

class ConditionNode : public BT::ConditionNode {
public:
    ConditionNode(const std::string& name, const BT::NodeConfig& config); 
    virtual ~ConditionNode() override = default;

    static BT::PortsList providedPorts();

protected:
    virtual BT::NodeStatus tick() override;
};

}
#endif
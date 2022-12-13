#ifndef FOROST_SYNC_ACTION_NODE_H
#define FOROST_SYNC_ACTION_NODE_H

#include <behaviortree_cpp_v3/action_node.h>
#include <rclcpp/rclcpp.hpp>

namespace forost {

class SyncActionNode : public BT::SyncActionNode {
public:
    SyncActionNode(const std::string& name, const BT::NodeConfiguration& config);
    virtual ~SyncActionNode() override = default;

    static BT::PortsList providedPorts();

protected:
    virtual BT::NodeStatus tick() override;
};

}
#endif
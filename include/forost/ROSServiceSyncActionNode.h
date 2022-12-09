#ifndef ROS_SERVICE_SYNC_ACTION_NODE_H
#define ROS_SERVICE_SYNC_ACTION_NODE_H

#include <behaviortree_cpp/action_node.h>
#include <rclcpp/rclcpp.hpp>

namespace forost {

class ROSServiceSyncActionNode : public BT::SyncActionNode {
public:
    ROSServiceSyncActionNode(const std::string& name, const BT::NodeConfig& config);
    virtual ~ROSServiceSyncActionNode() override = default;

    static BT::PortsList providedPorts();

protected:
    virtual BT::NodeStatus tick() override;
};

}
#endif
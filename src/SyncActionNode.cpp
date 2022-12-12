#include <forost/SyncActionNode.h>
#include <forost_interfaces/srv/action_iface.hpp>

namespace forost {

    SyncActionNode::SyncActionNode(const std::string& name, const BT::NodeConfig& config)
    : BT::SyncActionNode(name, config)
    {

    }

    BT::PortsList SyncActionNode::providedPorts() {
        return {
            BT::InputPort<std::string>("topic")
        };
    }

    BT::NodeStatus SyncActionNode::tick() {
        BT::Expected<std::string> topic = TreeNode::getInput<std::string>("topic");
        if(!topic) {
            throw BT::RuntimeError("Missing required input [topic]: ", topic.error());
        }

        auto node = rclcpp::Node::make_shared(this->name());

        rclcpp::Client<forost_interfaces::srv::ActionIface>::SharedPtr client = node->create_client<forost_interfaces::srv::ActionIface>(topic.value());

        if(!client->wait_for_service(std::chrono::duration<std::int64_t, std::milli>(5000))) return BT::NodeStatus::FAILURE;

        auto request = std::make_shared<forost_interfaces::srv::ActionIface::Request>();

        auto result = client->async_send_request(request);

        if(rclcpp::spin_until_future_complete(node, result) != rclcpp::FutureReturnCode::SUCCESS) return BT::NodeStatus::FAILURE;

        switch(result.get()->status) {
            case forost_interfaces::srv::ActionIface::Response::FAILURE:
                return BT::NodeStatus::FAILURE;
            case forost_interfaces::srv::ActionIface::Response::SUCCESS:
                return BT::NodeStatus::SUCCESS;
            default:
                return BT::NodeStatus::FAILURE;
        }
    }

}
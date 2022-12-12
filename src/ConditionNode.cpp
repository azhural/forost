#include <forost/ConditionNode.h>>
#include <forost_interfaces/srv/condition_iface.hpp>

namespace forost {

    ConditionNode::ConditionNode(const std::string& name, const BT::NodeConfig& config) 
    : BT::ConditionNode(name, config)
    {

    }

    BT::PortsList ConditionNode::providedPorts() {
        return {
            BT::InputPort<std::string>("topic")
        };
    }

    BT::NodeStatus ConditionNode::tick() {
        BT::Expected<std::string> topic = TreeNode::getInput<std::string>("topic");
        if(!topic) {
            throw BT::RuntimeError("Missing required input [topic]: ", topic.error());
        }

        auto node = rclcpp::Node::make_shared(this->name());

        rclcpp::Client<forost_interfaces::srv::ConditionIface>::SharedPtr client = node->create_client<forost_interfaces::srv::ConditionIface>(topic.value());

        if(!client->wait_for_service(std::chrono::duration<std::int64_t, std::milli>(5000))) return BT::NodeStatus::FAILURE;

        auto request = std::make_shared<forost_interfaces::srv::ConditionIface::Request>();

        auto result = client->async_send_request(request);

        if(rclcpp::spin_until_future_complete(node, result) != rclcpp::FutureReturnCode::SUCCESS) return BT::NodeStatus::FAILURE;

        switch(result.get()->status) {
            case forost_interfaces::srv::ConditionIface::Response::FAILURE:
                return BT::NodeStatus::FAILURE;
            case forost_interfaces::srv::ConditionIface::Response::SUCCESS:
                return BT::NodeStatus::SUCCESS;
            default:
                return BT::NodeStatus::FAILURE;
        }
    }

}

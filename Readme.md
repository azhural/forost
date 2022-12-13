# foROSt

Access to BehaviorTree.CPP via ROS2 interfaces.

This is intended for Python ROS2 users, as it is already possible to use ROS functionalities in custom BT-Node classes.

## Requirements

Install BehaviorTree.CPP v3.8 via apt: `ros-foxy-behaviortree-cpp-v3` or in your ROS workspace.
https://github.com/BehaviorTree/BehaviorTree.CPP

Get `forost_interfaces` which includes the ROS2 message types used in this package.


## Available Nodes

### General

Unsupported return values will trigger an exception being thrown. Unreachable ROS nodes will result in `FAILURE` status for the node.

### foROStConditionNode

Returns `SUCCESS` or `FAILURE` depending on service result.

 - `topic`: Service topic to attach to, uses `forost_interfaces::srv::ConditionIface`

 ### foROStSyncActionNode

Returns `SUCCESS` or `FAILURE` depending on service result. SyncActionNodes throw an exception if `RUNNING` is returned.

 - `topic`: Service topic to attach to, uses `forost_interfaces::srv::ActionIface`

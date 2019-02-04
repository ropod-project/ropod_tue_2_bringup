#!/bin/bash

source ~/ropod-project-software/catkin_workspace/src/platform/robot_common/setup.bash

alias ropod-wireless="export ROS_MASTER_URI=http://$ROPOD_TUE_2_IP:11311;
                     export ROS_IP=$ROPOD_TUE_2_IP;
                     export WIRED_CONNECTION=false;
                     unset ROS_HOSTNAME"

ropod-wireless

alias ropod-wired="export ROS_MASTER_URI=http://$ROPOD_IP_WIRED:11311;
                  export ROS_IP=$ROPOD_IP_WIRED;
                  export WIRED_CONNECTION=true;
                  unset ROS_HOSTNAME"

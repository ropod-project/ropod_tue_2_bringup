#!/bin/bash

source ~/ropod-project-software/catkin_workspace/src/platform/robot_common/setup.bash

#alias ropod-wireless="export ROS_MASTER_URI=http://$ROPOD_TUE_2_IP:11311;
#                     export ROS_IP=$ROPOD_TUE_2_IP;
#                     export WIRED_CONNECTION=false;
#                     unset ROS_HOSTNAME"
#
#ropod-wireless
#
#alias ropod-wired="export ROS_MASTER_URI=http://$ROPOD_IP_WIRED:11311;
#                  export ROS_IP=$ROPOD_IP_WIRED;
#                  export WIRED_CONNECTION=true;
#                  unset ROS_HOSTNAME"

#export ROS_MASTER_URI=http://localhost:11311;
#export ROS_HOSTNAME=ropod_tue_2;
#'192.168.44.92 169.254.104.2'
#export ROS_MASTER_URI=http://<hostname>.local:11311;

#export WIRED_CONNECTION=true;

#export ROS_MASTER_URI=http://192.168.44.92:11311;
#export ROS_MASTER_URI=$ROS_MASTER_URI http://169.254.104.2:11311;

#unset ROS_HOSTNAME;


export ROS_IP=`hostname -I`

#!/bin/bash

# Script to setup xavier nx devel

onlyroot="Do not run this script as root!!!"

if [ $(whoami) == "root" ]; then     #"guarding against root execution"
    echo -e $COLOR$onlyroot$MONO
    exit 0
fi

setup () {
  sudo apt install -y $1
  if [ $? -eq 0 ]; then
    echo "<--------------------------- $1 Install OK"
  else
    echo "<--------------------------- $1 Install failed"
    exit $?
  fi
}

echo "<-----Setting up devel----->"
#Update system
echo "<-----Updating system----->"
sudo apt update
sudo apt upgrade -y


#Install tools
echo "<-----Installing common tools----->"
setup "tmux"
setup "vim nano"
setup "openssh-server"
setup "build-essential git cmake"
setup "virtualenv"


#Install vscode
echo "<-----Installing VSCode---->"
setup "apt-transport-https"
wget -qO- https://packages.microsoft.com/keys/microsoft.asc | gpg --dearmor > packages.microsoft.gpg
sudo install -o root -g root -m 644 packages.microsoft.gpg /etc/apt/trusted.gpg.d/
sudo sh -c 'echo "deb [arch=amd64,arm64,armhf signed-by=/etc/apt/trusted.gpg.d/packages.microsoft.gpg] https://packages.microsoft.com/repos/code stable main" > /etc/apt/sources.list.d/vscode.list'
sudo apt update
setup code


#Install ROS Melodic
echo "<----Installing ROS Melodic----->"
sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'
sudo apt-key adv --keyserver 'hkp://keyserver.ubuntu.com:80' --recv-key C1CF6E31E6BADE8868B172B4F42ED6FBAB17C654
sudo apt update
setup "ros-melodic-desktop-full"

echo "#Sourcing ROS Melodic" >> ~/.bashrc
echo "source /opt/ros/melodic/setup.bash" >> ~/.bashrc
source ~/.bashrc

setup "python-rosdep python-rosinstall python-rosinstall-generator python-wstool"
sudo rosdep init
rosdep update
setup "python-catkin-tools"

sudo apt autoremove -y

echo "<----Devel setup done----->"

#!/usr/bin/env bash

# Post install script to setup a linux development environment

onlyroot="Do not run this script as root!!!"

if [ $(whoami) == "root" ]; then     #"guarding against root execution"
    echo -e $COLOR$onlyroot$MONO
    exit 0
fi

setup () {
  echo "Do you wish to install $1??"
  select reply in "Yes" "No"; do
    case $reply in
      Yes )
        sudo apt install -y $1
        if [ $? -eq 0 ]; then
          echo "<--------------------------- $1 Install OK"
        else
          echo "<--------------------------- $1 Install failed"
          exit $?
        fi
        break;;
      * )
        echo "Okay, no problem. :) Let's move on!"
        echo "Skipping $1" 
        break;;
    esac
  done
}

echo "-------------------------------------------------"
echo "<-- Linux Development Setup - Hans -->"
echo "-------------------------------------------------"

echo "<-- Updating base system -->"
sudo apt update
sudo apt upgrade -y

echo "-------------------------------------------------"
echo "<-- Installing common tools -->"
setup "snapd"
setup "terminator"
setup "vim"
setup "nano"
setup "wget"
setup "curl"
setup "openssh-server"
setup "build-essential cmake"
setup "virtualenv python3-pip pipenv"

echo "-------------------------------------------------"
echo "<-- Git install and config -->"
echo "Do you wish to install git??"
select reply in "Yes" "No"; do
  case $reply in
    Yes )
      echo "Installing Git"
      sudo apt install -y git
      echo "What username do you want to use for git?"
      read git_username
      git config --global user.name "$git_username"
      echo "-----------------------------------------"
      echo "What user email do you want to use for git?"
      read git_useremail
      git config --global user.email "$git_useremail"
      break;;
    * ) 
      echo "Okay, no problem. :) Let's move on!"
      echo "Skipping Git"
      break;;
  esac
done

echo "-------------------------------------------------"
echo "<-- VSCode install and config -->"
echo "Do you wish to install VSCode??"
select reply in "Yes" "No"; do
  case $reply in
    Yes )
      echo "Installing VSCode"
      sudo apt install -y apt-transport-https
      wget -qO- https://packages.microsoft.com/keys/microsoft.asc | gpg --dearmor > packages.microsoft.gpg
      sudo install -o root -g root -m 644 packages.microsoft.gpg /etc/apt/trusted.gpg.d/
      sudo sh -c 'echo "deb [arch=amd64,arm64,armhf signed-by=/etc/apt/trusted.gpg.d/packages.microsoft.gpg] https://packages.microsoft.com/repos/code stable main" > /etc/apt/sources.list.d/vscode.list'
      sudo apt update
      sudo apt install -y code
      break;;
    * )
      echo "Okay, no problem. :) Let's move on!"
      echo "Skipping VSCode"
      break;;
  esac
done

setup_extension () {
  echo "Do you wish to install extension: $1??"
  select reply in "Yes" "No"; do
    case $reply in
      Yes )
        code --install-extension $1
        if [ $? -eq 0 ]; then
          echo "<--------------------------- $1 Install OK"
        else
          echo "<--------------------------- $1 Install failed"
          exit $?
        fi
        break;;
      * )
        echo "Okay, no problem. :) Let's move on!"
        echo "Skipping $1"
        break;;
    esac
  done
}

echo "-------------------------------------------------"
echo "Do you wish to install some of my favourite VSCode extentions? (you can choose for each)"
select reply in "Yes" "No"; do
  case $reply in
    Yes )
      echo "Installing VSCode extensions"
      setup_extension eamodio.gitlens
      setup_extension coenraads.bracket-pair-colorizer-2
      setup_extension ms-vscode.cpptools-extension-pack 
      setup_extension mhutchie.git-graph
      setup_extension wayou.vscode-todo-highlight
      setup_extension ms-python.python
      setup_extension oderwat.indent-rainbow
      setup_extension pkief.material-icon-theme
      setup_extension esbenp.prettier-vscode
      break;;
    * )
      echo "Okay, no problem. :) Let's move on!"
      echo "Skipping VSCode extensions"
      break;;
  esac
done

echo "-------------------------------------------------"
echo "Do you wish to install spotify?"
echo "Make sure you HAVE snap store installed!"
select reply in "Yes" "No"; do
  case $reply in
    Yes )
      echo "Installing spotify"
      snap install spotify
      break;;
    * )
      echo "Okay, no problem. :) Let's move on!"
      echo "Skipping spotify"
      break;;
  esac
done

echo "<-- cleaning -->"
sudo apt autoremove -y

echo "-------------------------------------------------"
echo "<-- Linux Development Setup Done -->"
echo "-------------------------------------------------"
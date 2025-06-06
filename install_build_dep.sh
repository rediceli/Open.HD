#!/usr/bin/env bash
################################################################################
# OpenHD
# 
# Licensed under the GNU General Public License (GPL) Version 3.
# 
# This software is provided "as-is," without warranty of any kind, express or 
# implied, including but not limited to the warranties of merchantability, 
# fitness for a particular purpose, and non-infringement. For details, see the 
# full license in the LICENSE file provided with this source code.
# 
# Non-Military Use Only:
# This software and its associated components are explicitly intended for 
# civilian and non-military purposes. Use in any military or defense 
# applications is strictly prohibited unless explicitly and individually 
# licensed otherwise by the OpenHD Team.
# 
# Contributors:
# A full list of contributors can be found at the OpenHD GitHub repository:
# https://github.com/OpenHD
# 
# © OpenHD, All Rights Reserved.
################################################################################

set -e

PLATFORM="$1"


BASE_PACKAGES="libpoco-dev clang-format libusb-1.0-0-dev libpcap-dev libsodium-dev libnl-3-dev libnl-genl-3-dev libnl-route-3-dev libsdl2-dev"
VIDEO_PACKAGES="libgstreamer-plugins-base1.0-dev libv4l-dev"
BUILD_PACKAGES="git build-essential autotools-dev automake libtool python3-pip autoconf apt-transport-https ruby-dev cmake"


function install_pi_packages {
PLATFORM_PACKAGES="libcamera-openhd"
PLATFORM_PACKAGES_REMOVE="python3-libcamera libcamera0"
}
function install_x86_packages {
PLATFORM_PACKAGES="libunwind-dev gstreamer1.0-plugins-bad gstreamer1.0-plugins-ugly"
PLATFORM_PACKAGES_REMOVE=""
}
function install_rock_packages {
PLATFORM_PACKAGES="libpoco-dev gstreamer1.0-plugins-bad gstreamer1.0-plugins-ugly"
PLATFORM_PACKAGES_REMOVE=""
}

 # Add OpenHD Repository platform-specific packages
 apt update
 apt install -y curl
 curl -1sLf 'https://dl.cloudsmith.io/public/openhd/release/setup.deb.sh'| sudo -E bash
 apt update
 apt upgrade -y -o Dpkg::Options::="--force-overwrite" --no-install-recommends --allow-downgrades

# Main function
 
 if [[ "${PLATFORM}" == "rpi" ]]; then
    install_pi_packages
 elif [[ "${PLATFORM}" == "ubuntu-x86" ]] ; then
    install_x86_packages
 elif [[ "${PLATFORM}" == "rock5" ]] ; then
    install_rock_packages
 else
    echo "platform not supported"
 fi


 # Install platform-specific packages
 echo "Removing platform-specific packages..."
 for package in ${PLATFORM_PACKAGES_REMOVE}; do
     echo "Removing ${package}..."
     apt purge -y ${package}
     if [ $? -ne 0 ]; then
         echo "Failed to remove ${package}!"
         exit 1
     fi
 done

 # Install platform-specific packages
 echo "Installing platform-specific packages..."
 for package in ${PLATFORM_PACKAGES} ${BASE_PACKAGES} ${VIDEO_PACKAGES} ${BUILD_PACKAGES}; do
     echo "Installing ${package}..."
     apt install -y -o Dpkg::Options::="--force-overwrite" --no-install-recommends ${package}
     if [ $? -ne 0 ]; then
         echo "Failed to install ${package}!"
         exit 1
     fi
 done
 


# Installing ruby packages
gem install dotenv -v 2.8.1
gem install fpm


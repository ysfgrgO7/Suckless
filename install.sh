#!/usr/bin/env bash

# ~/
cd

# Install Deps
echo "### Installing DEPS ###"
if command -v pacman &> /dev/null
then
    sudo pacman -S --noconfirm --needed base-devel opendoas lm_sensors psmisc xorg-xsetroot    
elif command -v xbps-install &> /dev/null 
then
    sudo xbps-install -Syu libXft-devel libX11-devel harfbuzz-devel libXext-devel libXrender-devel libXinerama-devel base-devel psmisc opendoas lm_sensors xsetroot
elif command -v apt-get &> /dev/null
then
	sudo apt-get install build-essential libx11-dev lm-sensors libxinerama-dev sharutils suckless-tools libxft-dev libc6 x11-xserver-utils
fi

# Clone
echo "### Installing Suckless programs ###"
mkdir -p ~/.config
git clone https://github.com/ysfgrgO7/Suckless.git ~/.config/suckless

# Building
cd ~/.config/suckless/nvoidwm/
rm -f config.h
sudo make clean install
cd ../dmenu
rm -f config.h
sudo make clean install
cd ../st 
rm -f config.h
sudo make clean install
cd ../slstatus
sudo make clean install

# ~/.config/suckless
cd ~/.config/suckless/

# Copying the doas config
echo "### Copying the *Doas * config ###"
sudo cp -r doas.conf /etc/doas.conf

# Creating Login Manager Entry DWM
echo "Creating Login Manager Entry for DWM"
sudo mkdir -p /usr/share/xsessions/
cd /usr/share/xsessions
sudo touch dwm.desktop
sudo chown $USER dwm.desktop
sudo cat > dwm.desktop <<EOF
[Desktop Entry]
Encoding=UTF-8
Name=Dwm
Comment=the dynamic window manager
Exec=dwm
Icon=dwm
Type=XSession
EOF

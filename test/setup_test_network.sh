#!/bin/bash -eu
# -e: cmd1 && cmd2 && cmd3 === set -e \n cmd1 \n cmd2 \n cmd3
# -u: shell prints a message to stderr when it tries to expand a variable that is not set
# -x: The shell prints each command in a script to stderr before running it

# Remove 
sudo ifconfig tap0 down || echo ""
sudo ifconfig tap1 down || echo ""
sudo ifconfig tap0tap1 down || echo ""
sudo brctl delbr tap0tap1 || echo ""
sudo ip a del dev tap0 192.168.7.1/24 || echo ""
sudo ip a del dev tap1 192.168.7.2/24 || echo ""
sudo ip tuntap del dev tap0 mode tap || echo ""
sudo ip tuntap del dev tap1 mode tap || echo ""

# Add
sudo ip tuntap add dev tap0 mode tap user $(id -u)
sudo ip tuntap add dev tap1 mode tap user $(id -u)
sudo ip a a dev tap0 192.168.7.1/24
sudo ip a a dev tap1 192.168.7.2/24

sudo brctl addbr tap0tap1
sudo brctl addif tap0tap1 tap0
sudo brctl addif tap0tap1 tap1

# Activate
sudo ifconfig tap0tap1 up
sudo ifconfig tap0 up
sudo ifconfig tap1 up

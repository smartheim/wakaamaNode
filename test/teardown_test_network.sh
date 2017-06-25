#!/bin/bash -eux

sudo brctl delbr tap0tap1
sudo ip a del dev tap0 192.168.7.1/24
sudo ip a del dev tap1 192.168.7.2/24
sudo ip tuntap del dev tap0 mode tap
sudo ip tuntap del dev tap1 mode tap


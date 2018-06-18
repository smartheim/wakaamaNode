#!/bin/bash -eux

sudo brctl delbr tap0tap1 || echo ""
sudo ip a del dev tap0 192.168.7.1/24 || echo ""
sudo ip a del dev tap1 192.168.7.2/24 || echo ""
sudo ip tuntap del dev tap0 mode tap || echo ""
sudo ip tuntap del dev tap1 mode tap || echo ""


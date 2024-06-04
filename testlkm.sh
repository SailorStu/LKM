#!/bin/bash

if [ "$EUID" -ne 0 ]
  then echo "Please run as root"
  exit
fi

insmod nflkm_hook.ko

echo "Netfilter hook on UDP port 54 = DROP installed. Test and then Press any key to unload LKM."
read -n1 -s

rmmod nflkm_hook
tail -n20   /var/log/syslog

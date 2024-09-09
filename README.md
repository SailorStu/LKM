# LKM Netfilter Hook example


## Operation
This LKM will block all incoming traffic to local UDP port 54.

You will need kernel headers installed. 

Install Dev requirements

For Ubuntu:

sudo apt install clang llvm libelf-dev libbpf-dev libpcap-dev build-essential linux-headers-$(uname -r) linux-tools-common linux-tools-generic tcpdump net-tools procinfo

Install kernel headers
sudo apt-get -y install linux-headers-$(uname -r)

nflkm_hook.c:

This example will also use Netfilter to set a pre-routing hook on IPv4. It will drop all UDP packets sent
to host:54, while loaded. You can test using netcat to listen on 0.0.0.0:54 and then externally send a UDP 
packet to Host:54. 

readshadow.c:

Demonstrates how to properly read a file from the file system within kernel space. In this case we read
/etc/shadow and emit it into syslog using printk.

sudo  insmod readshadow.ko
sudo rmmod readshadow
sudo demsg


Have fun


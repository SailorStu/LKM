# LKM Netfilter Hook example


## Operation
This LKM will block all incoming traffic to local UDP port 54.

You will need kernel headers installed. 

Install Dev requirements

For Ubuntu:

sudo apt install clang llvm libelf-dev libbpf-dev libpcap-dev build-essential linux-headers-$(uname -r) linux-tools-common linux-tools-generic tcpdump net-tools procinfo

Install kernel headers
sudo apt-get -y install linux-headers-$(uname -r)

Have fun


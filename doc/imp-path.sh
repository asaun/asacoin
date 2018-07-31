echo "%sudo ALL=NOPASSWD: /usr/bin/lxc-start" > /etc/sudoers.d/gitian-lxc
# add cgroup for LXC
echo "cgroup  /sys/fs/cgroup  cgroup  defaults  0   0" >> /etc/fstab
# make /etc/rc.local script that sets up bridge between guest and host
echo '#!/bin/sh -e' > /etc/rc.local
echo 'brctl addbr br0' >> /etc/rc.local
echo 'ifconfig br0 10.0.3.2/24 up' >> /etc/rc.local
echo 'exit 0' >> /etc/rc.local
# make sure that USE_LXC is always set when logging in as debian,
# and configure LXC IP addresses
echo 'export USE_LXC=1' >> /home/cyy/.profile
echo 'export GITIAN_HOST_IP=10.0.3.2' >> /home/cyy/.profile
echo 'export LXC_GUEST_IP=10.0.3.5' >> /home/cyy/.profile

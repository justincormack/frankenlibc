## Basic example of running Nginx

Below is the outline of how to get Nginx running as a unikernel in
Linux userspace. It shows how to work with block and network
devices.

Working on making this easier still. FreeBSD and NetBSD are similar
but not currently as well tested.

```
# clone this repo
make
# add binaries to your path eg
export PATH=$PATH:~/frankenlibc/rump/bin

git clone https://github.com/mato/rump-nginx.git
cd rump-nginx
RUMPRUN_CC=rumprun-cc make
cd images
# this repo is set up to build two iso filesystems, we want a single root fs
# you might want to adjust config, eg error logging to stdout is useful
# if you do this you can also mount the file system read only later
tar cf /tmp/data.tar data
cp -a stubetc etc
tar cf /tmp/etc.tar etc
cd ..

# first get /dev nodes from default rump setup
rump.tar c -f - /dev > /tmp/dev.tar
# make an empty file
dd if=/dev/zero of=/tmp/fs.img bs=1k count=10k
# make it a loopback device
sudo losetup --show -f /tmp/fs.img 
it will output the device name eg /dev/loop0
# change ownership to your user
sudo chown justin:justin /dev/loop0
# make a file system on the block device
rexec rump.newfs /dev/loop0 -- /dev/rblock0

# you can look at the file system
rexec rump.df /dev/loop0
# add a /tmp directory
rexec rump.mkdir /dev/loop0 -- /tmp
rexec rump.ls /dev/loop0

# for some reason still to be fixed the system tar does not like stdin
# so lets copy the files onto the image first
cat /tmp/dev.tar | rexec rump.dd /dev/loop0 -- of=dev.tar
cat /tmp/data.tar | rexec rump.dd /dev/loop0 -- of=data.tar
cat /tmp/etc.tar | rexec rump.dd /dev/loop0 -- of=etc.tar

# untar these onto the filesystem
rexec rump.tar /dev/loop0 -- xvf dev.tar
rexec rump.tar /dev/loop0 -- xvf data.tar
rexec rump.tar /dev/loop0 -- xvf etc.tar

# clean up
rexec rump.rm /dev/loop0 -- dev.tar data.tar etc.tar

# now we have a useful root fs, set up networking
# easiest is a macvtap interface but you can only reach from another machine
# (cant get macvtap bridging working correctly)

# replace p5p1 with your network eg eth0; note wireless probably wont work
sudo ip link add link p5p1 name macvtap0 type macvtap
sudo ip link set dev macvtap0 up
# created /dev/tap6 - the number depends on the interface number, ls /dev/tap* to see
sudo chown justin /dev/tap6

# alternatively you can use a normal tap device if you add it to a bridge
sudo ip tuntap add dev tap0 mode tap user justin
sudo ip link set dev tap0 up
# add to bridge then you can refer to this as tun:tap0 instead of /dev/tap6 below
rexec rump.ifconfig tun:tap0

# check it picks up addresses
rexec rump.ifconfig /dev/tap6

# if that works lets try nginx
rexec nginx/objs/nginx /dev/tap6 /dev/loop0 -- -c /data/conf/nginx.conf

# notice if you restart it it will say "/: replaying log to disk" that is because we
# did not do a clean shutdown on a rw mounted fs, so it replays the journal.
```

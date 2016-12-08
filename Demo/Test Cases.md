
###Comments are enclosed in these symbols###

__________________________________________________________________________________________________________________
###Test Case 1: blocking all incoming traffic with a particular source IP address###
###Incoming traffic with source IP address 129.59.15.60 were successfully blocked###
###Incoming traffic with source IP address 128.119.8.148 were successfully blocked###

vagrant@Xubuntu-Vagrant:~/Desktop/Test_Final$ sudo echo "129.59.15.60" >> /proc/incoming <br />
vagrant@Xubuntu-Vagrant:~/Desktop/Test_Final$ sudo echo "128.119.8.148" >> /proc/incoming <br />
vagrant@Xubuntu-Vagrant:~/Desktop/Test_Final$ ping www.google.com <br />
PING www.google.com (173.194.66.105) 56(84) bytes of data. <br />
64 bytes from qo-in-f105.1e100.net (173.194.66.105): icmp_seq=1 ttl=63 time=15.3 ms <br />
64 bytes from qo-in-f105.1e100.net (173.194.66.105): icmp_seq=2 ttl=63 time=16.7 ms <br />
64 bytes from qo-in-f105.1e100.net (173.194.66.105): icmp_seq=3 ttl=63 time=24.9 ms <br />
c64 bytes from qo-in-f105.1e100.net (173.194.66.105): icmp_seq=4 ttl=63 time=17.9 ms <br />
64 bytes from qo-in-f105.1e100.net (173.194.66.105): icmp_seq=5 ttl=63 time=18.3 ms <br />
^C
--- www.google.com ping statistics ---
5 packets transmitted, 5 received, 0% packet loss, time 4005ms <br />
rtt min/avg/max/mdev = 15.366/18.673/24.989/3.325 ms <br />
vagrant@Xubuntu-Vagrant:~/Desktop/Test_Final$ ping 129.59.15.60 <br />
PING 129.59.15.60 (129.59.15.60) 56(84) bytes of data. <br />
^C
--- 129.59.15.60 ping statistics ---
5 packets transmitted, 0 received, 100% packet loss, time 4000ms   <br />
vagrant@Xubuntu-Vagrant:~/Desktop/Test_Final$ ping 128.119.8.148 <br />
PING 128.119.8.148 (128.119.8.148) 56(84) bytes of data. <br />
^C
--- 128.119.8.148 ping statistics ---
3 packets transmitted, 0 received, 100% packet loss, time 2014ms 


### Contents of the log file ###
vagrant@Xubuntu-Vagrant:~/Desktop/Test_Final$ sudo tail /var/log/syslog <br />
Dec  8 05:41:17 Xubuntu-Vagrant kernel: [ 9216.734011] packet accpted<br />
Dec  8 05:41:38 Xubuntu-Vagrant kernel: [ 9216.734024] incoming packet from source addr: 129.59.15.60 dropped <br />
Dec  8 05:41:38 Xubuntu-Vagrant kernel: [ 9237.717174] No outgoing traffic to block. <br />
Dec  8 05:41:38 Xubuntu-Vagrant kernel: [ 9237.775125] packet accpted <br />
Dec  8 05:41:39 Xubuntu-Vagrant kernel: [ 9237.775177] incoming packet from source addr: 128.119.8.148 dropped <br />
Dec  8 05:41:39 Xubuntu-Vagrant kernel: [ 9238.724143] No outgoing traffic to block. <br />
Dec  8 05:41:39 Xubuntu-Vagrant kernel: [ 9238.779040] packet accpted <br />
Dec  8 05:41:40 Xubuntu-Vagrant kernel: [ 9238.779092] incoming packet from source addr: 128.119.8.148 dropped <br />
Dec  8 05:41:40 Xubuntu-Vagrant kernel: [ 9239.731869] No outgoing traffic to block. <br />
Dec  8 05:41:40 Xubuntu-Vagrant kernel: [ 9239.786971] packet accpted <br />



__________________________________________________________________________________________________________________
###Test Case 2: blocking all outging traffic with a particular destination IP address###
###Incoming traffic with destination IP address 128.119.8.148 were successfully blocked###

vagrant@Xubuntu-Vagrant:~/Desktop/Test_Final$ sudo echo "128.119.8.148" >> /proc/outgoing <br />
vagrant@Xubuntu-Vagrant:~/Desktop/Test_Final$ ping 128.119.8.148 <br />
PING 128.119.8.148 (128.119.8.148) 56(84) bytes of data. <br />
ping: sendmsg: Operation not permitted <br />
ping: sendmsg: Operation not permitted <br />
ping: sendmsg: Operation not permitted <br />
ping: sendmsg: Operation not permitted <br />
ping: sendmsg: Operation not permitted <br />
ping: sendmsg: Operation not permitted <br />
ping: sendmsg: Operation not permitted <br />
ping: sendmsg: Operation not permitted <br />
^C
--- 128.119.8.148 ping statistics ---
8 packets transmitted, 0 received, 100% packet loss, time 6998ms  


### Contents of the log file ###
vagrant@Xubuntu-Vagrant:~/Desktop/Test_Final$ sudo tail /var/log/syslog <br />
Dec  8 05:41:39 Xubuntu-Vagrant kernel: [ 9237.775177] incoming packet from source addr: 128.119.8.148 dropped <br />
Dec  8 05:41:39 Xubuntu-Vagrant kernel: [ 9238.724143] No outgoing traffic to block. <br />
Dec  8 05:41:39 Xubuntu-Vagrant kernel: [ 9238.779040] packet accpted <br />
Dec  8 05:41:40 Xubuntu-Vagrant kernel: [ 9238.779092] incoming packet from source addr: 128.119.8.148 dropped <br />
Dec  8 05:41:40 Xubuntu-Vagrant kernel: [ 9239.731869] No outgoing traffic to block. <br />
Dec  8 05:41:40 Xubuntu-Vagrant kernel: [ 9239.786971] packet accpted <br />
Dec  8 05:42:52 Xubuntu-Vagrant kernel: [ 9239.787028] incoming packet from source addr: 128.119.8.148 dropped <br />
Dec  8 05:42:54 Xubuntu-Vagrant kernel: [ 9312.442782] outgoing packet to dest addr: 128.119.8.148 droppedoutgoing packet to dest addr: 128.119.8.148 dropped <br />
Dec  8 05:42:56 Xubuntu-Vagrant kernel: [ 9314.441713] outgoing packet to dest addr: 128.119.8.148 droppedoutgoing packet to dest addr: 128.119.8.148 dropped <br />
Dec  8 05:42:58 Xubuntu-Vagrant kernel: [ 9316.441763] outgoing packet to dest addr: 128.119.8.148 droppedoutgoing packet to dest addr: 128.119.8.148 dropped <br />



__________________________________________________________________________________________________________________
###Test Case 3: blocking all incoming & outging traffic###
###All traffic was successfully blocked###

vagrant@Xubuntu-Vagrant:~/Desktop/Test_Final$ sudo echo "1" >> /proc/blockAll <br />
vagrant@Xubuntu-Vagrant:~/Desktop/Test_Final$ ping www.google.com <br />
ping: unknown host www.google.com <br />



__________________________________________________________________________________________________________________
###Test Case 4: unblocking all incoming & outging traffic###
###All traffic was successfully unblocked###

vagrant@Xubuntu-Vagrant:~/Desktop/Test_Final$ sudo echo "1" >> /proc/blockAll <br />
vagrant@Xubuntu-Vagrant:~/Desktop/Test_Final$ ping www.google.com <br />
PING www.google.com (173.194.66.147) 56(84) bytes of data. <br />
64 bytes from qo-in-f147.1e100.net (173.194.66.147): icmp_seq=1 ttl=63 time=15.4 ms <br />
64 bytes from qo-in-f147.1e100.net (173.194.66.147): icmp_seq=2 ttl=63 time=17.9 ms <br />
64 bytes from qo-in-f147.1e100.net (173.194.66.147): icmp_seq=3 ttl=63 time=17.9 ms <br />
^C
--- www.google.com ping statistics ---
3 packets transmitted, 3 received, 0% packet loss, time 2003ms  <br />
rtt min/avg/max/mdev = 15.462/17.113/17.964/1.177 ms <br />

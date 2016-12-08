The following commands must be typed in the command line

Building the Module:
make

Loading the Module to the Kernel:
sudo insmod Final03.ko


Module Usage #1: Blocking & Unblocking all Incoming & Outgoing Traffic
sudo echo "anything" >> /proc/blockAll
(the initial input, which has length greater than 0, will cause the module to block all incoming traffic.
to unblock, type the above command again.)



Module Usage #2: Blocking all Incoming Traffic with specified source IP addresses
sudo echo "some IP address" >> /proc/incoming
(up to 50 IP addresses can be added to the list of source IP addresses to filter)


Module Usage #3: Blocking all Outgoing Traffic with specified destination IP addresses
sudo echo "some IP address" >> /proc/outgoing
(up to 50 IP addresses can be added to the list of destination IP addresses to filter)


Injecting the Module from the Kernel:
sudo rmmod Final03

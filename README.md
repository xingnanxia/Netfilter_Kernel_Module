In order to test this kernel module, please `download the Demo folder` and enter the following into the command line:

###Building the Module:### </br>
make

Loading the Module to the Kernel: </br>
sudo insmod Final03.ko


Module Usage #1: Blocking & Unblocking all Incoming & Outgoing Traffic </br>
sudo echo "anything" >> /proc/blockAll </br>
(the initial input, which has length greater than 0, will cause the module to block all incoming traffic.
to unblock, type the above command again.)



Module Usage #2: Blocking all Incoming Traffic with specified source IP addresses</br>
sudo echo "some IP address" >> /proc/incoming</br>
(up to 50 IP addresses can be added to the list of source IP addresses to filter)


Module Usage #3: Blocking all Outgoing Traffic with specified destination IP addresses</br>
sudo echo "some IP address" >> /proc/outgoing</br>
(up to 50 IP addresses can be added to the list of destination IP addresses to filter)


Injecting the Module from the Kernel: </br>
sudo rmmod Final03

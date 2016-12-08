Notes that this repository stores the final version in the` Demo` folder. </br>
All the previous intermediate files are stored in another repository: https://github.com/xingnanxia/ArdisNatalie_Project4.git

# Netfilter Kernel Module

## Introduction
This is a Linux Netfilter Kernel Module developed by Xingnan Xia (https://github.com/xingnanxia) and Ardis Choi (https://github.com/choiy5). It uses three /proc files for users to communicate with the kernel: </br>
  `/proc/blockAll` enables the user to block all incoming and outgoing traffic. </br>
  `/proc/incoming` enables the user to enter the source address for the incoming traffic to block. </br>
  `/proc/outgoing` enables the user to enter the destination address for the outgoing traffic to block. </br>
 
This module is maded and compiled in Linux 4.4.0-21-generic and Linux 4.4.0-45-generic. 
  
## Usage

Inorder to test this kernel module, please `download the Demo folder`, cd to the Demo folder and 
enter the following into the command line:

####Building the Module: </br>
`make`

####Loading the Module to the Kernel: </br>
`sudo insmod Final03.ko`


####Module Usage #1: Blocking & Unblocking all Incoming & Outgoing Traffic </br>
`sudo echo "anything" >> /proc/blockAll` </br>
(the initial input, which has length greater than 0, will cause the module to block all incoming traffic.
to unblock, type the above command again.) </br>


####Module Usage #2: Blocking all Incoming Traffic with specified source IP addresses</br>
`sudo echo "some IP address" >> /proc/incoming`</br>
up to `50` IP addresses can be added to the list of source IP addresses to filter </br>
address need to be entered into the proc file one by one </br>
address need to be in IP format, human-readable address such as 'www.google.com' is not supported. </br>
unblocking a source IP address is not enabled </br>

Example: sudo echo "128.119.8.148" >> /proc/incoming

####Module Usage #3: Blocking all Outgoing Traffic with specified destination IP addresses</br>
`sudo echo "some IP address" >> /proc/outgoing`</br>
up to `50` IP addresses can be added to the list of destination IP addresses to filter </br>
address need to be entered into the proc file one by one </br>
address need to be in IP format, human-readable address such as 'www.google.com' is not supported. </br>
unblocking a destination IP address is not enabled </br>

Example: sudo echo "128.119.8.148" >> /proc/outgoing

####Injecting the Module from the Kernel: </br>
`sudo rmmod Final03`

####Looking at the log file: </br>
`dmesg` or `dmesg | tail`

####Test and Output: </br>
See `Test Cases.md` in the Demo folder 

## Acknowledgement
We are inspired by the examples in http://www.paulkiddie.com/2009/10/creating-a-simple-hello-world-netfilter-module/ and http://www.paulkiddie.com/2009/11/creating-a-netfilter-kernel-module-which-filters-udp-packets/.

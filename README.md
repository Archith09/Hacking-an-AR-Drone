Design:

Mission is to take control of the drone. In order to achieve that, first research how the Parrot client software controls the drone. After discovering in their SDK document and confirmed by capturing control packets by Wireshark, that the drone is controlled by commands of the structure: AT*{command name}={sequence number}{,command arguments}\r, which is sent through UDP to port 5556 on the drone every 30ms. 
There is a vulnerability in sequence number, as the drone accepts any sequence number larger than that of the last command, and number 1. 

The drone allows to be controlled by only device at a time, and is distinguished by MAC address. 
Having observed this information, the control console written in c++, sending command messages through UDP to port 5556 with sequence number starting from a large number, which is much larger than that of the current command. Also forging MAC address to be the same as that of the controlling device. 
This design completely takes over the control over drone, even in the middle of control of its former owner.
We closed telnet connection on the drone by 
“iptables -A INPUT -p tcp -m tcp --dport 23 -j DROP”

Possible Defenses:

Allow connection to be established through authentications. This will prevent others connecting to the drone’s network, thus preventing the attack. 

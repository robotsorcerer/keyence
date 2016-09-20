# Protocol for retrieving the profile map from the keyence sensor

##[Table of Contents](#table-of-contents)

- [Network Settings](#network-settings)

	- [Keyence Sensor IP Address Settings](#keyence-sensor-ip-address-settings)

	- [Linux Machine Static IP set-up set-up](#linux-machine-static-ip-set-up)
- [Code Trial](#code-trial)

## Network Settings

### Keyence Sensor IP address settings

Using the Windows based LJ-Navigator executable, configure the ip address of the sensor via the provided usb cable as a static ip.  Choose a preferrable ip address you would want for the sensor e.g.

```bash
      IP address: 192.168.10.20
      Subnet: 255.255.255.0
      Gateway: 0.0.0.0
      TCP Port Number (Command Send and Receive): 24691
      TCP Port Number (High-Speed Communication): 24692
      UDP Port Number: 24693
      Band Limitation at High Speed Communication: OFF
      MTU at high-speed communication: 1500
```

When you are done, on the bottom-right corner of the window, click send setting to push these settings to the LJ-V7300 sensor. 

Since we are going to be developing the code in Linux, disconnect the RJ-45 connector from the usb hub of your windows machine and plug it into the 1000BaseT hub of your Linux machine. I have confirmed being able to use the sensor simulatneously on a Windows (with the USB connection) and a Linux machine (with the Ethernet connection) but I do not know how safe this could be. In the interest of safety, it may be wise to unplug the USB connector from the Windows machine before running the executables on your Linux machine.

### Linux Machine Static IP set-up set-up.

On your Linux machine, hit the Super key and type in `Network`. We want to configure the ip address of our machine similar to the following:

```bash
   IP address: 192.168.10.15
   Subnet Mask: 255.255.255.0
```

In a terminal, try pinging the sensor's ip that we set above. If you do not get a trace back, you have probably not set up the sensor ip correctly. Go back to the previous [section](#keyence-sensor-ip-setting) and make sure everything is honky-dory before going on.

If your ping returns with successful traces, you are good to go. Navigate to the `EXE` directory within the root folder of this project and choose the OS architecture that corresponds to your setup.

## Code trial

With the keyence sensor powered and the blue lasers facing a distinct object, launch any of the executables for testing e.g.

```bash
    ogunmolu:~/Desktop/Keyence/Exe/Linux_i686$ ./LJV7_GetProfile 192.168.10.20
```

If everything goes well, you should see an output similar to the results in the [following log file](/Exe/Linux_i686/profile.log).




# keyence

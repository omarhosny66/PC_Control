# PC Control Server

This is a multi-client server application to control the PC using phone
app. This program can be considered as just a multi-client server application
,but it also has the capability of receiving simple PC commands and execute
them while running in a seperate process preventing any lag in the main 
process handling the communication with the client smoothly.

## Requirements
- Linux OS
- [C++ compiler](https://linuxconfig.org/how-to-install-g-the-c-compiler-on-ubuntu-20-04-lts-focal-fossa-linux)
- Connection to local network
- [TCP client app](https://play.google.com/store/apps/details?id=tcpudpserverclient.steffenrvs.tcpudpserverclient&hl=en&gl=US)

## Building

Check local IP adrress

Open terminal and run this command

```sh
ifconfig
```

The IP will be found bellow <UP,BROADCAST,RUNNING,MULTICAST>
and we are using ipv4, so it will be next to inet

After cloning the repo open terminal and change directory to
the PC_Control_Server dir and build the project

```sh
g++ parser.cpp command.cpp  tcpserver.cpp main.cpp -o main
```

Now the program is ready to be executed
Run the program with the required PORT argument which can be 8080
as default or any other port
```sh
./main <PORT>
```

Open the TCP client app installed earlier and create client with
the ipv4 address obtained and the selected port for the server,
then select the run option to start communication.

Now any message can be sent to the server through the mobile app,
in addition to command execution such as:
- terminal
- firefox
- calculator




## Features to be added

- Remote network commuincation
- Sending commands to the opened terminal and receiving output back
- Adding more commands to the server program

# CPRE489

1. Lab 2
    - To use TCP sockets to write client and server programs to implement the ruptimeUNIX command.
    - When the server is contacted by the client, it will execute the UNIX shell command uptimeand send the information returned by uptime to the client.
    - The client will display a server’s address followed by the uptime information received from that server. For example, if one of the machines contacted was 192.168.254.2, the output from ruptimeClient for that machine could be:
        - 192.168.254.2: 10:47am up 27 day(s), 50 mins, 1 user, load average: 0.18, 0.26, 0.20
    - After printing the uptime information for the two servers, the client then quits. The serversremainopen and waitfor further connections.
    
2. Lab 3 
    - To use UDP sockets to write a program to implement network impairments (i.e., loss and delay), and study this effect on a video     stream
    - The program will run on a Linux machine and will accept five parameters: listenerIP, listenerport, destination IP, destination port, and loss rate
    - The program will listen on the port number specified by the listener port parameter and will accept packets with the listener address specified by the listener IP parameter. 
    - Start the source VLC player (Applications -> Multimedia -> VLC media player). From the “Media” menu, choose “Stream”. A dialog box will appear, and click “Add” within the “File” tab to add the multimedia file (skydiving.avi has been provided as a sample) you want to display, and then click “Stream” in the same tab. A new dialog will open. Verify that the “Source:” field has the file you want to display, and then click “Next”. Check the box that says “Display Locally”, and from the dropdownmenu, configure “RTP/MPEG Transport Stream” or “UDP”. For either one, select it from the dropdown menu, and click “Add”. In the address field, enter the IP address to stream the video to where the program you developed resides and a port number (this willbe the listener IP and listener port, remember this port number because this is the listenerport parameter passed to your program). Click “Stream”
    - Start a new terminal and enter the command to start the destination VLC player:
      - $ vlc -vvv udp://@DEST_IP:DEST_PORT

3. Lab 4
    - In this lab experiment, you are required to design and develop a sender function (primary.c) to implement the Go-Back-N ARQ protocol, with a Primary function (which will act as a client or sender) while the Secondary function (which will act as a server or receiver) is given to you. This Go-Back-N ARQ protocol is a revised version from the one we learned in class. One difference is that it uses both ACK and NAK packets; this is to simplify the implementation and avoid having to implement the timeout mechanism.
    - Send the alphabet, ABCDEFGHIJKLMNOPQRSTUVWXYZ, to the Secondary in a total of 13 packets (2 characters per packet, NOTE: the total number of packets sent may be higher since the packets may be corrupted by IntroduceError() and thus need to be redelivered).
    - Implement the Go-Back-N ARQ protocol with a send window of size N = 3: 
        - The Primary sends the packet to the Secondary and keeps it in a buffer until an ACK is received forthis packet. The Primary displays an indication of sending the packet, together with its sequence number.
        - When the Primary receives an ACK from the Secondary, it adjusts the send window and removes the packet from its buffer.  It also displays an indication of which packet was positively acknowledged.
        - When the Primary receives a NAK from the Secondary, it adjusts the send window and retransmits all the packets in the send window.  It also displays an indication of which packets were negatively acknowledged and were retransmitted.
    - Run receiver, and have it listened on some port number (change 50404 to another number according to the notes mentioned above).
        - ./receiver 50404
    - Run sender, and have it connected to the receiver program on a given IP and port number (that should match the receiver’s). You are also required to pass the BER value that will be handed down to your primary function.
        - ./sender 127.0.0.1 50404 0.001

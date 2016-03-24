#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char**argv)
{
   int sockfd; //ID for socket
   struct sockaddr_in servaddr,cliaddr; //address-structure for IP-Address
   char pNumber; //variable for program number to switch to

	if(argc < 2)  //give a hint in case of invalid parameters
	{
		printf("usage: LJV7_Trigger <IP-Address> \n");
		return EXIT_FAILURE;
	}
	

	
   printf("Sending Trigger to Controller @%s \n", argv[1]); //output status

   //byte-structure/command for sending trigger
   char LJV_Trigger[] = { 0x14, 0x00, 0x00, 0x00, 0x01, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
   size_t LJV_Trigger_s = sizeof(LJV_Trigger);  //get size

   sockfd=socket(AF_INET,SOCK_STREAM,0);//create socket
   servaddr.sin_family = AF_INET; //for protocol family
   servaddr.sin_addr.s_addr=inet_addr(argv[1]); //controller's IP-Address
   servaddr.sin_port=htons(24691); //port to be used

   
   connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)); //connect to controller
   send(sockfd, LJV_Trigger, LJV_Trigger_s, MSG_DONTROUTE); //send command
   char recvline[1000];  //buffer for response
   int n;
   usleep(5*10000); //simply wait x ms for controller to answer - replace this with an event-driven approach if needed
   n=read(sockfd,recvline,1000,0,NULL,NULL); //read socket/received data
   recvline[n]=0; //add string termination character 
   fputs(recvline,stdout);
   printf("Received %i Bytes in response: ", n);
   int i;
   for (i=0; i<n+1; i++) printf("%02X ", (unsigned char)recvline[i]); //output every byte
   printf("\n");
   int ErrorCode = (unsigned char)recvline[17];
   if (ErrorCode == 128) printf("Error: Controller is not in external trigger mode, error condition was set to 0x%02X", ErrorCode);
   close(sockfd);
}
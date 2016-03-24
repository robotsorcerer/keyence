#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char**argv)
{
   int sockfd; //ID for socket
   struct sockaddr_in servaddr,cliaddr; //address-structure for IP-Address
   char autoZeroState; //variable for auto zero state (on/off) 

	if(argc < 2)  //give a hint in case of invalid parameters
	{
		printf("usage: LJV7_AutoZero <IP-Address> <1 for on, 0 for off> \n");
		return EXIT_FAILURE;
	}
	
	int autoZeroStateParam; //auto zero state for switch-structure
	autoZeroStateParam = atoi(argv[2]); //fetch parameter
	switch (autoZeroStateParam) {
		case(0): autoZeroState = 0x00; break;
		case(1): autoZeroState = 0x01; break;
		default: autoZeroState = 0x00; break;
	}
	
	printf("Sending AutoZero-Command to Controller @%s \n", argv[1]); //output status

   //byte-structure/command for sending auto zero command
   char LJV_AutoZero[] = { 0x18, 0x00, 0x00, 0x00, 0x01, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00, autoZeroState, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00 };
    
   //Byte21 'autoZeroState' tells whether to enable (everything other than 0) or to disalbe (=0) AutoZero (set measurement value to zero or restore to original value)
   //Byte25 and 26 address the affected out number(s) bitwise (1000 0000 0000 0000 or 0x00 0x0F for OUT16 / 0000 0000 0000 0001 or 0x01 0x00 is OUT1). Pay attention to the endianess - Byte25 covers OUT1-8, Byte26 OUT9-16 
   //Expample: Byte25=0x01 and Byte26=0x00 is OUT1, Byte25=0x00 and Byte26=0x0F is OUT16
   //consult 'LJ-V7000 Communication Protocol' for more details

   size_t LJV_AutoZero_s = sizeof(LJV_AutoZero);  //get size

   sockfd=socket(AF_INET,SOCK_STREAM,0);//create socket
   servaddr.sin_family = AF_INET; //for protocol family
   servaddr.sin_addr.s_addr=inet_addr(argv[1]); //controller's IP-Address
   servaddr.sin_port=htons(24691); //port to be used

   
   connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)); //connect to controller
   send(sockfd, LJV_AutoZero, LJV_AutoZero_s, MSG_DONTROUTE); //send command
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
   close(sockfd);
}
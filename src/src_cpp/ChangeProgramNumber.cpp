#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char**argv)
{
   int sockfd; //ID for socket
   struct sockaddr_in servaddr,cliaddr; //address-structure for IP-Address
   char pNumber; //variable for program number to switch to

	if(argc < 3)  //give a hint in case of invalid parameters
	{
		printf("usage: LJV7_ChangeProgramNumber <IP-Address> <ProgramNumber> \n");
		return EXIT_FAILURE;
	}
	
	int pNumberParam; //program number for switch-structure
	pNumberParam = atoi(argv[2]); //fetch parameter
	switch (pNumberParam) {
		case(0): pNumber = 0x00; break;
		case(1): pNumber = 0x01; break;
		case(2): pNumber = 0x02; break;
		case(3): pNumber = 0x03; break;
		case(4): pNumber = 0x04; break;
		case(5): pNumber = 0x05; break;
		case(6): pNumber = 0x06; break;
		case(7): pNumber = 0x07; break;
		case(8): pNumber = 0x08; break;	
		case(9): pNumber = 0x09; break;	
		case(10): pNumber = 0x0A; break;	
		case(11): pNumber = 0x0B; break;
		case(12): pNumber = 0x0C; break;	
		case(13): pNumber = 0x0D; break;	
		case(14): pNumber = 0x0E; break;
		case(15): pNumber = 0x0F; break;
		default: pNumber = 0x00; break;
	}
	
   printf("Changing Controller @%s to Program 0x0%X \n", argv[1], pNumber); //output status

   //byte-structure/command for changing current program number
   char LJV_ChangeProgram[] = { 0x14, 0x00, 0x00, 0x00, 0x01, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x39, 0x00, 0x00, 0x00, 0x5F, 0x14, 0xC0 };
   size_t LJV_ChangeProgram_s = sizeof(LJV_ChangeProgram);  //get size

   sockfd=socket(AF_INET,SOCK_STREAM,0);//create socket
   servaddr.sin_family = AF_INET; //for protocol family
   servaddr.sin_addr.s_addr=inet_addr(argv[1]); //controller's IP-Address
   servaddr.sin_port=htons(24691); //port to be used

   
   connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)); //connect to controller
   send(sockfd, LJV_ChangeProgram, LJV_ChangeProgram_s, MSG_DONTROUTE); //send command
   char recvline[1000];  //buffer for response
   int n;
   usleep(5*10000); //wait x ms for controller to answer
   n=read(sockfd,recvline,1000); //read socket/received data || ,0,NULL,NULL
   recvline[n]=0; //add string termination character 
   fputs(recvline,stdout);
   printf("Received %i Bytes in response: ", n);
   int i;
   for (i=0; i<n+1; i++) printf("%02X ", (unsigned char)recvline[i]); //output every byte
   printf("\n");
   close(sockfd);
}
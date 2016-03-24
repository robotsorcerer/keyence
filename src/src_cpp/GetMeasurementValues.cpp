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

	if(argc < 2)  //give a hint in case of invalid parameters
	{
		printf("usage: LJV7_GetMeasurementValues <IP-Address>\n");
		return EXIT_FAILURE;
	}
   printf("Getting measurement values of Controller @%s \n", argv[1]); //output status

   //byte-structure/command for getting latest measurement values
   char LJV_GetMeasurementValues[] = { 0x14, 0x00, 0x00, 0x00, 0x01, 0x00, 0xF0, 0x00, \
                                       0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, \
                                       0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
   size_t LJV_GetMeasurementValues_s = sizeof(LJV_GetMeasurementValues);  //get size

   sockfd=socket(AF_INET,SOCK_STREAM,0);//create socket
   servaddr.sin_family = AF_INET; //for protocol family
   servaddr.sin_addr.s_addr=inet_addr(argv[1]); //controller's IP-Address
   servaddr.sin_port=htons(24691); //port to be used

   connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)); //connect to controller
   send(sockfd, LJV_GetMeasurementValues, LJV_GetMeasurementValues_s, MSG_DONTROUTE); //send command
		   
   char recvline[1000];  //byte-buffer for response
   int n;
   usleep(5*10000); //simply wait x ms for controller to answer - replace this with an event-driven approach if needed
   n=read(sockfd,recvline,1000); //read socket/received data || ,0,NULL,NULL
   recvline[n]=0; //add string termination character 
   fputs(recvline,stdout); //print received bytes
   printf("Received %i Bytes in response: ", n); //print number of bytes
   //for (int i=0; i<n+1; i++) printf("%02X ", (unsigned char)recvline[i]); //output every byte
   printf("\n");

   //getting measurement value	for OUT1-OUT12
   int i;
   for(i=1; i<=16; i++)
   {
   		int msb, lsb, byte2, byte3, outStartBytePosition, outMeasurementValue, byteOffset; //integer-vairables
   		double outMeasurementValueMM; //measurement value in mm-scale should be a float value
   		byteOffset = (i-1) * 8; //every Out has an Offset of 8 byte to the prvious one (except Out1 which starts in byte 232) 
   		outStartBytePosition = 232 + byteOffset; //Out1 measurement value starts with lsb at byte 232 therefore we add OutNumber*8 to 
   		msb = (unsigned char)recvline[outStartBytePosition+3]; //due to network byte order, msb is the last of 4 bytes
   		byte2 =  (unsigned char)recvline[outStartBytePosition+2]; //followed by byte #2
   		byte3 = (unsigned char)recvline[outStartBytePosition+1];  //byte #3
   		lsb = (unsigned char)recvline[outStartBytePosition]; //and lsb
   		outMeasurementValue = msb << 24 | byte2 << 16 | byte3 << 8 | lsb; //shift bytes to big endian
   		outMeasurementValueMM = outMeasurementValue * 0.00001; //since values are stored in 10nm units we have to multiply with factor 0.00001 to reach a mm-scale
   		printf("OUT%i value = %fmm \n", i, outMeasurementValueMM); //output decimal value for OUT1-16
   }   
   close(sockfd);
}
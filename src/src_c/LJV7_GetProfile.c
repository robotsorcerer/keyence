#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char**argv)
{
   int sockfd; //ID for socket
   struct sockaddr_in servaddr,cliaddr; //address-structure for IP-Address

	if(argc < 2)  //give a hint in case of invalid parameters
	{
		printf("usage: LJV7_GetProfile <IP-Address>\n");
		return EXIT_FAILURE;
	}
   printf("Getting newest profile of Controller @%s \n", argv[1]); //output status

   //byte-structure/command for getting latest profile data
   char LJV_GetProfile[] = { 0x20,  0x00,  0x00,  0x00, 0x01 , 0x00, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x03};
   size_t LJV_GetProfile_s = sizeof(LJV_GetProfile);  //get size

   sockfd=socket(AF_INET,SOCK_STREAM,0);//create socket
   servaddr.sin_family = AF_INET; //for protocol family
   servaddr.sin_addr.s_addr=inet_addr(argv[1]); //controller's IP-Address
   servaddr.sin_port=htons(24691); //port to be used

   connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)); //connect to controller
   send(sockfd, LJV_GetProfile, LJV_GetProfile_s, MSG_DONTROUTE); //send command
		   
   char recvline[10000];  //byte-buffer for response
   int n;
   usleep(15*10000); //simply wait x ms for controller to answer - replace this with an event-driven approach if needed
   n=read(sockfd,recvline,10000,0,NULL,NULL); //read socket/received data
   recvline[n]=0; //add string termination character 
   fputs(recvline,stdout); //print received bytes
   printf("Received %i Bytes in response: ", n); //print number of bytes
   int i;
   for (i=0; i<n+1; i++) printf("%02X ", (unsigned char)recvline[i]); //output every byte, uncomment if necessary
   printf("\n");

   int msb, lsb, byte2, byte3, startBytePosition; //integer-vairables

   //Start outputting profile information
   printf("\nProfile information: \n");

   //Current profile number
   int currentProfileNumber;
   startBytePosition = 28; //start byte position according to protocol -1 (because array starts with 0)
   msb = (unsigned char)recvline[startBytePosition+3]; //due to network byte order, msb is the last of 4 bytes
   byte2 =  (unsigned char)recvline[startBytePosition+2]; //followed by byte #2
   byte3 = (unsigned char)recvline[startBytePosition+1];  //byte #3
   lsb = (unsigned char)recvline[startBytePosition]; //and lsb
   currentProfileNumber = msb << 24 | byte2 << 16 | byte3 << 8 | lsb; //shift bytes to big endian
   //printf("Current profile number = %i \n", msb, byte2, byte3, lsb, currentProfileNumber); //output value
   
   //Profile data count
   int profileDataCount = 0;
   startBytePosition = 46; //start byte position according to protocol -1 (because array starts with 0)
   msb = (unsigned char)recvline[startBytePosition+1]; //due to network byte order, msb is the last of 2 bytes
   lsb = (unsigned char)recvline[startBytePosition]; //and lsb
   profileDataCount = msb << 8 | lsb; //shift bytes to big endian
   printf("Profile data count = %i \n", profileDataCount); //output value

   //1st point X coordinate
   int firstPointCoordinate;
   double firstPointCoordinateMM;
   startBytePosition = 52; //start byte position according to protocol -1 (because array starts with 0)
   msb = (unsigned char)recvline[startBytePosition+3]; //due to network byte order, msb is the last of 4 bytes
   byte2 =  (unsigned char)recvline[startBytePosition+2]; //followed by byte #2
   byte3 = (unsigned char)recvline[startBytePosition+1];  //byte #3
   lsb = (unsigned char)recvline[startBytePosition]; //and lsb
   firstPointCoordinate = msb << 24 | byte2 << 16 | byte3 << 8 | lsb; //shift bytes to big endian
   firstPointCoordinateMM =  firstPointCoordinate * 0.00001; //since values are stored in 10nm units we have to multiply with factor 0.00001
   printf("1st point X coordinate = %f mm \n", firstPointCoordinateMM); //output value

   //X direction interval
   int xDirectionInterval;
   double xDirectionIntervalMM;
   startBytePosition = 56; //start byte position according to protocol -1 (because array starts with 0)
   msb = (unsigned char)recvline[startBytePosition+3]; //due to network byte order, msb is the last of 4 bytes
   byte2 =  (unsigned char)recvline[startBytePosition+2]; //followed by byte #2
   byte3 = (unsigned char)recvline[startBytePosition+1];  //byte #3
   lsb = (unsigned char)recvline[startBytePosition]; //and lsb
   xDirectionInterval = msb << 24 | byte2 << 16 | byte3 << 8 | lsb; //shift bytes to big endian
   xDirectionIntervalMM = xDirectionInterval * 0.00001; //since values are stored in 10nm units we have to multiply with factor 0.00001
   printf("X-direction interval = %f mm \n", xDirectionIntervalMM); //output value

   //Trigger count
   int triggerCount;
   startBytePosition = 64; //start byte position according to protocol -1 (because array starts with 0)
   msb = (unsigned char)recvline[startBytePosition+3]; //due to network byte order, msb is the last of 4 bytes
   byte2 =  (unsigned char)recvline[startBytePosition+2]; //followed by byte #2
   byte3 = (unsigned char)recvline[startBytePosition+1];  //byte #3
   lsb = (unsigned char)recvline[startBytePosition]; //and lsb
   triggerCount = msb << 24 | byte2 << 16 | byte3 << 8 | lsb; //shift bytes to big endian
   printf("Trigger count = %i \n", triggerCount); //output value
   
   //Encoder count
   int encoderCount;
   startBytePosition = 68; //start byte position according to protocol -1 (because array starts with 0)
   msb = (unsigned char)recvline[startBytePosition+3]; //due to network byte order, msb is the last of 4 bytes
   byte2 =  (unsigned char)recvline[startBytePosition+2]; //followed by byte #2
   byte3 = (unsigned char)recvline[startBytePosition+1];  //byte #3
   lsb = (unsigned char)recvline[startBytePosition]; //and lsb
   encoderCount = msb << 24 | byte2 << 16 | byte3 << 8 | lsb; //shift bytes to big endian
   printf("Encoder count = %i \n", encoderCount); //output value


   //Profile data points
   for(i = 1; i<=profileDataCount; i++)
	{
	   		int msb, lsb, byte2, byte3, startBytePosition, profileDataValue, byteOffset; //integer-vairables
	   		double profileDataValueMM; //measurement value in mm-scale should be a float value
	   		byteOffset = (i-1) * 4; //every Out has an Offset of 8 byte to the prvious one (except Out1 which starts in byte 232) 
	   		startBytePosition = 84 + byteOffset; //Out1 measurement value starts with lsb at byte 232 therefore we add OutNumber*8 to 
	   		msb = (unsigned char)recvline[startBytePosition+3]; //due to network byte order, msb is the last of 4 bytes
	   		byte2 =  (unsigned char)recvline[startBytePosition+2]; //followed by byte #2
	   		byte3 = (unsigned char)recvline[startBytePosition+1];  //byte #3
	   		lsb = (unsigned char)recvline[startBytePosition]; //and lsb
	   		profileDataValue = msb << 24 | byte2 << 16 | byte3 << 8 | lsb; //shift bytes to big endian
	   		profileDataValueMM = profileDataValue * 0.00001; //since values are stored in 10nm units we have to multiply with factor 0.00001 to reach a mm-scale
		    printf("%i: %fmm \n", i, profileDataValueMM); //print profile data values (value -21474.836480 means not measureable/invalid data point)
	}	
   

close(sockfd);
}
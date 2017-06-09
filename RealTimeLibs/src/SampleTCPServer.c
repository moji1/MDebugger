/*
 * SampleTCPServer.c
 *
 *  Created on: Nov 8, 2016
 *      Author: mojtababagherzadeh
 *      copied from https://www.tutorialspoint.com/unix_sockets/socket_server_example.htm and changed slightly
 */

#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>

#include <string.h>


int main1( int argc, char *argv[] ) {
   int sockfd, newsockfd, portno, clilen;
   printf("TCP server is started\n");
   char buffer[9999];
   struct sockaddr_in serv_addr, cli_addr;
   int  n;

   /* First call to socket() function */
   sockfd = socket(AF_INET, SOCK_STREAM, 0);

   if (sockfd < 0) {
      perror("ERROR opening socket");
      exit(1);
   }

   /* Initialize socket structure */
   bzero((char *) &serv_addr, sizeof(serv_addr));
   portno = 8001;

   serv_addr.sin_family = AF_INET;
   serv_addr.sin_addr.s_addr = INADDR_ANY;
   serv_addr.sin_port = htons(portno);

   /* Now bind the host address using bind() call.*/
   if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
      perror("ERROR on binding");
      exit(1);
   }

   /* Now start listening for the clients, here process will
      * go in sleep mode and will wait for the incoming connection
   */

   listen(sockfd,5);
   clilen = sizeof(cli_addr);

   /* Accept actual connection from the client */
   newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);

   if (newsockfd < 0) {
      perror("ERROR on accept");
      exit(1);
   }
   else
	   printf("new connection is established\n");

   /* If connection is established then start communicating */
   bzero(buffer,256);
   //// read the list upon the connection
   n = read(newsockfd,buffer,4);
   buffer[4]='\0';
   int length=atoi(buffer);
   printf("data length is : %d\n",length);
   n = read(newsockfd,buffer,length);
   if (n>1){
   buffer[n+1]='\0';
   printf("data is %s\n",buffer);
   }
   //// parsing of first list is done
   // send list command
   write(newsockfd,"0004list",8);
   /// read list command response
   n = read(newsockfd,buffer,4);
   buffer[4]='\0';
   length=atoi(buffer);
   printf("data length is : %d\n",length);
   n = read(newsockfd,buffer,length);
   if (n>1){
   buffer[n]='\0';
   printf("response is %s\n",buffer);
   }
   printf("try commands\n");
   char  cmd[256];
   //char buffer[1024];
   while (1){
	   bzero(cmd,256);
	   bzero(buffer,9999);
	   char ch;
	   int i=0;
	   while ( i<255){
		   ch=getchar();
		   if (ch!='\n')
			   cmd[i++]=ch;
		   else
			   break;
	   }
	   sprintf(buffer,"%04d%s",strlen(cmd),cmd);
	   write(newsockfd,buffer,strlen(buffer));
	   /// read list command response
	   n = read(newsockfd,buffer,4);
	   buffer[4]='\0';
	   length=atoi(buffer);
	   printf("data length is : %d\n",length);
	   n = read(newsockfd,buffer,length);
	   if (n>1){
	   buffer[n]='\0';
	   printf("response is %s\n",buffer);
   }
	   //// send list -c capsuleName
   }


   return 0;
}



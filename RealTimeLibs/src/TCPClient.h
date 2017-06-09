/*
 * TCPClient.h
 *
 *  Created on: Jun 12, 2016
 *      Author: mojtaba
 */

#ifndef TCPCLIENT_H_
#define TCPCLIENT_H_
#include<iostream>
#include<string.h>
#include<string>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<stdlib.h>
#include <iomanip>

namespace Comms {
enum connectionStatus{closed,opened};
class TCPClient {
public:
	inline TCPClient(int port=8001,std::string ip="127.0.0.1")
	{
		this->socketfd=-1;
		this->port=port;
		this->serverAddress=ip;
		status=closed;
	}
	inline virtual ~TCPClient()
	{
		if (this->status==opened)
		{
			close(this->socketfd);
		}

	}
	int conn();
	int sendData(std::string data);
	int receive(int len, char * buffer);
	void closeConn();
	int getPort() const ;

	void setPort(int port);

	const std::string& getServerAddress() ;

	void setServerAddress(const std::string& serverAddress) ;

	connectionStatus getStatus() const ;

	void setStatus(connectionStatus status);

	int  checkConnectionStatus(); // check if the connection is dropper or no

	int sendDataWithLen(const std::string  data);

	int receiveWithLen(char ** buffer);

private:

	int socketfd;
	std::string serverAddress;
	int port;
	struct sockaddr_in serv_addr;
	//struct hostent *server;
	connectionStatus status;

};


/////
inline int  TCPClient::checkConnectionStatus() // check if the connection is dropper or no
{
  int result=-1;
  struct sockaddr_in  addr;
  socklen_t len=sizeof(addr);
  result=getpeername(this->socketfd,(sockaddr *)& addr,&len);
  if (result==-1)
  {
	  perror("Get name failed, client  connection is dropped, try to connect again\n");
	  this->setStatus(closed);
  }

  return result;
}
/////
inline void TCPClient::closeConn() // close the connection, after close we can connect again, of the connection fail establishment
                            // the connection need to be closed first.
{
	if (socketfd!=-1)
	{
		close(socketfd);
		this->socketfd=-1;
		this->setStatus(closed);

	}
}



inline int TCPClient::conn(){ // return 0 if the conenction is sucessfull, otherwise -1 and print the error message
	int result=-1;
	if (this->socketfd==-1)
		socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if (socketfd < 0) {
	      perror("ERROR opening socket");
	      return result;
	   }
	struct hostent *server;
	server = gethostbyname(serverAddress.c_str());
	if (server == NULL) {
			perror("ERROR, no such host\n");
			return result;
		}
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr,server->h_length);
	serv_addr.sin_port = htons(this->port);
	//free(server);
	if (connect(this->socketfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
	{
		perror("ERROR connecting");
	    return -1;
	}
	this->setStatus(opened);
	return 0; // means connection is successful
}

inline int TCPClient::sendData(std::string data) // send string data, append  the "\0" to end of string for parsing purpose.
{
	int result=-1;
	//if (this->checkConnectionStatus()!=-1)
	std::cout<<"try to send data\n";
	//if (this->getStatus()==opened)
	{
	result = write(this->socketfd,data.c_str(),data.length());
	std::cout<<"data is written\to socket:\n"<<data;
	if (result < 0)
		perror("ERROR writing to socket");
		this->setStatus(closed);
	}
	return result;

}

inline int TCPClient::sendDataWithLen(const std::string  data) // send string data, append  the "\0" to end of string for parsing purpose.
{
	int result=-1;
	std::stringstream ss;
	//std::cout<<"data received by function is: "<<data<<"\n";
	if (data.length()>9999)
		return result; // max data to send is 9999, for larger data split it
	//if (this->checkConnectionStatus()!=-1)
	ss<<std::setfill ('0')<<std::setw(4)<<data.length();
	ss<<data;
	//std::cout<<"try to send data"<<ss.str()<<"\n";
	//if (this->getStatus()==opened)
	{
	result = write(this->socketfd,ss.str().c_str(),data.length()+4);
	//std::cout<<"Data is written\to socket:\n"<<data<<"\n";
	if (result < 0)
		perror("ERROR writing to socket");
		this->setStatus(closed);
	}
	return result;

}

inline int TCPClient::receive(int len, char * buffer)
{
	//buffer= new char[len];
	int result  = read(this->socketfd,buffer,len);
	if (result < 0)
	{
	    perror("ERROR reading from socket");
	}
	return result;

}
inline int TCPClient::receiveWithLen(char ** buffer) // the returned buffer is null terminated
{
	//buffer= new char[len];
	//std::cout<<"recieving data with length\n";
	char bufferStr[5];
	int length=0;
	int result  = read(this->socketfd,bufferStr,4);
	if (result==4){
		bufferStr[4]='\0';
		length=atoi(bufferStr);
		if (length>0){
			//std::cout<<"command length is: "<<length<<"\n";
			*buffer=(char *) malloc(length+1);
			bzero(*buffer,length+1);
			//std::cout<<"malloc is done\n";
			result=read(this->socketfd,*buffer,length);
			//std::cout<<"read is  is done\n";
			//*buffer[length]='\0';
			//std::cout<<"data is "<<*buffer<<"\n";
		}
	}
	else
		result=-1;
	return result;
}

inline int TCPClient::getPort() const {
	return this->port;
}

inline void TCPClient::setPort(int port) {
	this->port = port;
}

inline const std::string& TCPClient::getServerAddress()  {
	return serverAddress;
}

inline void TCPClient::setServerAddress(const std::string& serverAddress) {
	this->serverAddress = serverAddress;
}

inline connectionStatus TCPClient::getStatus() const {
	return status;
}

inline void TCPClient::setStatus(connectionStatus status) {
	this->status = status;
}

} /* namespace Comms */

#endif /* TCPCLIENT_H_ */

/*
 * UMLRTDebugger.h
 *
 *  Created on: Nov 22, 2016
 *      Author: mojtababagherzadeh
 */

#ifndef UMLRTDEBUGGER_H_
#define UMLRTDEBUGGER_H_
#include "CapsuleTracker.h"
#include "SharedMem.h"
#include "Config.h"
#include "DebugCommand.h"
#include <netdb.h>
#include <netinet/in.h>
#include "TCPClient.h"
#include <thread>
//#include <condition_variable>
#include <mutex>
#include <chrono>
#include "SROManager.h"
#include "ParsingUtil.h"
#include <iostream>
#include <fstream>
#include <unordered_set>


#include "CmdInterface.h"
namespace mdebugger {
static const std::string  DEBUG_PREFIX="__Debug__";
struct TCPServer{
	int sockfd, newsockfd, portno, client;
	sockaddr_in serv_addr, cli_addr;
};

class UMLRTDebugger {
public:
	UMLRTDebugger();
	virtual ~UMLRTDebugger();
	void readEvents();
	void sendCommand(std::string cmdStr);
	void intialize();
	void handelClient();
	void handelExtTCPSrvConn();//(std::string host, int port);
	int  getCaspuleIndex(std::string capsuleQualifiedName,debugEvents::Event event);
	void addCapsule(mdebugger::CapsuleTracker);
	void cmdMainLoop();
	void processUserCommnad();
	std::string processExtCommnad(mdebugger::CmdInterface cmd);
	void listCapsules();
	void listCapsuleConfig(std::string capsuleQualifiedName);
	void listCapsuleBreakPoints(std::string capsuleQualifiedName);
	std::string serializeCapsuleConfig(std::string capsuleQualifiedName);
	std::string serializeCapsuleBreakPoints(std::string capsuleQualifiedName);
	void viewCapsuleAttributes(std::string capsuleQualifiedName);
	void viewCapsuleEvents(std::string capsuleQualifiedName,int count);
	void viewSequenceDiagram(std::string capsuleQualifiedName,int count);
	std::string serializeCapsuleAttributes(std::string capsuleQualifiedName);
	std::string serializeCapsuleEvents(std::string capsuleQualifiedName,int count);
	void stepExec(std::string capsuleQualifiedName);
	void setBreakPoint(std::string capsuleQualifiedName,std::string transName,int location,BreakPointType breakPointType);
	void setExecMode(std::string capsuleQualifiedName,ExecMode execMode);
	void remBreakPoint(std::string capsuleQualifiedName,std::string transName,int location,BreakPointType breakPointType);
	const std::string  serializeCapsuleList();
	void modifyCapsuleAttribute(std::string capsuleQualifiedName,std::string varName,std::string varValue);
	void exitMDebugger();
	bool  saveEvents(std::string capsuleName,std::string filePath);
	const std::string& getIntialInput() const;
	void setIntialInput(const std::string& intialInput);
	bool isIntialInputPresent() const;
	void setIntialInputPresent(bool intialInputPresent);

	Comms::TCPClient   clientConn;
private:
	std::vector<mdebugger::CapsuleTracker> capsules;
	std::map<std::string,int> capsuleMap;
	Comms::SharedMem eventQ;
	Comms::SharedMem commandQ;
	ConfigUtil::Config config;
	void intializeTCP();
	void intializeSHM();
	std::mutex eventMutex;
	std::mutex commandMutex;
	bool  commandIsReady;
	bool  eventIsReady;
	bool  intialInputPresent;
	std::string intialInput;
	//std::condition_variable eventCond;
	//std::condition_variable cmdCond;
	std::thread extCon;
	CmdInterface cmdLineInterface;
	static bool eventComp(const debugEvents::Event &e1, const debugEvents::Event &e2);
	std::string convertTime(long timeSecond, long timeNano);
};

} /* namespace mdebugger */

#endif /* UMLRTDEBUGGER_H_ */

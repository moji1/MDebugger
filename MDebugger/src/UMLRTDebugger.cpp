/*
 * UMLRTDebugger.cpp
 *
 *  Created on: Nov 22, 2016
 *      Author: mojtababagherzadeh
 */

#include "UMLRTDebugger.h"



namespace mdebugger {


UMLRTDebugger::UMLRTDebugger() {
	// TODO Auto-generated constructor stub
	eventIsReady=false;
	commandIsReady=false;
	intialInputPresent=false;

}

UMLRTDebugger::~UMLRTDebugger() {
	this->extCon.join();
	// TODO Auto-generated destructor stub
}

} /* namespace mdebugger */

void mdebugger::UMLRTDebugger::intialize() {
	this->intializeSHM();
}

void mdebugger::UMLRTDebugger::readEvents() {
	 bool newEvent=false;
	 while (true){
	    std::string tempStr=this->eventQ.safePopBackString(); // for a reason that i don't know push_back and pop back works like pushback and popfront, that is wired
	    //std::cout<<"try read event\n";
	    if (tempStr!=""){
	    	debugEvents::Event e1;
	    	e1.deserialize(tempStr);
	    	//std::cout<<"Event reader-> waiting for lock\n";
	    	std::unique_lock<std::mutex> l1(eventMutex);
	    	//std::cout<<"Event reader-> lock acquired \n";
	    	int cpasuleIndex=this->getCaspuleIndex(e1.getOwnerName(),e1);
	    	if (cpasuleIndex>=0){
	    		this->capsules[cpasuleIndex].addEvent(e1);
	    		if (e1.getEventSourceKind()==debugEvents::STATE &&
	    				(e1.getEventType()==debugEvents::STATEENTRYSTART || e1.getEventType()==debugEvents::STATEENTRYEND ) &&
	    				e1.getSourceName()!=this->capsules[cpasuleIndex].getCurrentState()){
	    			this->capsules[cpasuleIndex].setCurrentState(e1.getSourceName());
	    			//std::cout<<e1.getSimpleSourceName()<<"\n";
	    			/// if capsule running mode is Run and the state is added by instruemnation send stepExec command
	    			//if (this->capsules[cpasuleIndex].getExecMode()==ExecMode::Running &&
	    			//		e1.getSimpleSourceName().find(DEBUG_PREFIX)!=std::string::npos ){
	    			//	this->stepExec(e1.getOwnerName());
	    				//std::cout<<"Step exec beacuse of STATEENTRY and RUN mode"<<"\n";
	    			//}
	    			//else if (this->capsules[cpasuleIndex].getExecMode()==ExecMode::Resume &&
	    			//		e1.getSimpleSourceName().find(DEBUG_PREFIX)!=std::string::npos &&
					//		!(capsules[cpasuleIndex].existBreakPoints(e1.getSimpleSourceName())) ){
	    			//	this->stepExec(e1.getOwnerName());
	    			//}
	    		}
	    		newEvent=true;
	    	}

	    }
	    /*else if (!eventIsReady and newEvent ){
	    	eventIsReady=true;
	    	newEvent=false;
	    }
	    else if (eventIsReady){
	    	eventCond.notify_all();
	    	eventIsReady=false;
	    }*/
	    else sleep(1);
	 }
}

int mdebugger::UMLRTDebugger::getCaspuleIndex(std::string capsuleOwner,debugEvents::Event event) {
	if (capsuleOwner.length()>=1)
	if (this->capsuleMap.count(capsuleOwner))
			return this->capsuleMap.at(capsuleOwner);
		else{
			int n=this->capsuleMap.size();
			this->capsuleMap[capsuleOwner]=n;
			mdebugger::CapsuleTracker c1;
			c1.setCapsuleName(event.getCapsuleName());
			c1.setCapsuleInstance(event.getCapsuleInstance());
			c1.setCapsuleIndex(event.getCapsuleIndex());
			this->capsules.push_back(c1);
			return capsuleMap.at(capsuleOwner);
		}
	else
		return -1;
}

void mdebugger::UMLRTDebugger::addCapsule(mdebugger::CapsuleTracker capsuleTracker) {
	this->capsules.push_back(capsuleTracker);
}

void mdebugger::UMLRTDebugger::listCapsuleConfig(std::string capsuleName) {
	for(std::map<std::string,int>::const_iterator it = this->capsuleMap.begin(); it != this->capsuleMap.end(); ++it)
		if (it->first.find(capsuleName) != std::string::npos){
			//std::cout<<it->second <<") "<<it->first<<"\n";
			//std::cout<<std::setw(30)<<std::setfill('-')<<"\n";
			std::cout<<"Current State is \""<<this->capsules[it->second].getCurrentState()<<"\"\n";
			std::cout<<"Running Mode is  \""<<this->capsules[it->second].getExecModeStr()<<"\"\n";
			std::cout<<"Breakpoints:\n"; //
			for (int i=0;i<this->capsules[it->second].getBreakPoints().size();i++)
				std::cout<<i+1<<") "<<this->capsules[it->second].getBreakPoints()[i]<<"\n";
			}

}

void mdebugger::UMLRTDebugger::listCapsuleBreakPoints(std::string capsuleName) {
	for(std::map<std::string,int>::const_iterator it = this->capsuleMap.begin(); it != this->capsuleMap.end(); ++it)
		if (it->first.find(capsuleName) != std::string::npos){
			//std::cout<<it->second <<"- "<<it->first<<"\n";
			std::cout<<"Breakpoints:\n"; //
			for (int i=0;i<this->capsules[it->second].getBreakPoints().size();i++)
				std::cout<<i+1<<") "<<this->capsules[it->second].getBreakPoints()[i]<<"\n";
			}
}

void mdebugger::UMLRTDebugger::viewCapsuleAttributes(std::string capsuleName) {
	//std::cout<<"show variables\n";
	for(std::map<std::string,int>::const_iterator it = this->capsuleMap.begin(); it != this->capsuleMap.end(); ++it)
		if (it->first.find(capsuleName) != std::string::npos){
			//std::cout<<it->second <<") "<<it->first<<"\n";
			//this->capsules[it->second].processLiveEvent();
			std::cout<<"Current State is \""<<this->capsules[it->second].getCurrentState()<<"\"\n";
			std::cout<<"----------- "<<capsuleName<<" Capsule's Variables---------------------------\n"; //
			std::cout<<this->capsules[it->second].getLastEvent().getVariableData()<<"\n";
			//std::cout<<this->capsules[it->second].getLastEvent().getEventId()<<"\n";
			//std::cout<<"-----------------------------------------------------------------------------\n";
			}

}

void mdebugger::UMLRTDebugger::viewCapsuleEvents(std::string capsuleName,int count) {
	for(std::map<std::string,int>::const_iterator it = this->capsuleMap.begin(); it != this->capsuleMap.end(); ++it)
		if (it->first.find(capsuleName) != std::string::npos){
			//std::cout<<it->second <<"- "<<it->first<<"\n";
			//this->capsules[it->second].processLiveEvent();
			std::cout<<"Current State is \""<<this->capsules[it->second].getCurrentState()<<"\"\n";
			//std::cout<<"-----------last  "<<count<<" "<<capsuleName<<" Capsule's Events---------------------------\n"; //
			std::vector<debugEvents::Event> events=this->capsules[it->second].lastNEvents(count);
			for (int i=0;i<events.size();i++)
				std::cout<<i+1<<"- "<<events[i];
			}

}

// added by David
// Note that this doesn't work well for "fast" systems (e.g. PingPong where the two capsules are sending singals every
// few milliseconds.  By the time event data has been obtained from the first capsule, the second capsule will have recorded
// several more new events.  Can maybe get around this by somehow "pausing" all capsule execution while obtaining events?
void mdebugger::UMLRTDebugger::viewSequenceDiagram(std::string capsuleName,int count) {
	std::string filterString("Debug__Path"); //used to filter out duplicate transitions
	std::vector<debugEvents::Event> events;
	for(std::map<std::string,int>::const_iterator it = this->capsuleMap.begin(); it != this->capsuleMap.end(); ++it) {
		//if (it->first.find(capsuleName) != std::string::npos){
			mdebugger::CapsuleTracker currentCapsule = this->capsules[it->second];
			// for now, just grab 10*count events.  Find a better way to do this in the future though
			std::vector<debugEvents::Event> capEvents=currentCapsule.lastNEvents(count*10);
			int i = 0;
			int j = 0;
			while (j < count && i < capEvents.size()) {
			//for (int i=0;i<events.size();i++) {
				if (capEvents[i].getEventSourceKind() == 3){
					std::string sender = capEvents[i].getEventPayload().find("SenderCapsule")->second;
					std::string owner = capEvents[i].getOwnerName();
					if (!(capEvents[i].getEventPayload().find("Source")->second).compare(0,filterString.length(),filterString) &&
							(capsuleName == owner || capsuleName.substr(0,capsuleName.find(":")) == sender)) {
						events.push_back(capEvents[i]);
						//std::cout<<owner.substr(0,owner.find(":"))<<" <- "<<sender<<": "<<port<<" : "<<signal<<"\n";
						//std::cout<<"note right: "<<events[i].getTimePointSecond()<<":"<<events[i].getTimePointNano()<<"\n";
						//std::cout<<"note right: "<<convertTime(events[i].getTimePointSecond(), events[i].getTimePointNano());
						// note left if current capsule is sending signal
						j++;
					} // end if
				} // end if
				i++;
			} // end while
	} // end for
	sort(events.begin(),events.end(),eventComp);
	std::cout<<"@startuml\n";
	for (int i = 0; i < count && i < events.size(); i++){
		std::string sender = events[i].getEventPayload().find("SenderCapsule")->second;
		std::string owner = events[i].getOwnerName();
		std::string port = events[i].getEventPayload().find("Port")->second;
		std::string signal = events[i].getEventPayload().find("Signal")->second;
		std::cout<<owner.substr(0,owner.find(":"))<<" <- ";
		if (port == "timer")
			std::cout<<port;
		else
			std::cout<<sender;
		std::cout<<": "<<signal<<"\n";
		std::cout<<"note right: "<<events[i].getTimePointSecond()<<":"<<events[i].getTimePointNano()<<"\n";
		//std::cout<<"note right: "<<convertTime(events[i].getTimePointSecond(), events[i].getTimePointNano());
	} // end for
	std::cout<<"@enduml\n";
}

// added by David: for sorting vector of events by timestamp
bool mdebugger::UMLRTDebugger::eventComp(const debugEvents::Event &e1, const debugEvents::Event &e2){
	if (e1.getTimePointSecond() == e2.getTimePointSecond())
		return e1.getTimePointNano() > e2.getTimePointNano();
	else
		return e1.getTimePointSecond() > e2.getTimePointSecond();
}

// added by David: for formatting timestamp
std::string mdebugger::UMLRTDebugger::convertTime(long timeSecond, long timeNano) {
	char* t;
	strftime(t, 23, "%d-%m-%Y\\n(%H:%M:%S:",localtime(&timeSecond));
	std::string output(t);
	std::string nano = std::to_string(timeNano);
	return output + nano + ")\n";
}

void mdebugger::UMLRTDebugger::sendCommand(std::string cmdStr) {
	commandQ.safePushBackString(cmdStr);

}

void mdebugger::UMLRTDebugger::stepExec(std::string qualifiedName) {
	mdebugger::DebugCommand dbgCmd;
	//std::cout<<qualifiedName;
	dbgCmd.setQualifiedName(qualifiedName);
	dbgCmd.setCmdId(mdebugger::dbgCmd::EXEC);
	dbgCmd.generateTraceNo();
	sendCommand(dbgCmd.serialize());
}

void mdebugger::UMLRTDebugger::setBreakPoint(std::string capsuleName,std::string loc, int place,BreakPointType breakPointType) {
	std::stringstream ss;
	ss<<DEBUG_PREFIX;
	ss<<place;
	ss<<"__S__";
	ss<<loc;
	std::cout<<"setting breakpoint at loc='" <<loc<<"' place='"<<place<<"' type='"<<breakPointType<<"' \n";
	for(std::map<std::string,int>::const_iterator it = this->capsuleMap.begin(); it != this->capsuleMap.end(); ++it)
		if (it->first.find(capsuleName) != std::string::npos){
			this->capsules[it->second].setBreakPoints(ss.str());
	/// add to send breakpoint command to debugging agent, for now do not change existing code
			mdebugger::DebugCommand dbgCmd;
			dbgCmd.setQualifiedName(capsuleName);
			dbgCmd.setCmdId(dbgCmd::SETBREAKPOINT);
			dbgCmd.setCmdParams("loc", loc);
			dbgCmd.setCmdParams("type", Util::intToStr((int) breakPointType)); // // 0 = means TransitionEffectBreakPoint  1= StateEntryBreakPoint 2=StateExitBreakPoint
			dbgCmd.setCmdParams("place", Util::intToStr(place)); // 0 begin 1=end
			dbgCmd.generateTraceNo();
			sendCommand(dbgCmd.serialize());
		}
}

void mdebugger::UMLRTDebugger::setExecMode(std::string capsuleName,ExecMode execMode) {
	for(std::map<std::string,int>::const_iterator it = this->capsuleMap.begin(); it != this->capsuleMap.end(); ++it)
		if (it->first.find(capsuleName) != std::string::npos){
			this->capsules[it->second].setExecMode(execMode);
			mdebugger::DebugCommand dbgCmd;
			dbgCmd.setQualifiedName(capsuleName);
			dbgCmd.setCmdId(dbgCmd::SETEXECMODE);
			dbgCmd.setCmdParams("ExecMode", Util::intToStr(int(execMode))); // 0 begin 1=end
			dbgCmd.generateTraceNo();
			sendCommand(dbgCmd.serialize());
		}

}

void mdebugger::UMLRTDebugger::remBreakPoint(std::string capsuleName,std::string loc, int place,BreakPointType breakPointType) {
	std::stringstream ss;
	std::cout<<"setting breakpoint at loc='" <<loc<<"' place='"<<place<<"' type='"<<breakPointType<<"' \n";
	ss<<DEBUG_PREFIX;
	ss<<place;
	ss<<"__S__";
	ss<<loc;
	for(std::map<std::string,int>::const_iterator it = this->capsuleMap.begin(); it != this->capsuleMap.end(); ++it)
		if (it->first.find(capsuleName) != std::string::npos){
			this->capsules[it->second].remBreakPoint(ss.str());
			mdebugger::DebugCommand dbgCmd;
			dbgCmd.setQualifiedName(capsuleName);
			dbgCmd.setCmdId(dbgCmd::REMBREAKPOINT);
			dbgCmd.setCmdParams("loc", loc);
			dbgCmd.setCmdParams("type", Util::intToStr((int) breakPointType)); // // 0 = means TransitionEffectBreakPoint  1= StateEntryBreakPoint 2=StateExitBreakPoint
			dbgCmd.setCmdParams("place", Util::intToStr(place)); // 0 begin 1=end
			dbgCmd.generateTraceNo();
			sendCommand(dbgCmd.serialize());
		}
}

const std::string  mdebugger::UMLRTDebugger::serializeCapsuleList(){
	std::stringstream ss;
	bool firstRec=true;
	for(std::map<std::string,int>::const_iterator it = this->capsuleMap.begin(); it != this->capsuleMap.end(); ++it){
		if (firstRec)
			firstRec=false;
		else
			ss<<"&";
		ss<<it->first<<"|";
		ss<<this->capsules[it->second].getCurrentState();
	}
	return ss.str();

}
void mdebugger::UMLRTDebugger::handelExtTCPSrvConn(){//(std::string host, int port) {
	//Comms::TCPClient  * clientConn= new Comms::TCPClient(port,host);
	//if (clientConn.checkConnectionStatus()!=0){
		//std::cout<<host<<":"<<port<<"\n";
		if (clientConn.conn()==0 && clientConn.checkConnectionStatus()==0){
			mdebugger::CmdInterface extCmd;
			std::string tempS="";
			{
				std::unique_lock<std::mutex> lock(this->eventMutex);
				tempS=this->serializeCapsuleList();
			}
			if (clientConn.sendDataWithLen("0000|"+tempS))
				while (true){ // the map loop for handling request
					char * buffer;
					if (clientConn.receiveWithLen(&buffer)>0){
						tempS="";
						tempS.append(buffer);
						free(buffer);
						extCmd.setCommandStr(tempS);
						extCmd.tokenizeCommand();
						extCmd.parseCommand();
						std::string cmdTraceId="";
						if (extCmd.getParsedCmd().commandOptions.count("-i")==1){ // echo the command id
							mdebugger::ParsedCMD tempParsedCmd=extCmd.getParsedCmd();
							cmdTraceId=tempParsedCmd.commandOptions["-i"];
						}
						clientConn.sendDataWithLen(cmdTraceId+"|"+processExtCommnad(extCmd));
					}
					else{
						clientConn.closeConn();
						break;
					}
				}
		}
	//}
}

std::string mdebugger::UMLRTDebugger::serializeCapsuleConfig(std::string capsuleQualifiedName) {
	std::stringstream ss;
	bool firstRec=true;
	for(std::map<std::string,int>::const_iterator it = this->capsuleMap.begin(); it != this->capsuleMap.end(); ++it)
			if (it->first.find(capsuleQualifiedName) != std::string::npos){
				if (! firstRec)
					ss<<"&";
				else
					firstRec=false;
				ss<<it->first<<"|";
				ss<<this->capsules[it->second].getCurrentState()<<"|";
				ss<<this->capsules[it->second].getExecModeStr();
				for (int i=0;i<this->capsules[it->second].getBreakPoints().size();i++){
					ss<<"|";
					ss<<this->capsules[it->second].getBreakPoints()[i];
				}
			}
	return ss.str();
}

std::string mdebugger::UMLRTDebugger::serializeCapsuleBreakPoints(std::string capsuleQualifiedName) {
	std::stringstream ss;
	bool firstRec=true;
	for(std::map<std::string,int>::const_iterator it = this->capsuleMap.begin(); it != this->capsuleMap.end(); ++it)
		if (it->first.find(capsuleQualifiedName) != std::string::npos){
			if (! firstRec)
				ss<<"&";
			else
				firstRec=false;
			ss<<it->first;
			for (int i=0;i<this->capsules[it->second].getBreakPoints().size();i++){
				ss<<"|";
				ss<<this->capsules[it->second].getBreakPoints()[i];
			}
		}
	return ss.str();
}

std::string mdebugger::UMLRTDebugger::serializeCapsuleAttributes(std::string capsuleQualifiedName) {
	std::stringstream ss;
	bool firstRec=true;
	for(std::map<std::string,int>::const_iterator it = this->capsuleMap.begin(); it != this->capsuleMap.end(); ++it)
		if (it->first.find(capsuleQualifiedName) != std::string::npos){
			if (! firstRec)
				ss<<"&";
			else
				firstRec=false;
			ss<<it->first<<"|";
			ss<<this->capsules[it->second].getCurrentState()<<"|";
			ss<<this->capsules[it->second].getLastEvent().getVariableData();
			}
	return ss.str();

}

std::string mdebugger::UMLRTDebugger::serializeCapsuleEvents(std::string capsuleQualifiedName, int count) {
	std::stringstream ss;
	bool firstRec=true;
	for(std::map<std::string,int>::const_iterator it = this->capsuleMap.begin(); it != this->capsuleMap.end(); ++it)
		if (it->first.find(capsuleQualifiedName) != std::string::npos){
			if (! firstRec)
				ss<<"&";
			else
				firstRec=false;
			ss<<it->first<<"|";
			ss<<this->capsules[it->second].getCurrentState();
			std::vector<debugEvents::Event> events=this->capsules[it->second].lastNEvents(count);
			for (int i=0;i<events.size();i++){
					ss<<"|";
					ss<<i+1<<events[i].serialize();
			}
		}
	return ss.str();
}

void mdebugger::UMLRTDebugger::modifyCapsuleAttribute(std::string capsuleQualifiedName, std::string varName,std::string varValue) {
	mdebugger::DebugCommand dbgCmd;
	dbgCmd.setQualifiedName(capsuleQualifiedName);
	dbgCmd.setCmdId(mdebugger::dbgCmd::VARCHANGE);
	dbgCmd.generateTraceNo();
	dbgCmd.setCmdParams(varName, varValue);
	sendCommand(dbgCmd.serialize());
}

void mdebugger::UMLRTDebugger::exitMDebugger() {
	// later add code to close the connection to SHM and tcp sockets
	exit(0);

}

bool mdebugger::UMLRTDebugger::saveEvents(std::string capsuleName,std::string filePath) {
	std::ofstream traceFile (filePath);
	if (!(traceFile.is_open()))
		return false;
	else
		for(std::map<std::string,int>::const_iterator it = this->capsuleMap.begin(); it != this->capsuleMap.end(); ++it){
			if (capsuleName=="*" || it->first.find(capsuleName) != std::string::npos){
				std::vector<debugEvents::Event> events=this->capsules[it->second].lastNEvents(this->capsules[it->second].eventsSize());
				for (int i=0;i<events.size();i++)
					traceFile<<events[i]<<std::endl;
				}
			}
	traceFile.close();
	return true;
}

void mdebugger::UMLRTDebugger::intializeSHM() {
	this->eventQ.setName("EventArea");
	this->eventQ.setQueueName("EventQ");
	this->eventQ.setSize(99999999);
	this->eventQ.setWithLock(true);
	eventQ.setUp(client);
	this->commandQ.setName("CommandArea");
	this->commandQ.setQueueName("CommandQ");
	this->commandQ.setSize(9999);
	this->commandQ.setWithLock(true);
	commandQ.setUp(client);
}

void mdebugger::UMLRTDebugger::intializeTCP() {
}

void mdebugger::UMLRTDebugger::listCapsules(){
	std::cout<<"Running Capsule List:\n";
	for(std::map<std::string,int>::const_iterator it = this->capsuleMap.begin(); it != this->capsuleMap.end(); ++it){
			std::cout<<it->second <<"- "<<it->first<<"\n";
			//this->capsules[it->second].processLiveEvent();
			//std::cout<<std::setw(30)<<std::setfill('-')<<"\n";
			std::cout<<"Current State is \""<<this->capsules[it->second].getCurrentState()<<"\"\n";
			//std::cout<<std::setw(40)<<std::setfill('-')<<"\n";
		}
}

void mdebugger::UMLRTDebugger::cmdMainLoop() {
	while (true){
		/// check for intial command and run it if there is any
		if (this->isIntialInputPresent()){
			sleep(1);
			cmdLineInterface.setCommandStr(this->getIntialInput());
			cmdLineInterface.tokenizeCommand();
			if (cmdLineInterface.parseCommand())
				processUserCommnad();
			else
				std::cout<<"Command is invalid, please use help to see the commands and their options\n";
			this->setIntialInputPresent(false);
		}
		cmdLineInterface.getCommand();
		cmdLineInterface.tokenizeCommand();
		if (cmdLineInterface.parseCommand())
			processUserCommnad();
		else
			std::cout<<"Command is invalid, please use help to see the commands and their options\n";
	}
}

void mdebugger::UMLRTDebugger::processUserCommnad() {
	mdebugger::ParsedCMD cmd=cmdLineInterface.getParsedCmd();
	switch(cmd.cmdID){
		case mdebugger::mdebuggerCommand::HELP:
			cmdLineInterface.showHelp();
			break;
		case mdebugger::mdebuggerCommand::EXIT:
			exitMDebugger();
			break;
		case mdebugger::mdebuggerCommand::SAVE:
			if (cmd.commandOptions.count("-c")==1 && cmd.commandOptions.count("-f")==1){
				std::unique_lock<std::mutex> lock(this->eventMutex);
				saveEvents(cmd.commandOptions["-c"],cmd.commandOptions["-f"]);
			}
			break;
		case mdebugger::mdebuggerCommand::LIST:
			if (cmd.commandOptions.count("-c")==1 && cmd.commandOptions.count("-b")==1){
				std::unique_lock<std::mutex> lock(this->eventMutex);
				listCapsuleBreakPoints(cmd.commandOptions["-c"]);
			}
			else if (cmd.commandOptions.count("-c")==1){
				std::unique_lock<std::mutex> lock(this->eventMutex);
				listCapsuleConfig(cmd.commandOptions["-c"]);
			}
			else {
				std::unique_lock<std::mutex> lock(this->eventMutex);
				listCapsules();}
			break;
		case mdebugger::mdebuggerCommand::VIEW:
			if (cmd.commandOptions.count("-c")==1 && cmd.commandOptions.count("-v")==1){
				std::unique_lock<std::mutex> lock(this->eventMutex);
				viewCapsuleAttributes(cmd.commandOptions["-c"]);
			}
			else if (cmd.commandOptions.count("-c")==1 && cmd.commandOptions.count("-e")==1){
				std::unique_lock<std::mutex> lock(this->eventMutex);
				if (cmd.commandOptions.count("-n")==1){
					if  (atoi(cmd.commandOptions["-n"].c_str())>0)
						viewCapsuleEvents(cmd.commandOptions["-c"], atoi(cmd.commandOptions["-n"].c_str()));
				}
				else
					viewCapsuleEvents(cmd.commandOptions["-c"], 5);
			}
			break;
		case mdebugger::mdebuggerCommand::NEXT:
			if (cmd.commandOptions.count("-c")==1 ){
				std::unique_lock<std::mutex> lock(this->eventMutex);
				std::cout<<"Step execution to  next model-level instruction\n";
				setExecMode(cmd.commandOptions["-c"],ExecMode::Stepping);
				stepExec(cmd.commandOptions["-c"]);
			}
			break;
		case mdebugger::mdebuggerCommand::BREAKPOINT:
			if (cmd.commandOptions.count("-c")==1 && cmd.commandOptions.count("-t")==1 && cmd.commandOptions.count("-b")==1 && cmd.commandOptions.count("-r")==1){
				std::unique_lock<std::mutex> lock(this->eventMutex);
				std::cout<<"Removing breakpoint at beginning of the transition "<<cmd.commandOptions["-t"]<<std::endl;
				remBreakPoint(cmd.commandOptions["-c"],cmd.commandOptions["-t"],0,TransitionEffectBreakPoint);
			}
			else if (cmd.commandOptions.count("-c")==1 && cmd.commandOptions.count("-t")==1 && cmd.commandOptions.count("-e")==1 && cmd.commandOptions.count("-r")==1){
				std::unique_lock<std::mutex> lock(this->eventMutex);
				std::cout<<"Removing breakpoint at end of the transition "<<cmd.commandOptions["-t"]<<std::endl;
				remBreakPoint(cmd.commandOptions["-c"],cmd.commandOptions["-t"],1,TransitionEffectBreakPoint);
			}
			else if (cmd.commandOptions.count("-c")==1 && cmd.commandOptions.count("-t")==1 && cmd.commandOptions.count("-b")==1){
				std::unique_lock<std::mutex> lock(this->eventMutex);
				std::cout<<"Setting breakpoint at start of transition "<<cmd.commandOptions["-t"]<<std::endl;
				setBreakPoint(cmd.commandOptions["-c"],cmd.commandOptions["-t"],0,TransitionEffectBreakPoint);
			}
			else if (cmd.commandOptions.count("-c")==1 && cmd.commandOptions.count("-t")==1 && cmd.commandOptions.count("-e")==1){
				std::unique_lock<std::mutex> lock(this->eventMutex);
				std::cout<<"Setting breakpoint at beginning  of transition "<<cmd.commandOptions["-t"]<<std::endl;
				setBreakPoint(cmd.commandOptions["-c"],cmd.commandOptions["-t"],1,TransitionEffectBreakPoint);
			}
			////state breckpoint
			else if (cmd.commandOptions.count("-c")==1 && cmd.commandOptions.count("-s")==1 && cmd.commandOptions.count("-b")==1 && cmd.commandOptions.count("-r")==1){
				std::unique_lock<std::mutex> lock(this->eventMutex);
				BreakPointType breakPointType;
				if (cmd.commandOptions.count("-entry")==1)
				     breakPointType=StateEntryBreakPoint;
				else if (cmd.commandOptions.count("-exit")==1)
					 breakPointType=StateExitBreakPoint;
				else {
					std::cout<<"Command  is invalid, specify -entry or exit,  use help to see options\n";
					break;
				}
				std::cout<<"Removing breakpoint at beginning of the state [entry/exit] "<<cmd.commandOptions["-s"]<<std::endl;
				remBreakPoint(cmd.commandOptions["-c"],cmd.commandOptions["-s"],0,breakPointType);
			}
			else if (cmd.commandOptions.count("-c")==1 && cmd.commandOptions.count("-s")==1 && cmd.commandOptions.count("-e")==1 && cmd.commandOptions.count("-r")==1){
				std::unique_lock<std::mutex> lock(this->eventMutex);
				BreakPointType breakPointType;
				if (cmd.commandOptions.count("-entry")==1)
				     breakPointType=StateEntryBreakPoint;
				else if (cmd.commandOptions.count("-exit")==1)
					 breakPointType=StateExitBreakPoint;
				else {
					std::cout<<"Command  is invalid, specify -entry or exit,  use help to see options\n";
					break;
				}
				std::cout<<"Removing breakpoint at end of the state [entry/exit]  "<<cmd.commandOptions["-s"]<<std::endl;
				remBreakPoint(cmd.commandOptions["-c"],cmd.commandOptions["-s"],1,breakPointType);
			}
			else if (cmd.commandOptions.count("-c")==1 && cmd.commandOptions.count("-s")==1 && cmd.commandOptions.count("-b")==1){
				std::unique_lock<std::mutex> lock(this->eventMutex);
				BreakPointType breakPointType;
				if (cmd.commandOptions.count("-entry")==1)
				     breakPointType=StateEntryBreakPoint;
				else if (cmd.commandOptions.count("-exit")==1)
					 breakPointType=StateExitBreakPoint;
				else {
					std::cout<<"Command  is invalid, specify -entry or exit,  use help to see options\n";
					break;
				}
				std::cout<<"Setting breakpoint at beginning of state [entry/exit] "<<cmd.commandOptions["-s"]<<std::endl;
				setBreakPoint(cmd.commandOptions["-c"],cmd.commandOptions["-s"],0,breakPointType);
			}
			else if (cmd.commandOptions.count("-c")==1 && cmd.commandOptions.count("-s")==1 && cmd.commandOptions.count("-e")==1){
				std::unique_lock<std::mutex> lock(this->eventMutex);
				BreakPointType breakPointType;
				if (cmd.commandOptions.count("-entry")==1)
				     breakPointType=StateEntryBreakPoint;
				else if (cmd.commandOptions.count("-exit")==1)
					 breakPointType=StateExitBreakPoint;
				else {
					std::cout<<"Command  is invalid, specify -entry or exit,  use help to see options\n";
					break;
				}
				std::cout<<"Setting breakpoint at end of state [etry/exit] "<<cmd.commandOptions["-s"]<<std::endl;
				setBreakPoint(cmd.commandOptions["-c"],cmd.commandOptions["-s"],1,breakPointType);
			}
			break;
		case mdebugger::mdebuggerCommand::CONTINUEEXEC:
			if (cmd.commandOptions.count("-c")==1){
				std::unique_lock<std::mutex> lock(this->eventMutex);
				setExecMode(cmd.commandOptions["-c"],ExecMode::Resume);
				stepExec(cmd.commandOptions["-c"]);
			}
			break;
		case mdebugger::mdebuggerCommand::RUNEXEC:
			if (cmd.commandOptions.count("-c")==1){
				std::unique_lock<std::mutex> lock(this->eventMutex);
				setExecMode(cmd.commandOptions["-c"],ExecMode::Running);
				stepExec(cmd.commandOptions["-c"]);
			}
			break;
		case mdebugger::mdebuggerCommand::CONNECT:
			if (cmd.commandOptions.count("-h")==1 && cmd.commandOptions.count("-p")){
				std::cout<<"Starting TCP connection\n";
				std::string host=cmd.commandOptions["-h"];
				int port=atoi(cmd.commandOptions["-p"].c_str());
				clientConn.setPort(port);
				clientConn.setServerAddress(host);
				//std::thread extCon(&mdebugger::UMLRTDebugger::handelExtTCPSrvConn,this,std::cref(host),port);
				//this->extCon=std::thread(&mdebugger::UMLRTDebugger::handelExtTCPSrvConn,this,std::cref(host),port);
				this->extCon=std::thread(&mdebugger::UMLRTDebugger::handelExtTCPSrvConn,this);
				//extCon.detach();
			}
			break;
		case mdebugger::mdebuggerCommand::MODIFY:
			if (cmd.commandOptions.count("-c")==1 && cmd.commandOptions.count("-n") && cmd.commandOptions.count("-v")){
				modifyCapsuleAttribute(cmd.commandOptions["-c"],cmd.commandOptions["-n"],cmd.commandOptions["-v"]);
			}
			break;
		/// added by david
		case mdebugger::mdebuggerCommand::SEQ:
			if  (atoi(cmd.commandOptions["-n"].c_str())>0) {
				viewSequenceDiagram(cmd.commandOptions["-c"], atoi(cmd.commandOptions["-n"].c_str()));
			} else {
				std::cout<<"invalid count\n";
			}
			break;
		default:
			std::cout<<"command is unknown, please use help to see commands and their options\n";
			break;
			//cmdLineInterface.showPrompt();
	}
}

/////
std::string mdebugger::UMLRTDebugger::processExtCommnad(mdebugger::CmdInterface extCommand) {
	mdebugger::ParsedCMD cmd=extCommand.getParsedCmd();
	std::string cmdTraceId="";

	switch(cmd.cmdID){
		case mdebugger::mdebuggerCommand::LIST:
			if (cmd.commandOptions.count("-c")==1 && cmd.commandOptions.count("-b")==1){
				std::unique_lock<std::mutex> lock(this->eventMutex);
				return serializeCapsuleBreakPoints(cmd.commandOptions["-c"]);
			}
			else if (cmd.commandOptions.count("-c")==1){
				std::unique_lock<std::mutex> lock(this->eventMutex);
				return serializeCapsuleConfig(cmd.commandOptions["-c"]);
			}
			else {
				std::unique_lock<std::mutex> lock(this->eventMutex);
				return serializeCapsuleList();}
			return "INVALIDOPTION";
		case mdebugger::mdebuggerCommand::VIEW:
			if (cmd.commandOptions.count("-c")==1 && cmd.commandOptions.count("-v")==1){
				std::unique_lock<std::mutex> lock(this->eventMutex);
				return serializeCapsuleAttributes(cmd.commandOptions["-c"]);
			}
			else if (cmd.commandOptions.count("-c")==1 && cmd.commandOptions.count("-e")==1){
				std::unique_lock<std::mutex> lock(this->eventMutex);
				if (cmd.commandOptions.count("-n")==1){
					if  (atoi(cmd.commandOptions["-n"].c_str())>0)
						return serializeCapsuleEvents(cmd.commandOptions["-c"], atoi(cmd.commandOptions["-n"].c_str()));
				}
				else
					return serializeCapsuleEvents(cmd.commandOptions["-c"], 5);
			}
			return "INVALIDOPTION";
		case mdebugger::mdebuggerCommand::NEXT:
			if (cmd.commandOptions.count("-c")==1 ){
				std::unique_lock<std::mutex> lock(this->eventMutex);
				std::cout<<"Step execution to next\n";
				setExecMode(cmd.commandOptions["-c"],ExecMode::Stepping);
				stepExec(cmd.commandOptions["-c"]);
				return "ACK|"+cmd.commandOptions["-c"];
			}
			return "INVALIDOPTION";
		case mdebugger::mdebuggerCommand::BREAKPOINT:
			if (cmd.commandOptions.count("-c")==1 && cmd.commandOptions.count("-t")==1 && cmd.commandOptions.count("-b")==1 && cmd.commandOptions.count("-r")==1){
				std::unique_lock<std::mutex> lock(this->eventMutex);
				std::cout<<"Removing breakpoint at start of \n";
				remBreakPoint(cmd.commandOptions["-c"],cmd.commandOptions["-t"],0,TransitionEffectBreakPoint);
				return "ACK|"+cmd.commandOptions["-c"];
			}
			else if (cmd.commandOptions.count("-c")==1 && cmd.commandOptions.count("-t")==1 && cmd.commandOptions.count("-e")==1 && cmd.commandOptions.count("-r")==1){
				std::unique_lock<std::mutex> lock(this->eventMutex);
				std::cout<<"Removing breakpoint at start of \n";
				remBreakPoint(cmd.commandOptions["-c"],cmd.commandOptions["-t"],1,TransitionEffectBreakPoint);
				return "ACK|"+cmd.commandOptions["-c"];
			}
			else if (cmd.commandOptions.count("-c")==1 && cmd.commandOptions.count("-t")==1 && cmd.commandOptions.count("-b")==1){
				std::unique_lock<std::mutex> lock(this->eventMutex);
				std::cout<<"Setting breakpoint at start of \n";
				setBreakPoint(cmd.commandOptions["-c"],cmd.commandOptions["-t"],0,TransitionEffectBreakPoint);
				return "ACK|"+cmd.commandOptions["-c"];
			}
			else if (cmd.commandOptions.count("-c")==1 && cmd.commandOptions.count("-t")==1 && cmd.commandOptions.count("-e")==1){
				std::unique_lock<std::mutex> lock(this->eventMutex);
				std::cout<<"Setting breakpoint at start of \n";
				setBreakPoint(cmd.commandOptions["-c"],cmd.commandOptions["-t"],1,TransitionEffectBreakPoint);
				return "ACK|"+cmd.commandOptions["-c"];
			}
			////state breckpoint
			else if (cmd.commandOptions.count("-c")==1 && cmd.commandOptions.count("-s")==1 && cmd.commandOptions.count("-b")==1 && cmd.commandOptions.count("-r")==1){
				std::unique_lock<std::mutex> lock(this->eventMutex);
				std::cout<<"Removing breakpoint at begining of \n";
				BreakPointType breakPointType;
				if (cmd.commandOptions.count("-entry")==1)
				     breakPointType=StateEntryBreakPoint;
				else if (cmd.commandOptions.count("-exit")==1)
					 breakPointType=StateExitBreakPoint;
				else {
					std::cout<<"Command  is invalid, specify -entry or exit,  use help to see options\n";
					return "INVALIDOPTION";
				}
				remBreakPoint(cmd.commandOptions["-c"],cmd.commandOptions["-s"],0,breakPointType);
				return "ACK|"+cmd.commandOptions["-c"];
			}
			else if (cmd.commandOptions.count("-c")==1 && cmd.commandOptions.count("-s")==1 && cmd.commandOptions.count("-e")==1 && cmd.commandOptions.count("-r")==1){
				std::unique_lock<std::mutex> lock(this->eventMutex);
				std::cout<<"Removing breakpoint at end of \n";
				BreakPointType breakPointType;
				if (cmd.commandOptions.count("-entry")==1)
				     breakPointType=StateEntryBreakPoint;
				else if (cmd.commandOptions.count("-exit")==1)
					 breakPointType=StateExitBreakPoint;
				else {
					std::cout<<"Command  is invalid, specify -entry or exit,  use help to see options\n";
					return "INVALIDOPTION";
				}
				remBreakPoint(cmd.commandOptions["-c"],cmd.commandOptions["-s"],1,breakPointType);
				return "ACK|"+cmd.commandOptions["-c"];
			}
			else if (cmd.commandOptions.count("-c")==1 && cmd.commandOptions.count("-s")==1 && cmd.commandOptions.count("-b")==1){
				std::unique_lock<std::mutex> lock(this->eventMutex);
				std::cout<<"Setting breakpoint at start of \n";
				BreakPointType breakPointType;
				if (cmd.commandOptions.count("-entry")==1)
				     breakPointType=StateEntryBreakPoint;
				else if (cmd.commandOptions.count("-exit")==1)
					 breakPointType=StateExitBreakPoint;
				else {
					std::cout<<"Command  is invalid, specify -entry or exit,  use help to see options\n";
					return "INVALIDOPTION";
				}
				setBreakPoint(cmd.commandOptions["-c"],cmd.commandOptions["-s"],0,breakPointType);
				return "ACK|"+cmd.commandOptions["-c"];
			}
			else if (cmd.commandOptions.count("-c")==1 && cmd.commandOptions.count("-s")==1 && cmd.commandOptions.count("-e")==1){
				std::unique_lock<std::mutex> lock(this->eventMutex);
				std::cout<<"Setting breakpoint at end of \n";
				BreakPointType breakPointType;
				if (cmd.commandOptions.count("-entry")==1)
				     breakPointType=StateEntryBreakPoint;
				else if (cmd.commandOptions.count("-exit")==1)
					 breakPointType=StateExitBreakPoint;
				else {
					std::cout<<"Command  is invalid, specify -entry or exit,  use help to see options\n";
					return "INVALIDOPTION";
				}
				setBreakPoint(cmd.commandOptions["-c"],cmd.commandOptions["-s"],1,breakPointType);
				return "ACK|"+cmd.commandOptions["-c"];
			}
			return "INVALIDOPTION";
		case mdebugger::mdebuggerCommand::CONTINUEEXEC:
			if (cmd.commandOptions.count("-c")==1){
				std::unique_lock<std::mutex> lock(this->eventMutex);
				setExecMode(cmd.commandOptions["-c"],ExecMode::Resume);
				stepExec(cmd.commandOptions["-c"]);
				return "ACK|"+cmd.commandOptions["-c"];
			}
		case mdebugger::mdebuggerCommand::RUNEXEC:
			if (cmd.commandOptions.count("-c")==1){
				std::unique_lock<std::mutex> lock(this->eventMutex);
				setExecMode(cmd.commandOptions["-c"],ExecMode::Running);
				stepExec(cmd.commandOptions["-c"]);
				return "ACK|"+cmd.commandOptions["-c"];
			}
			return "INVALIDOPTION";
		case mdebugger::mdebuggerCommand::MODIFY:
			if (cmd.commandOptions.count("-c")==1 && cmd.commandOptions.count("-n") && cmd.commandOptions.count("-v")){
				modifyCapsuleAttribute(cmd.commandOptions["-c"],cmd.commandOptions["-n"],cmd.commandOptions["-v"]);
				return "ACK|"+cmd.commandOptions["-c"];
			}
			return "INVALIDOPTION";
		default:
			return "INVALIDCOMMAND";
	}
}

const std::string& mdebugger::UMLRTDebugger::getIntialInput() const {
return intialInput;
}

void mdebugger::UMLRTDebugger::setIntialInput(const std::string& intialInput) {
	this->setIntialInputPresent(true);
	this->intialInput = intialInput;
}

bool mdebugger::UMLRTDebugger::isIntialInputPresent() const {
return intialInputPresent;
}

void mdebugger::UMLRTDebugger::setIntialInputPresent(bool intialInputPresent) {
this->intialInputPresent = intialInputPresent;
}

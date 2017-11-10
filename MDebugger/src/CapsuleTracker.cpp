/*
 * CapsuleTracker.cpp
 *
 *  Created on: Nov 22, 2016
 *      Author: mojtababagherzadeh
 */

#include "CapsuleTracker.h"

namespace mdebugger {

CapsuleTracker::CapsuleTracker() {
	// TODO Auto-generated constructor stub
	this->capsuleIndex=0;
	//capsuleHistoryEvents.set_capacity(MAX_EVENT_BUFFER_SIZE);
	//execMode=STEPOVER;
	execMode=ExecMode::Stepping;
}

CapsuleTracker::~CapsuleTracker() {
	// TODO Auto-generated destructor stub
}

int CapsuleTracker::getCapsuleIndex() const {
	return capsuleIndex;
}

void CapsuleTracker::setCapsuleIndex(int capsuleIndex) {
	this->capsuleIndex = capsuleIndex;
}

const std::string& CapsuleTracker::getCapsuleInstance() const {
	return capsuleInstance;
}

void CapsuleTracker::setCapsuleInstance(
		const std::string& capsuleInstanceName) {
	this->capsuleInstance = capsuleInstanceName;
}

const std::string& CapsuleTracker::getCapsuleName() const {
	return capsuleName;
}

CapsuleTracker::CapsuleTracker(debugEvents::Event event) {
	this->capsuleIndex=event.getCapsuleIndex();
	this->setCapsuleInstance(event.getCapsuleInstance());
	this->setCapsuleName(event.getCapsuleName());
	//capsuleHistoryEvents.set_capacity(MAX_EVENT_BUFFER_SIZE);
	//execMode=STEPOVER;
	execMode=ExecMode::Stepping;
}

void CapsuleTracker::setCapsuleName(const std::string& capsuleName) {
	this->capsuleName = capsuleName;
}

void CapsuleTracker::addEvent(std::string eventStr) {
	debugEvents::Event e1;
	e1.deSerializePayload(eventStr);
	capsuleLiveEvents.push_front(e1);
}

void CapsuleTracker::addEvent(debugEvents::Event event) {
	//std::cout<<"adding event\n";
	this->capsuleLiveEvents.push_front(event);
	//std::cout<<"event is added\n";
	//std::cout<<"event is added\n";
}

const debugEvents::Event CapsuleTracker::lastEvent() {
	return this->capsuleLiveEvents.front();

}



const std::vector<debugEvents::Event>   CapsuleTracker::lastNEvents(int count) {
	if (count>this->capsuleLiveEvents.size())
			count=capsuleLiveEvents.size();
	std::vector<debugEvents::Event> v1(this->capsuleLiveEvents.begin(),this->capsuleLiveEvents.begin()+count);
	return v1;
}

const debugEvents::Event& CapsuleTracker::getLastEvent() const {
	return this->capsuleLiveEvents.front();
}

/*void   CapsuleTracker::processLiveEvent() {
	std::vector<std::string>::iterator it1;
	//for (int i=0; i< this->capsuleLiveEvents.size();i++){
	while (not this->capsuleLiveEvents.empty()){
		debugEvents::Event e1;
		e1=(this->capsuleLiveEvents.front());
		//std::cout<<e1.getEventId()<<"\n";
		if (e1.getEventSourceKind()==debugEvents::STATE && e1.getSourceName()!=this->getCurrentState())
			this->setCurrentState(e1.getSourceName());
		this->capsuleHistoryEvents.push_back(e1);
		this->capsuleLiveEvents.pop_front();
	}
}*/

void CapsuleTracker::clearEvents() {
	this->capsuleLiveEvents.clear();
}

int  CapsuleTracker::eventsSize() {
	return this->capsuleLiveEvents.size();
}

const std::string& CapsuleTracker::getCurrentState() const {
	return currentState;
}

void CapsuleTracker::setCurrentState(const std::string& currentState) {
	this->currentState = currentState;
}

bool CapsuleTracker::existBreakPoints(std::string location)  {
	std::deque<std::string>::iterator it1;
	for (it1=this->breakPoints.begin();it1!=this->breakPoints.end();it1++)
		if (it1->find(location)!=std::string::npos || location.find(*it1)!=std::string::npos) // be careful, we need to make it more percise later
			return true;
		/*else {
			std::cout<<*it1<<"\n";
			std::cout<<location<<"\n";
		}*/
	return false;
}

void CapsuleTracker::setBreakPoints(const std::string & location) {
	std::cout<<"Breakpoint is"<<location<<"\n";
	if (not this->existBreakPoints(location))
		this->breakPoints.push_back(location);
}


ExecMode CapsuleTracker::getExecMode() const {
	return execMode;
}

void CapsuleTracker::remBreakPoint(std::string location) {
	std::deque<std::string>::iterator it1;
	bool del=false;
	for (it1=this->breakPoints.begin();it1!=this->breakPoints.end();it1++)
			if (it1->find(location) != std::string::npos){
				del=true;
				break;
			}
	if (del)
		this->breakPoints.erase(it1);

}

void CapsuleTracker::remAllBreakPoints(std::string location) {
	this->breakPoints.clear();
}

void CapsuleTracker::setExecMode(ExecMode execMode) {
	this->execMode = execMode;
}

const std::deque<std::string>& CapsuleTracker::getBreakPoints() const {
	return breakPoints;
}

std::string CapsuleTracker::getQualifiedName() {
	std::stringstream s1;
	s1 << getCapsuleName()<<":"<<getCapsuleInstance()<<":"<<getCapsuleIndex();
	return s1.str();
}



const std::deque<debugEvents::Event>& CapsuleTracker::getCapsuleHistoryEvents() const {
	return capsuleLiveEvents;
}

void CapsuleTracker::setCapsuleHistoryEvents(const std::deque<debugEvents::Event>& capsuleHistoryEvents) {
	this->capsuleLiveEvents = capsuleHistoryEvents;
}

/*const std::string& CapsuleTracker::getLastState() const {
	return lastState;
}*/

/*void CapsuleTracker::setLastState(const std::string& lastState) {
	this->lastState = lastState;
}*/

std::string CapsuleTracker::getCrrentStateForPrint() {
	std::string fullCurrentState=this->getCurrentState();
	int i=fullCurrentState.find_last_of("::");
	std::string currentState=fullCurrentState.substr(i+1);
	i=currentState.find_first_of("__");
	std::string tempS=currentState.substr(0, i);
	if (tempS.compare("Debug")==0)
		currentState=currentState.substr(i+2);
	return currentState;

}

} /* namespace mdebugger */

std::string mdebugger::CapsuleTracker::getExecModeStr() {
	std::vector<std::string>  execModeStr={"STEPIN","STEPOVER","CONTINUE","RUN"};
	return execModeStr[this->getExecMode()];
}


